//
//  MusicManager.m
//  soul-sifter
//
//  Created by Robby Neale on 4/28/12.
//  Copyright (c) 2012 Dogatech. All rights reserved.
//
//  Core that manages possible tags for the music file. This is not multi-thread safe.
//
//  At some point I'd like to upgrade this to C++11, but it'll require getting libs compiled
//  for it as well. In cases I used homebrew, update the formula to include the C++11 compiler:
//  ENV['CXXFLAGS'] = " -std=c++11 -stdlib=libc++"

#include "MusicManager.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <regex.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <vector>

#include <boost/algorithm/string/predicate.hpp>
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>
#include <taglib/apetag.h>
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
#include "BasicGenre.h"
#include "Song.h"
#include "SoulSifterSettings.h"
#include "Style.h"
#include "TagService.h"

using namespace boost;
using namespace std;

namespace dogatech {
namespace soulsifter {

# pragma mark private helpers

namespace {

  const string FEATURING_REGEX = " [(]?[Ff](eaturing|t[.]?|eat[.]?) (.*?)[)]?$";

  string* cleanDirName(string* name) {
    std::replace(name->begin(), name->end(), '/', '-');
    std::replace(name->begin(), name->end(), ':', ' ');
    return name;
  }

}  // namespace

# pragma mark initialization

MusicManager::MusicManager() :
lastParsedSong(NULL),
lastSongFixed(NULL),
artistToGenre(1600),
albumSubPathForImage() {
}

MusicManager::~MusicManager() {
    // TODO delete artistToGenre
}

# pragma mark tagging

void MusicManager::readTagsFromSong(Song* song) {
    if (!song->getAlbum()) {
        Album album;
        song->setAlbum(album);
    }

    string songFilepath = song->getFilepath();
    if (!boost::filesystem::exists(songFilepath)) {
      songFilepath = SoulSifterSettings::getInstance().get<string>("music.dir") + song->getFilepath();
      if (!boost::filesystem::exists(songFilepath)) {
        cerr << "unable to find song: " << song->getFilepath() << endl;
      }
    }
  
    if (boost::algorithm::iends_with(song->getFilepath(), ".mp3")) {
        TagLib::MPEG::File f(songFilepath.c_str());
        TagLib::ID3v1::Tag* id3v1 = f.ID3v1Tag();
        if (id3v1) {
            stringstream ss;
            if (id3v1->title() != TagLib::String::null) song->setTitle(id3v1->title().to8Bit());
            if (id3v1->artist() != TagLib::String::null) song->setArtist(id3v1->artist().to8Bit());
            if (id3v1->album() != TagLib::String::null) song->getAlbum()->setName(id3v1->album().to8Bit());
            if (id3v1->comment() != TagLib::String::null) song->setComments(id3v1->comment().to8Bit());
            //TODO if (id3v1->genre() != TagLib::String::null) song->setGenre(id3v1->genre().to8Bit());
            if (id3v1->year() != 0) song->getAlbum()->setReleaseDateYear(id3v1->year());
            if (id3v1->track() != 0) {
                ss.clear();
                ss << id3v1->track();
                song->setTrack(ss.str());
            }
        }
        TagService::readId3v2Tag(song);
    } else if (boost::algorithm::iends_with(song->getFilepath(), ".m4a") ||
               boost::algorithm::iends_with(song->getFilepath(), ".mp4") ||
               boost::algorithm::iends_with(song->getFilepath(), ".aac") ||
               boost::algorithm::iends_with(song->getFilepath(), ".alac")) {
      TagLib::MP4::File f(songFilepath.c_str());
      TagLib::MP4::Tag* tag = f.tag();
      if (tag) {
        stringstream ss;
        if (tag->title() != TagLib::String::null) song->setTitle(tag->title().to8Bit());
        if (tag->artist() != TagLib::String::null) song->setArtist(tag->artist().to8Bit());
        if (tag->track() != 0) song->setTrack((ostringstream() << tag->track()).str());
        if (tag->album() != TagLib::String::null) song->getAlbum()->setName(tag->album().to8Bit());
        if (tag->comment() != TagLib::String::null) song->setComments(tag->comment().to8Bit());
        if (tag->year() != 0) song->getAlbum()->setReleaseDateYear(tag->year());
      }
      TagService::readId3v2Tag(song);
    }
}

void MusicManager::writeTagsToSong(Song* song) {
  delete lastSongFixed;
  lastSongFixed = new Song(*song);

  TagService::writeId3v2Tag(song);
}
    
# pragma mark monitor changes
  
