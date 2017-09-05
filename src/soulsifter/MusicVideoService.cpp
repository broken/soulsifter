#include "MusicVideoService.h"

#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <vector>

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/range/algorithm_ext/erase.hpp>
#include <boost/regex.hpp>

#include "Album.h"
#include "BasicGenre.h"
#include "Song.h"
#include "MusicVideo.h"
#include "MusicManager.h"
#include "SoulSifterSettings.h"
#include "TagService.h"

using namespace std;

namespace dogatech {
namespace soulsifter {

namespace {

string removeSpecialCharsFromPath(string filepath) {
  string newPath = boost::remove_erase_if(filepath, boost::is_any_of("'\""));
  if (!newPath.compare(filepath)) return filepath;

  cout << "Renaming '" << filepath << "'' to '" << newPath << "'" << endl;
  try {
      boost::filesystem::path src(filepath);
      boost::filesystem::path dest(newPath);
      boost::filesystem::rename(src, dest);
      return newPath;
  } catch (const boost::filesystem::filesystem_error& ex) {
      cerr << "Unable to rename music video related file '" << filepath << "'\n" << ex.what() << endl;
      return filepath;
  }
}

}  // namespace

vector<string> MusicVideoService::downloadYouTubeAudio(const string& id) {
  cout << "downloadYouTubeAudio YouTube video " << id << endl;
  vector<string> filepaths;

  boost::filesystem::path tmpPath(SoulSifterSettings::getInstance().get<string>("dir.tmp"));  // todo: use os.tmpdir()
  if (!boost::filesystem::exists(tmpPath)) {
    if (!boost::filesystem::create_directories(tmpPath)) {
      cerr << "Unable to create temporary directory " << tmpPath << endl;
      return filepaths;
    }
  } else if (!boost::filesystem::is_directory(tmpPath)) {
    cerr << "Temporary directory is not a directory " << tmpPath << endl;
    return filepaths;
  }

  FILE *fpipe;
  stringstream command;
  command << "cd " << tmpPath << "; youtube-dl --print-json --write-all-thumbnails --restrict-filenames --extract-audio --audio-format mp3 --audio-quality 0 --quiet www.youtube.com/watch?v=" << id;
  if (!(fpipe = (FILE*)popen(command.str().c_str(), "r"))) {
    cerr << "Problem with youtube-dl pipe." << endl;
    return filepaths;
  }

  char buffer[1024];
  stringstream ss;
  cout << "Running command '" << command.str() << "'" << endl;
  while (fgets(buffer, sizeof buffer, fpipe)) {
    ss << buffer;
  }

  pclose(fpipe);

  // read output
  string json;
  while (std::getline(ss, json, '\n')) {
    if (json.at(0) == '{') {
      boost::property_tree::ptree ptree;
      std::stringstream tmp(json);
      read_json(tmp, ptree);

      Song* song = new Song();
      Album* album = new Album();
      song->setAlbum(album);

      string baseFileName = ptree.get<string>("_filename").substr(0, ptree.get<string>("_filename").size() - ptree.get<string>("ext").size());
      song->setFilepath(SoulSifterSettings::getInstance().get<string>("dir.tmp") + '/' + baseFileName + "mp3");
      album->setCoverFilepath(SoulSifterSettings::getInstance().get<string>("dir.tmp") + '/' + baseFileName + "jpg");
      string title = ptree.get<string>("title");
      if (!MusicManager::getInstance().splitArtistAndTitle(title, song)) {
        song->setArtist(title);
        song->setTitle(title);
      }
      MusicManager::getInstance().moveFeaturing(song);
      MusicManager::getInstance().copyRemixer(song);
      song->setLowQuality(true);
      song->setCurator(ptree.get<string>("uploader"));
      string date = ptree.get<string>("upload_date", "00000000");
      if (!date.empty() && !!date.compare("null")) {
        album->setReleaseDateYear(std::stoi(date.substr(0, 4)));
        album->setReleaseDateMonth(std::stoi(date.substr(4, 2)));
        album->setReleaseDateDay(std::stoi(date.substr(6, 4)));
      }
      album->setName(song->getTitle());

      TagService::writeId3v2Tag(song);
      filepaths.push_back(song->getFilepath());
      filepaths.push_back(album->getCoverFilepath());
      delete song;
      return filepaths;
    }
  }
  return filepaths;
}

MusicVideo* MusicVideoService::associateYouTubeVideo(Song* const song, const string& id) {
  cout << "Associate YouTube video " << id << " with song " << song->getId() << endl;

  boost::filesystem::path mvBasePath(SoulSifterSettings::getInstance().get<string>("mv.dir"));
  if (!boost::filesystem::exists(mvBasePath) || !boost::filesystem::is_directory(mvBasePath)) {
    cerr << "Music video base path does not exist. " << mvBasePath << endl;
    return NULL;
  }

  string mvArtistDir;
  {
    stringstream ss;
    ss << mvBasePath.string() << song->getAlbum()->getBasicGenre()->getName() << "/" << song->getArtist();
    mvArtistDir = ss.str();
  }
  boost::filesystem::path mvArtistPath(mvArtistDir);
  if (!boost::filesystem::exists(mvArtistPath)) {
    if (!boost::filesystem::create_directories(mvArtistPath)) {
      cerr << "Unable to create music video artist directory " << mvArtistDir << endl;
      return NULL;
    }
  } else if (!boost::filesystem::is_directory(mvArtistPath)) {
    cerr << "Music video artist directory is not a directory " << mvArtistDir << endl;
    return NULL;
  }
      
  FILE *fpipe;
  stringstream command;
  command << "cd " << mvArtistDir << "; youtube-dl --write-thumbnail --restrict-filenames --merge-output-format mp4 www.youtube.com/watch?v=" << id;
  if (!(fpipe = (FILE*)popen(command.str().c_str(), "r"))) {
    cerr << "Problem with youtube-dl pipe." << endl;
    return NULL;
  }
  
  char buffer[1024];
  stringstream ss;
  cout << "Command output for '" << command.str() << "':" << endl;
  while (fgets(buffer, sizeof buffer, fpipe)) {
    cout << buffer;
    ss << buffer;
  }
  cout << endl;
  
  pclose(fpipe);

  string output(ss.str());
  boost::regex thumbnailRegex("Writing thumbnail to: (.*)$");
  boost::smatch thumbnailMatch;
  boost::regex videoRegex("Merging formats into \"(.*mp4)\"$");
  boost::smatch videoMatch;
  MusicVideo* musicVideo = new MusicVideo();
  vector<string> lines;
  boost::split(lines, output, boost::is_any_of("\n"));
  for (string line : lines) {
    if (boost::regex_search(line, thumbnailMatch, thumbnailRegex)) {
      stringstream ssTn;
      ssTn << mvArtistDir << "/" << thumbnailMatch[1];
      musicVideo->setThumbnailFilePath(ssTn.str());
    } else if (boost::regex_search(line, videoMatch, videoRegex)) {
      stringstream ssMv;
      ssMv << mvArtistDir << "/" << videoMatch[1];
      musicVideo->setFilePath(ssMv.str());
    }
  }
  if (musicVideo->getFilePath().empty()) {
    delete musicVideo;
    cerr << "Did not find music video file from youtube-dl output." <<endl;
    return NULL;
  }

  // remove special chars from files
  // TODO remove if --restrict-filenames works
  musicVideo->setFilePath(removeSpecialCharsFromPath(musicVideo->getFilePath()));
  musicVideo->setThumbnailFilePath(removeSpecialCharsFromPath(musicVideo->getThumbnailFilePath()));

  // remove base path
  musicVideo->setFilePath(boost::algorithm::ireplace_first_copy(musicVideo->getFilePath(), SoulSifterSettings::getInstance().get<string>("mv.dir"), ""));
  musicVideo->setThumbnailFilePath(boost::algorithm::ireplace_first_copy(musicVideo->getThumbnailFilePath(), SoulSifterSettings::getInstance().get<string>("mv.dir"), ""));
  
  musicVideo->setSongId(song->getId());
  musicVideo->save();
  return musicVideo;
}

}  // namespace soulsifter
}  // namespace dogatech

