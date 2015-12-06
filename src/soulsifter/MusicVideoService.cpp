#include "MusicVideoService.h"

#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <vector>

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>

#include "Album.h"
#include "BasicGenre.h"
#include "Song.h"
#include "MusicVideo.h"

using namespace std;

namespace dogatech {
namespace soulsifter {

MusicVideo* MusicVideoService::associateYouTubeVideo(const Song* const song, const string& id) {
  cout << "Associate YouTube video " << id << " with song " << song->getId() << endl;

  boost::filesystem::path mvBasePath("/Users/dogatech/Music/mv");  // TODO as a setting
  if (!boost::filesystem::exists(mvBasePath) || !boost::filesystem::is_directory(mvBasePath)) {
    cerr << "Music video base path does not exist. " << mvBasePath << endl;
    return NULL;
  }

  string mvArtistDir;
  {
    stringstream ss;
    ss << mvBasePath.string() << "/" << song->getAlbum()->getBasicGenre()->getName() << "/" << song->getArtist();
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
  command << "youtube-dl --write-thumbnail -k www.youtube.com/watch?v=" << id;
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
  boost::regex videoRegex("[download] Destination: (.*).mp4$");
  boost::smatch videoMatch;
  MusicVideo* musicVideo = new MusicVideo();
  vector<string> lines;
  boost::split(lines, output, boost::is_any_of("\n"));
  for (string line : lines) {
    if (boost::regex_search(line, thumbnailMatch, thumbnailRegex)) {
      musicVideo->setThumbnailFilePath(thumbnailMatch[1]);
    } else if (boost::regex_search(line, videoMatch, videoRegex)) {
      musicVideo->setFilePath(videoMatch[1]);
    }
  }
  if (musicVideo->getFilePath().empty()) {
    delete musicVideo;
    cerr << "Did not find music video file from youtube-dl output." <<endl;
    return NULL;
  }
  
  musicVideo->setSongId(song->getId());
  musicVideo->save();
  return musicVideo;
}

}  // namespace soulsifter
}  // namespace dogatech