  void MusicManager::updateSongWithChanges(const Song& song, Song* updatedSong) {
    *updatedSong = song;
    
    // compare with last
    if (lastParsedSong && lastSongFixed) {
      if (!song.getArtist().compare(lastParsedSong->getArtist())) {
        // featuring normally comes from title field rather than artist,
        // so we remove it since it rarely matches in practice.
        boost::regex featRegex(" [(]ft[.] .*");
        updatedSong->setArtist(boost::regex_replace(lastSongFixed->getArtist(), featRegex, ""));
      }
      if (song.getTrack().length() == 0) {
        int trackNum = atoi(lastSongFixed->getTrack().c_str());  // returns 0 on error
        if (trackNum > 0) {
          ++trackNum;
          if (lastSongFixed->getTrack().length() > 1 && trackNum < 10) {
            updatedSong->setTrack('0' + (ostringstream() << trackNum).str());
          } else {
            updatedSong->setTrack((ostringstream() << trackNum).str());
          }
        }
      }
      // I created these 'Once' methods so you can retrieve model without saving the pointer and method remains const
      Album* songAlbum = song.getAlbumOnce();
      AlbumPart* songAlbumPart = song.getAlbumPartOnce();
      // we shouldn't auto set track title b/c it changes so much
      // nor should we auto update remixer
      if (!songAlbum->getArtist().compare(lastParsedSong->getAlbum()->getArtist())) {
        updatedSong->getAlbum()->setArtist(lastSongFixed->getAlbum()->getArtist());
      }
      if (!songAlbum->getName().compare(lastParsedSong->getAlbum()->getName())) {
        updatedSong->getAlbum()->setName(lastSongFixed->getAlbum()->getName());
      }
      updatedSong->getAlbum()->setMixed(lastSongFixed->getAlbum()->getMixed());
      if (!songAlbum->getLabel().compare(lastParsedSong->getAlbum()->getLabel())) {
        updatedSong->getAlbum()->setLabel(lastSongFixed->getAlbum()->getLabel());
      }
      if (!songAlbum->getCatalogId().compare(lastParsedSong->getAlbum()->getCatalogId())) {
        updatedSong->getAlbum()->setCatalogId(lastSongFixed->getAlbum()->getCatalogId());
      }
      if (songAlbum->getReleaseDateYear() == lastParsedSong->getAlbum()->getReleaseDateYear()) {
        updatedSong->getAlbum()->setReleaseDateYear(lastSongFixed->getAlbum()->getReleaseDateYear());
      }
      if (songAlbum->getReleaseDateMonth() == lastParsedSong->getAlbum()->getReleaseDateMonth()) {
        updatedSong->getAlbum()->setReleaseDateMonth(lastSongFixed->getAlbum()->getReleaseDateMonth());
      }
      if (songAlbum->getReleaseDateDay() == lastParsedSong->getAlbum()->getReleaseDateDay()) {
        updatedSong->getAlbum()->setReleaseDateDay(lastSongFixed->getAlbum()->getReleaseDateDay());
      }
      if (songAlbum->getBasicGenreId() == lastParsedSong->getAlbum()->getBasicGenreId()) {
        updatedSong->getAlbum()->setBasicGenreId(lastSongFixed->getAlbum()->getBasicGenreId());
      }
      if (song.getComments().size() > 0 && !song.getComments().compare(lastParsedSong->getComments())) {
        updatedSong->setComments(lastSongFixed->getComments());
      }
      // we may not always have an album part
      if (songAlbumPart && lastParsedSong->getAlbumPart()) {
        if (!songAlbumPart->getName().compare(lastParsedSong->getAlbumPart()->getName()) &&
            !songAlbumPart->getPos().compare(lastParsedSong->getAlbumPart()->getPos())) {
          if (lastSongFixed->getAlbumPart()) {
            updatedSong->getAlbumPart()->setName(lastSongFixed->getAlbumPart()->getName());
            updatedSong->getAlbumPart()->setPos(lastSongFixed->getAlbumPart()->getPos());
          } else {
            updatedSong->setAlbumPartId(0);
          }
        } else if (!songAlbumPart->getName().compare(lastParsedSong->getAlbumPart()->getName()) &&
                   lastSongFixed->getAlbumPart()) {
          updatedSong->getAlbumPart()->setName(lastSongFixed->getAlbumPart()->getName());
        } else if (!songAlbumPart->getPos().compare(lastParsedSong->getAlbumPart()->getPos()) &&
                   lastSongFixed->getAlbumPart()) {
          updatedSong->getAlbumPart()->setPos(lastSongFixed->getAlbumPart()->getPos());
        }
      }
    }
    
    // strip featuring from the title and add it to the artist.
    moveFeaturing(updatedSong);
    // copy remixer
    copyRemixer(updatedSong);
    // add an album artist if one does not exist
    if (updatedSong->getAlbum()->getArtist().empty()) {
      boost::regex featRegex(FEATURING_REGEX);
      boost::smatch featMatch;
      if (boost::regex_search(updatedSong->getArtist(), featMatch, featRegex, boost::match_extra)) {
        updatedSong->getAlbum()->setArtist(featMatch[1]);
      }
    }
    // add an album name if one does not exist
    if (updatedSong->getAlbum()->getName().empty()) {
      updatedSong->getAlbum()->setName(updatedSong->getTitle());
    }
    // remove album part if there is just one
    if (updatedSong->getAlbumPart() && !updatedSong->getAlbumPart()->getPos().compare("1/1")) {
      updatedSong->getAlbumPart()->setPos("");
    }
    
    delete lastParsedSong;
    lastParsedSong = new Song(song);
  }
    
