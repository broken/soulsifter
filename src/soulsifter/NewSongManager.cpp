#include "NewSongManager.h"

#include <iostream>
#include <string>
#include <vector>

#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>

#include "Album.h"
#include "AlbumPart.h"
#include "FilesToAdd.h"
#include "MusicManager.h"
#include "Song.h"

using namespace boost;
using namespace std;

namespace dogatech {
namespace soulsifter {

NewSongManager::NewSongManager()
    : hasMovedFile(false),
      filesToAdd(NULL) {
}

NewSongManager::~NewSongManager() {
  delete filesToAdd;
}

void NewSongManager::import(const vector<string>& filepaths) {
  delete filesToAdd;
  filesToAdd = new FilesToAdd();
  hasMovedFile = false;
  vector<filesystem::path> paths;
  transform(filepaths.begin(), filepaths.end(), back_inserter(paths), [](const string& fp) { return filesystem::path(fp); });
  preprocessAllFiles(paths);
  //loadCover();
  //[fileUrls removeAllObjects];
  // loadNextSong();
}

// This was ported from TagInfoController. In there I had a TODO to move this over
// to the FilesToAdd object.
void NewSongManager::preprocessAllFiles(const vector<filesystem::path>& filepaths) {
  
  // TODO So I'd like to do this all in the FilesToAdd class, and should slowly move this over, but
  // I don't want to rewrite a lot of code, so I'll leverage this until porting the code over
  // to c++.
  for (const filesystem::path& filepath : filepaths) {

    // skip files starting with period
    if (filepath.filename().string().at(0) == '.') {
      cout << "skipping " << filepath << endl;
      continue;
    }
    
    // if file is directory, enumerate over it and add files
    if (filesystem::is_directory(filepath)) {
      vector<filesystem::path> dirContents;
      copy(filesystem::directory_iterator(filepath), filesystem::directory_iterator(), back_inserter(dirContents));
      filesToTrash.push_back(filepath);
      preprocessAllFiles(dirContents);
      continue;
    }
    
    // TODO unarchive zips & rars, adding extracted files
    /*if ([[NSPredicate predicateWithFormat:@"self matches[c] \".+\\.part\\d+\\.rar$\""] evaluateWithObject:[filepath lastPathComponent]]) {
      if ([[filepath path] hasSuffix:@".part1.rar"]) {
        [self preprocessAllFiles:[NSArray arrayWithObject:[ArchiveUtil unrarFile:filepath]]];
      }
      [filesToTrash addObject:filepath];
      continue;
    } else if ([[filepath pathExtension] isEqualToString:@"rar"]) {
      [self preprocessAllFiles:[NSArray arrayWithObject:[ArchiveUtil unrarFile:filepath]]];
      [filesToTrash addObject:filepath];
      continue;
    } else if ([[filepath pathExtension] isEqualToString:@"zip"]) {
      [self preprocessAllFiles:[NSArray arrayWithObject:[ArchiveUtil unzipFile:filepath]]];
      [filesToTrash addObject:filepath];
      continue;
    }*/
    
    // let FilesToAdd do the rest
    filesToAdd->addFile(filepath.string());
  }
}

bool NewSongManager::nextSong(Song* updatedSong, Song* originalSong) {
  // Try to pull the next songs first if there is one.
  string* path = NULL;
  if (filesToAdd->pullSong(&path)) {
    originalSong->clear();
    originalSong->setFilepath(*path);
    MusicManager::getInstance().readTagsFromSong(originalSong);
    MusicManager::getInstance().updateSongWithChanges(*originalSong, updatedSong);

    // TODO do this in a different thread and have it update the UI when finished
    // TODO this goes in caller
    /*const Bpms *bpms = AudioAnalyzer::analyzeBpm(updatedSong);
    if (!updatedSong->getBpm().empty()) [bpm setStringValue:[NSString stringWithFormat:@"%.2f",bpms->candidate[0]]];
    [bpmAnalyzed setStringValue:[NSString stringWithFormat:@"%.2f, %.2f, %.2f",bpms->candidate[0],bpms->candidate[1],bpms->candidate[2]]];
    delete bpms;
    
    const Keys *keys = AudioAnalyzer::analyzeKey(updatedSong);
    if (updatedSong->getTonicKeys().empty()) [key setStringValue:[NSString stringWithFormat:@"%s",keys->candidate[0].first.c_str()]];
    stringstream ss;
    boost::format fmt("%.1f");
    for (int i = 0; i < keys->candidate.size() && keys->candidate[i].second > 20; ++i) {
      ss << keys->candidate[i].first.c_str() << "(" << fmt % keys->candidate[i].second << "), ";
    }
    [keyAnalyzed setStringValue:[NSString stringWithFormat:@"%s", ss.str().c_str()]];
    delete keys;*/
    return true;
  }
  
  if (filesToAdd->pullFile(&path)) {
    // TODO only move image if a song has been moved or a song has not been skipped
    if (hasMovedFile) {
      // TODO move to last parent (no subalbums)
      // straight move image to last directory
      MusicManager::getInstance().moveImage(*path);
      // TODO should this really happen here?
      // update album with cover art
      if (filesToAdd->coverPath() && !strcasecmp(path->c_str(), filesToAdd->coverPath()->c_str())) {
        MusicManager::getInstance().updateLastSongAlbumArtWithImage(*path);
      }
    }
    delete path;
    return nextSong(updatedSong, originalSong);  // should never return true
  }
  
  // TODO trash files if desired
  /*for (auto& fileToTrash : filesToTrash) {
    NSLog(@"trashing file %@", fileToTrash);
    [[NSFileManager defaultManager] trashItemAtURL:fileToTrash resultingItemURL:nil error:nil];
  }*/
  filesToTrash.clear();
  return false;
}

bool NewSongManager::processSong(Song* song) {
  // TODO this validation should be in fe
  // TODO unable to move file if any of these are blank
  /*if ([genreComboBox stringValue] == nil || [[genreComboBox stringValue] length] <= 0 ||
      [artist stringValue] == nil || [[artist stringValue] length] <= 0 ||
      [album stringValue] == nil || [[album stringValue] length] <= 0) {
    NSBeep();
    return false;
  }*/
    
  // update tag
  MusicManager::getInstance().writeTagsToSong(song);
  
  // move file
  MusicManager::getInstance().moveSong(song);
  hasMovedFile = true;
  
  // save song
  if (!song->getId()) {
    song->setDateAddedToNow();
    song->save();
    MusicManager::getInstance().setNewSongChanges(*song);
  } else {
    song->update();
  }

  return true;
}

// TODO
void NewSongManager::trashMusicFile(Song* song) {
  if (!processSong(song)) return;
    
  // NSFileManager *fileManager = [NSFileManager defaultManager];
  // NSURL *oldPath = [NSURL fileURLWithPath:[NSString stringWithUTF8String:song->getFilepath().c_str()]];
  // std::string newPath = song->getFilepath() + ".txt";
  // if (![fileManager createFileAtPath:[NSString stringWithUTF8String:newPath.c_str()]
  //                           contents:nil
  //                         attributes:nil]) {
  //   NSBeep();
  //   // TODO can't tell by id, then how do we tell?
  //   if (!song->getId()) {
  //     delete song;
  //   }
  //   return;
  // }
    
  // song->setTrashed(true);
  // song->setFilepath(newPath);
  // song->update();
    
  // [fileManager trashItemAtURL:oldPath resultingItemURL:nil error:nil];
  
  // // TODO can't tell by id, then how do we tell?
  // if (!song->getId()) {
  //   delete song;
  // }
  
  // [self loadNextSong];
}

string NewSongManager::coverImagePath() const {
  return *filesToAdd->coverPath();
}

}  // namespace soulsifter
}  // namespace dogatech

