#include "TagService.h"

#include <cmath>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>
#include <taglib/attachedpictureframe.h>
#include <taglib/fileref.h>
#include <taglib/id3v2frame.h>
#include <taglib/id3v1tag.h>
#include <taglib/id3v2tag.h>
#include <taglib/mp4file.h>
#include <taglib/mpegfile.h>
#include <taglib/popularimeterframe.h>
#include <taglib/tbytevector.h>
#include <taglib/textidentificationframe.h>
#include <taglib/tpropertymap.h>
#include <taglib/tstring.h>
#include <taglib/tstringlist.h>

#include "Album.h"
#include "AlbumPart.h"
#include "DTVectorUtil.h"
#include "SearchUtil.h"
#include "Song.h"
#include "SoulSifterSettings.h"
#include "Style.h"

namespace dogatech {
namespace soulsifter {

namespace {

int canonicalizeBpm(const int bpm) {
  if (bpm <= 0) return 0;
  if (bpm < 75) return canonicalizeBpm(bpm << 1);
  if (bpm >= 150) return canonicalizeBpm(bpm >> 1);
  return bpm;
}

int canonicalizeBpm(const string& bpm) {
  return canonicalizeBpm(std::atoi(bpm.c_str()));
}
    
const string getId3v2Text(TagLib::ID3v2::Tag* id3v2, const char* name) {
  TagLib::ID3v2::FrameList frameList = id3v2->frameListMap()[name];
  return frameList.isEmpty() ? "" : frameList.front()->toString().to8Bit();
}

bool readId3v2TagAttributes(Song* song, TagLib::ID3v2::Tag* id3v2) {
  std::cout << "reading tags for song " << song->getId() << std::endl;
  bool updated = false;
  if (!id3v2 || !song) {
    return updated;
  }
  // bpm
  const string bpm = getId3v2Text(id3v2, "TBPM");
  if (canonicalizeBpm(bpm) != canonicalizeBpm(song->getBpm())) {
    std::cout << "updating song " << song->getId()
         << " bpm from " << song->getBpm()
         << " to " << bpm << std::endl;
    if (abs(canonicalizeBpm(bpm) - canonicalizeBpm(song->getBpm())) > 3) {
      std::cerr << "BPM for song " << song->getId() << " was WAY off!" << std::endl;
    }
    if (canonicalizeBpm(bpm) > 0) {
      song->setBpm(bpm);
      updated = true;
    }
  }
  // energy
  const string grpTag = getId3v2Text(id3v2, "TIT1");
  boost::regex grpRegex("^(\\d+(?![\\w\\d]))?(?: - )?(?:1?\\d[AB] (.{1,3}))?$");
  boost::smatch grpMatch;
  string oldKey;
  if (boost::regex_search(grpTag, grpMatch, grpRegex, boost::match_default)) {
    string energystr = grpMatch[1];
    oldKey = grpMatch[2];
    std::cout << "song " << song->getId() << " from " << grpTag
              << " found energy " << energystr
              << " and key " << oldKey << std::endl;
    int energy = std::atoi(energystr.c_str());
    if (energy != song->getEnergy()) {
      std::cout << "updating song " << song->getId()
                << " energy from " << song->getEnergy()
                << " to " << energy << std::endl;
      if (energy > 0) {
        song->setEnergy(energy);
        updated = true;
      }
    }
  }
  // key
  const string keylist = getId3v2Text(id3v2, "TKEY");
  std::set<std::string> keys;
  boost::split(keys, keylist, boost::is_any_of("\\"));
  if (keys != song->getTonicKeys()) {
    std::cout << "updating song " << song->getId()
         << " keys from " << boost::algorithm::join(song->getTonicKeys(), ",") << " or " << oldKey
         << " to " << boost::algorithm::join(keys, ",") << std::endl;
    if (keys.size() > 0) {
      // convert old key from sharp to flat
      if (oldKey.length() >= 2 && oldKey[1] == '#') {
        if (oldKey[0] == 'G') oldKey[0] = 'A';
        else oldKey[0] = oldKey[0] + 1;
        oldKey[1] = 'b';
      }
      song->setTonicKey(oldKey);
      song->setTonicKeys(keys);
      updated = true;
    }
  }

  return updated;
}

bool readId3v2TagAttributes(Song* song) {
  TagLib::MPEG::File f((SoulSifterSettings::getInstance().get<string>("music.dir") + song->getFilepath()).c_str());
  TagLib::ID3v2::Tag* id3v2 = f.ID3v2Tag();  // still owned by file
  return readId3v2TagAttributes(song, id3v2);
}

}  // namespace
  
void TagService::readId3v2Tag(Song* song) {
  string songFilepath = song->getFilepath();
  if (!boost::filesystem::exists(songFilepath)) {
    songFilepath = SoulSifterSettings::getInstance().get<string>("music.dir") + song->getFilepath();
    if (!boost::filesystem::exists(songFilepath)) {
      cerr << "unable to find song: " << song->getFilepath() << endl;
    }
  }
  TagLib::MPEG::File f(songFilepath.c_str());
  TagLib::ID3v2::Tag* id3v2 = f.ID3v2Tag();
  if (!id3v2) {
    return;
  }

    if (id3v2->artist() != TagLib::String::null) song->setArtist(id3v2->artist().to8Bit());
    song->setTrack(getId3v2Text(id3v2, "TRCK"));
    if (id3v2->title() != TagLib::String::null) song->setTitle(id3v2->title().to8Bit());
    song->setRemixer(getId3v2Text(id3v2, "TPE4"));
    song->getAlbum()->setArtist(getId3v2Text(id3v2, "TPE2"));
    if (id3v2->album() != TagLib::String::null) song->getAlbum()->setName(id3v2->album().to8Bit());
    song->getAlbum()->setLabel(getId3v2Text(id3v2, "TPUB"));
    song->getAlbum()->setCatalogId(getId3v2Text(id3v2, "TCID"));
    if (id3v2->year() != 0) song->getAlbum()->setReleaseDateYear(id3v2->year());
    //TODO if (id3v2->genre() != TagLib::String::null) song->setGenre(id3v2->genre().to8Bit());
    if (id3v2->comment() != TagLib::String::null) song->setComments(id3v2->comment().to8Bit());
    
    TagLib::ID3v2::FrameList frameList = id3v2->frameListMap()["POPM"];
    if (!frameList.isEmpty()) {
      TagLib::ID3v2::PopularimeterFrame *popm = static_cast<TagLib::ID3v2::PopularimeterFrame*>(frameList.front());
      song->setRating(popm->rating());
    }
    
    // part of set
    const string pos = getId3v2Text(id3v2, "TPOS");
    if (pos.length() > 0) {
      if (!song->getAlbumPart()) {
        AlbumPart ap;
        song->setAlbumPart(ap);
      }
      song->getAlbumPart()->setAlbum(*song->getAlbum());
      song->getAlbumPart()->setPos(pos);
    }
    
    // string in the DDMM format
    const string date = getId3v2Text(id3v2, "TDAT");
    char *tmp = new char[3];
    tmp[0] = date[0];
    tmp[1] = date[1];
    tmp[2] = '\0';
    if (tmp[0] != '0' || tmp[1] != '0')
      song->getAlbum()->setReleaseDateDay(atoi(tmp));
    tmp[0] = date[2];
    tmp[1] = date[3];
    song->getAlbum()->setReleaseDateMonth(atoi(tmp));
    delete [] tmp;

  readId3v2TagAttributes(song, id3v2);
}

void TagService::updateSongAttributesFromTags() {
  std::cout << "updating song attributes from tags" << std::endl;

  // get max id
  vector<Style*> emptyStyles;
  vector<Song*> emptySongs;
  string query = "id:\"(select max(id) from songs)\"";
  vector<Song*>* songs = SearchUtil::searchSongs(query, 0, set<string>(), emptyStyles, emptySongs, 1);
  int maxId = 0;
  for (Song* song : *songs) {
    maxId = song->getId();
  }
  deleteVectorPointers(songs);

  // loop through songs
  int span = 100;
  for (int i = 0; i <= maxId; i += span) {
    stringstream ss;
    ss << "q:\"s.id >= " << i << "\" q:\"s.id < " << (i + span) << "\"";
    ss << " trashed:0";  // q:\"bpm is null\"";
    query = ss.str();
    songs = SearchUtil::searchSongs(query,  0, set<string>(), emptyStyles, emptySongs, span);

    for (Song* song : *songs) {
      if (readId3v2TagAttributes(song)) {
        std::cout << "updating song " << song->getId() << "'s attributes" << std::endl;
        song->update();
      }
    }
    deleteVectorPointers(songs);
  }
}
    
}  // namespace soulsifter
}  // namespace dogatech