    void MusicManager::setNewSongChanges(const Song& song) {
        delete lastSongFixed;
        lastSongFixed = new Song(song);
    }
    
    void MusicManager::updateLastSongAlbumArtWithImage(const string& img) {
        if (!lastSongFixed) return;
        
        // code taken from moveImage(img)
        stringstream destpath;
        boost::filesystem::path src(img);
        destpath << albumSubPathForImage << "/" << src.filename().string();
        
        Album* album = lastSongFixed->getAlbum();
        album->setCoverFilepath(destpath.str());
        album->update();
    }
                
# pragma mark paths
 
string MusicManager::getCopyToPath() {
    filesystem::path dir(SoulSifterSettings::getInstance().get<string>("music.dir"));
    if (filesystem::exists(dir) && filesystem::is_directory(dir)) {
        return SoulSifterSettings::getInstance().get<string>("music.dir");
    }
    filesystem::path staging(SoulSifterSettings::getInstance().get<string>("staging.dir"));
    if (filesystem::exists(staging) && filesystem::is_directory(staging)) {
        return SoulSifterSettings::getInstance().get<string>("staging.dir");
    }
    return "";
}

// TODO shouldn't need to lower case full path
// TODO removed use of stagingPath. Add back feature?
bool MusicManager::moveSong(Song* song) {
    try {
        string albumPath;
        {
            ostringstream ssdirpath;
            string albumartist = song->getAlbum()->getArtist().length() > 0 ? song->getAlbum()->getArtist() : "_compilations_";
            string albumname = song->getAlbum()->getName();
            ssdirpath << song->getAlbum()->getBasicGenre()->getName() << "/" << *cleanDirName(&albumartist) << "/" << *cleanDirName(&albumname);
            albumSubPathForImage = ssdirpath.str();
            transform(albumSubPathForImage.begin(), albumSubPathForImage.end(), albumSubPathForImage.begin(), ::tolower);
            if (song->getAlbumPart() && song->getAlbumPart()->getName().length()) {
                string part = song->getAlbumPart()->getName();
                ssdirpath << "/" << *cleanDirName(&part);
            }
            albumPath = ssdirpath.str();
        }
        // create directory
        transform(albumPath.begin(), albumPath.end(), albumPath.begin(), ::tolower);
        string fullAlbumPath = SoulSifterSettings::getInstance().get<string>("music.dir") + albumPath;
        filesystem::path dir(fullAlbumPath);
        if (!filesystem::exists(dir)) {
            if (!filesystem::create_directories(dir)) {
                cerr << "Error occurred while trying to create directory " << fullAlbumPath << endl;
                return false;
            }
        } else if (!filesystem::is_directory(dir)) {
            cerr << "Cannot move file b/c destination is not a directory " << fullAlbumPath << endl;
            return false;
        }
    
        // move file to dest
        boost::filesystem::path src(song->getFilepath());
        string songPath = albumPath + "/" + src.filename().string();
        stringstream destPath;
        destPath << SoulSifterSettings::getInstance().get<string>("music.dir") << songPath;
        boost::filesystem::path dest(destPath.str());
        boost::filesystem::rename(src, dest);
        
        // update song path
        song->setFilepath(songPath);
    
        return true;  //TODO better testing
    } catch (const filesystem::filesystem_error& ex) {
        cerr << ex.what() << '\n';
    }
    return false;
}

