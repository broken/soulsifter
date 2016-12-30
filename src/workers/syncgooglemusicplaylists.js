var ss = require('../soulsifter/build/Release/soulsifter');
var pm = require('playmusic');

var settings = new ss.SoulSifterSettings();
var playmusic = new pm();

var email = settings.getString('google.email');
var appKey = settings.getString('google.appKey');

var maxReturned = 500;
var nextPageToken = undefined;
var total = 0;

var playlists = ss.Playlist.findAll().filter(function(p) {
  return !!p.gmusicId;
});
var playlistEntries = {};
for (let i = 0; i < playlists.length; ++i) {
  let obj = {};
  obj.playlist = playlists[i];
  obj.entries = {};
  playlistEntries[obj.playlist.gmusicId] = obj;
}

var getPlaylistEntriesFromDb = function(playlist) {
  if (!playlist.query) {
    let entries = playlist.playlistEntries;
    return entries.sort(function(a, b) { return a.position - b.position; })
                  .map(function(x) { return x.song; });
  }
  return ss.SearchUtil.searchSongs(playlist.query, 0, [], playlist.styles, [], 10000);
};

var processPlaylist = function(playlist, entries) {
  let playlistEntriesFromDb = getPlaylistEntriesFromDb(playlist);
  let songsToAdd = [];
  for (let i = 0; i < playlistEntriesFromDb.length; ++i) {
    let song = playlistEntriesFromDb[i];
    if (!!song.googleSongId) {
      if (!entries[song.googleSongId]) {
        songsToAdd.push(song.googleSongId);
      } else {
        delete entries[song.googleSongId];
      }
    }
  }
  if (songsToAdd.length) {
    playmusic.addTrackToPlayList(songsToAdd, playlist.gmusicId, function(err, mutationStatus) {
      if (!!err) {
        console.error(err);
        return;
      }
      console.info(mutationStatus);
    });
  }
  if (entries.length) {
    // todo uncomment after further testing
    /*playmusic.removePlayListEntry(Object.keys(entries), function(err, mutationStatus) {
      if (!!err) {
        console.error(err);
        return;
      }
      console.info(mutationStatus);
    });*/
    console.warn('Removing entries from playlist');
    console.warn(playlist.gmusicId);
    console.warn(entries);
  }
};

var processEntries = function(err, entries) {
  nextPageToken = entries.nextPageToken;
  let count = 0;
  if (err) {
    console.error(err);
    return;
  }
  for (let i = 0; i < entries.data.items.length; ++i) {
    count++;
    total++;
    let entry = entries.data.items[i];
    if (!!entry && !entry.deleted && !!playlistEntries[entry.playlistId]) {
      playlistEntries[entry.playlistId].entries[entry.trackId] = true;
    }
  }
  if (maxReturned == count) {
    playmusic.getPlayListEntries({limit: maxReturned, nextPageToken: nextPageToken}, processEntries);
  } else {
    console.info('processed ' + total + ' playlist entries.');
    for (let gmusicId in playlistEntries) {
      processPlaylist(playlistEntries[gmusicId].playlist, playlistEntries[gmusicId].entries);
    }
  }
};

playmusic.init({email: email,  password: appKey}, function(err) {
  if (err) {
    console.error(err);
    return;
  }
  playmusic.getPlayListEntries({limit: maxReturned, nextPageToken: nextPageToken}, processEntries);
});
// get playlists w gmusic
// get all playlist entries
// sort
// remove unused entries
// add new entries
