#include "GoogleMusicService.h"

#include <algorithm>
#include <regex.h>
#include <set>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>

#include <boost/algorithm/string/predicate.hpp>
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>
#include <g3log/g3log.hpp>
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
#include "DTVectorUtil.h"
#include "Playlist.h"
#include "PlaylistEntry.h"
#include "SearchUtil.h"
#include "Song.h"
#include "SoulSifterSettings.h"
#include "Style.h"
#include "TagService.h"

#include "/Users/dogatech/Development/open.src/gmusicapi-cpp/include/gmusicapi/Mobileclient.h"
#include "/Users/dogatech/Development/open.src/gmusicapi-cpp/include/gmusicapi/Module.h"

namespace dogatech {
namespace soulsifter {

namespace {

bool comparePlaylistEntries(PlaylistEntry* e1, PlaylistEntry* e2) {
  return e1->getPosition() < e2->getPosition();
}

}  // namespace

void GoogleMusicService::syncGoogleMusicPlaylists() {
  vector<Playlist*> *playlists = Playlist::findAll()->toVector();

  // create sets of song for each Google playlist
  std::unordered_map<std::string, std::vector<Song*>*> playlistsSongs;
  for (Playlist* playlist : *playlists) {
    if (playlist->getGmusicId().empty()) continue;
    std::vector<Song*> *songs = new std::vector<Song*>;
    playlistsSongs.insert(std::make_pair<>(std::string(playlist->getGmusicId()), songs));
    if (playlist->getQuery().empty()) {
      // populate songs from entries
      vector<PlaylistEntry*> *entries = PlaylistEntry::findByPlaylistId(playlist->getId())->toVector();
      std::sort(entries->begin(), entries->end(), comparePlaylistEntries);
      for (PlaylistEntry* entry : *entries) {
        songs->push_back(entry->getSong());
      }
      deleteVectorPointers(entries);
      delete(entries);
    } else {
      // populate songs from query
      const set<string> keys;
      const vector<Song*> songsToOmit;
      vector<Song*>* songs = SearchUtil::searchSongs(playlist->getQuery(), 0 /* bpm */, keys, playlist->getStyles(), songsToOmit, 200 /* limit */);
      playlistsSongs.insert(std::make_pair<>(std::string(playlist->getGmusicId()), songs));
    }
  }

  // compute differences of goldens with current
  try {
    GMusicApi::Module module;
    GMusicApi::Mobileclient mc(module);
    bool success = mc.login(SoulSifterSettings::getInstance().get<string>("google.email"), SoulSifterSettings::getInstance().get<string>("google.appKey"), "");
    if (!success) {
      std::cerr << "Unable to log into Google Music." << std::endl;
    } else {
          std::cout << "----------------------0------------------------";
      GMusicApi::PlaylistRange gmPlaylists = mc.get_all_user_playlist_contents();
          std::cout << "----------------------1------------------------";
      for (GMusicApi::Playlist&& gmPlaylist : gmPlaylists) {
          std::cout << "---------------------2-------------------------";
        if (gmPlaylist.deleted) {
          std::cout << "Playlist " << gmPlaylist.id << " deleted.";
          continue;
        }
        std::vector<GMusicApi::identifier> tracksToRemove;
        std::vector<Song*>* songs;
        std::unordered_map<std::string, std::vector<Song*>*>::const_iterator it = playlistsSongs.find(gmPlaylist.id);
        if (it == playlistsSongs.end()) {
          std::cout << "Playlist not local - " << gmPlaylist.id << std::endl;
          continue;
        } else {
          std::cout << "Found local playlist " << gmPlaylist.id << std::endl;
          songs = it->second;
        }
        for (GMusicApi::PlaylistEntry& track : gmPlaylist.tracks) {
          if (track.deleted) { 
            std::cout << "Track " << track.id << " deleted.";
            continue;
          }
          bool found = false;
          for (auto it = songs->begin(); it != songs->end(); ++it) {
            Song* song = *it;
            if (!song->getGoogleSongId().compare(track.id)) {
              std::cout << "Track " << track.id << " found.";
              found = true;
              songs->erase(it);
              delete(song);
              break;
            }
          }
          if (!found) {
            std::cout << "Track " << track.id << " not found.";
            tracksToRemove.push_back(track.id);
          }
        }
        // remove old tracks
        mc.remove_entries_from_playlist(tracksToRemove);
        // add remaining tracks
        std::vector<GMusicApi::identifier> tracksToAdd;
        for (Song* song : *songs) {
          if (song->getGoogleSongId().empty()) continue;
          tracksToAdd.push_back(song->getGoogleSongId());
        }
        mc.add_songs_to_playlist(gmPlaylist.id, tracksToAdd);
        std::cout << "Updated playlist " << gmPlaylist.id << std::endl;
      }
    }
  } catch (std::exception& e) {
    std::cerr << e.what() << '\n';
  }

  // cleanup
  deleteVectorPointers(playlists);
  delete(playlists);
  for (auto it = playlistsSongs.begin(); it != playlistsSongs.end(); ++it) {
    std::vector<Song*>* songs = it->second;
    deleteVectorPointers(songs);
    delete(songs);
  }
}

}
}