    // TODO removed use of stagingPath. Add back feature?
    bool MusicManager::moveImage(const string& img) {
        try {
            // move file to dest
            stringstream destpath;
            boost::filesystem::path src(img);
            destpath << SoulSifterSettings::getInstance().get<string>("music.dir") << albumSubPathForImage << "/" << src.filename().string();
            boost::filesystem::path dest(destpath.str());
            boost::filesystem::rename(src, dest);
            
            return true;
        } catch (const filesystem::filesystem_error& ex) {
            cerr << ex.what() << '\n';
        }
        return false;
    }
    
/*
// TODO remove old directories from staging
- (void)populateStagingDirectory {
    NSLog(@"musicManager.populateStagingDirectory");
    
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
    NSFileManager *fileManager = [NSFileManager defaultManager];
    NSError *error;
    
    // verify paths exist
    NSString *path;
    if (![self getCopyToPath:&path]) {
        return;
    }
    
    // enumerate over path; releasing values with each iteration for better memory management
	NSDirectoryEnumerator *enumerator  = [fileManager enumeratorAtPath:path];
	NSString *file;
	while (file = [enumerator nextObject]) {
		NSDictionary *fileAttribs = [enumerator fileAttributes];
		
        // we process all directories that do not start with a period
		if ([fileAttribs objectForKey:NSFileType] == NSFileTypeDirectory) {
			if ([file characterAtIndex:0] == '.') {
				continue;
			}
            NSURL *path = [NSURL fileURLWithPathComponents:
                           [NSArray arrayWithObjects:
                            [userDefaults stringForKey:UDStagingPath], file , nil]];
            NSLog(@"creating directory: %@", path);
            if (![fileManager createDirectoryAtURL:path withIntermediateDirectories:YES attributes:nil error:&error]) {
                NSString *msg = [NSString stringWithFormat:@"Error occurred while trying to create directory: %@", error];
                NSAssert(NO, msg);
            }
		}
	}
}
*/
    void MusicManager::flushStagingDirectory() {
        try {
            filesystem::path musicPath(SoulSifterSettings::getInstance().get<string>("music.dir"));
            if (!filesystem::exists(musicPath) || !filesystem::is_directory(musicPath)) {
                cerr << "music path does not exist or is not a directory: " << musicPath.string() << endl;
                return;
            }
            filesystem::path stagingPath(SoulSifterSettings::getInstance().get<string>("staging.dir"));
            if (!filesystem::exists(stagingPath) || !filesystem::is_directory(stagingPath)) {
                cerr << "staging path does not exist or is not a directory: " << stagingPath.string() << endl;
                return;
            }
            
            // enumerate over paths
            unsigned long relativePathPosition = stagingPath.string().length();
            filesystem::recursive_directory_iterator end; // default ctor yields past the end
            for (filesystem::recursive_directory_iterator it(stagingPath); it != end; ++it) {
                if (filesystem::is_directory(it->status())) {
                    // do nothing
                } else if (filesystem::is_regular_file(it->status())) {
                    if (it->path().filename().string()[0] == '.') {
                        continue;
                    }
                    // create directory if it doesn't exist
                    string subPath = it->path().parent_path().string().substr(relativePathPosition);
                    filesystem::path dir(musicPath.string() + subPath);
                    if (!filesystem::exists(dir)) {
                        if (!filesystem::create_directories(dir)) {
                            cerr << "Error occurred while trying to create directory " << dir.string() << endl;
                            continue;
                        }
                    } else if (!filesystem::is_directory(dir)) {
                        cerr << "Cannot move file b/c destination is not a directory " << dir.string() << endl;
                        continue;
                    }
                    // move file
                    stringstream destpath;
                    destpath << dir.string() << "/" << it->path().filename().string();
                    filesystem::path dest(destpath.str());
                    cerr << "Moving " << it->path().string() << " to " << dest.string() << endl;
                    filesystem::copy(it->path(), dest);
                    if (filesystem::exists(dest)) {
                        filesystem::path trash("/Users/rneale/.Trash/" + it->path().filename().string());
                        filesystem::rename(it->path(), trash);
                    }
                } else {
                    cerr << "wtf is this? " << it->path().string() << endl;
                }
            }
        } catch (const filesystem::filesystem_error& ex) {
            cerr << ex.what() << '\n';
        }
    }

# pragma mark db updates

void MusicManager::updateDatabaseBasicGenres() {
    // TODO the artists to genres
    try {
        filesystem::path path(getCopyToPath());
        if (!filesystem::exists(path)) {
            cerr << "Cannot update db basic genres because path does not exist: " << getCopyToPath() << endl;
            return;
        } else if (!filesystem::is_directory(path)) {
            cerr << "Cannot update db basic genres because path is not a directory: " << getCopyToPath() << endl;
            return;
        }
        
        filesystem::directory_iterator end; // default ctor yields past the end
        for (filesystem::directory_iterator it(path); it != end; ++it) {
            if (filesystem::is_directory(it->status())) {
                string filename = it->path().filename().string();
                const BasicGenre *genre = BasicGenre::findByName(filename);
                if (!genre) {
                    BasicGenre *basicGenre = new BasicGenre();
                    basicGenre->setName(filename);
                    basicGenre->save();
                    genre = BasicGenre::findByName(filename);
                }
                for (filesystem::directory_iterator jt(it->path()); jt != end; ++jt) {
                    string artist = jt->path().filename().string();
                    artistToGenre[artist] = genre;
                }
            }
        }
    } catch (const filesystem::filesystem_error& ex) {
        cerr << ex.what() << '\n';
    }
}
   
const BasicGenre* MusicManager::findBasicGenreForArtist(const string& artist) {
    return artistToGenre[artist];
}

bool MusicManager::splitArtistAndTitle(const string& songString, Song* updatedSong) {
  if (updatedSong->getArtist().length() > 0 || updatedSong->getTitle().length() > 0) return false;
  boost::regex splitRegex("^(.+) - (.+)$");
  boost::smatch match;
  if (boost::regex_search(songString, match, splitRegex, boost::match_extra)) {
    updatedSong->setArtist(match[1]);
    updatedSong->setTitle(match[2]);
    return true;
  }
  return false;
}

bool MusicManager::moveFeaturing(Song* updatedSong) {
  boost::regex featRegex(FEATURING_REGEX);
  boost::smatch featMatch;
  if (boost::regex_search(updatedSong->getTitle(), featMatch, featRegex, boost::match_extra)) {
    updatedSong->setArtist(updatedSong->getArtist() + " (ft. " + featMatch[2] + ")");
    updatedSong->setTitle(boost::regex_replace(updatedSong->getTitle(), featRegex, ""));
    return true;
  }
  return false;
}

bool MusicManager::copyRemixer(Song* updatedSong) {
  boost::regex rmxrRegex("[(](.+) ([Rr]emix|[Rr]mx|[Mm]ix|[Rr]efix|[Dd]ub)[)]$");
  boost::smatch rmxrMatch;
  if (boost::regex_search(updatedSong->getTitle(), rmxrMatch, rmxrRegex, boost::match_extra) &&
      updatedSong->getRemixer().length() == 0) {
    string remixer(rmxrMatch[1]);
    if (!!remixer.compare("original") && !!remixer.compare("Original")) {
      updatedSong->setRemixer(remixer);
      return true;
    }
  }
  return false;
}
                
 /*
# pragma mark paths accessors

- (NSArray *)basicGenres {
    NSLog(@"musicManager.basicGenreList");
    if (!basicGenres) {
        [self initializePathMembers];
    }
    return basicGenres;
}

@end*/
}
}
