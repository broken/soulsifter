var ss = require('../soulsifter/build/Release/soulsifter');
var pm = require('playmusic');

var settings = new ss.SoulSifterSettings();
var playmusic = new pm();

var email = settings.getString('google.email');
var appKey = settings.getString('google.appKey');
var androidId = settings.getString('google.androidId');
var songLimit = 200;

var maxReturned = 1000;
var nextPageToken = undefined;
var masterToken = undefined;

let playlists = ss.Playlist.findAll();

// create sets of song for each Google playlist
let playlistsSongIds = {};
for (let i = 0; i < playlists.length; ++i) {
  let playlist = playlists[i];
  if (!playlist.gmusicId) continue;
  let songs = [];
  if (!playlist.query) {
    // populate songs from entries
    let entries = ss.PlaylistEntry.findByPlaylistId(playlist.id);
    entries.sort((a, b) => a.position - b.position);
    entries.forEach(entry => songs.push(entry.song));
  } else {
    // populate from query
    songs = ss.SearchUtil.searchSongs(playlist.query, 0 /* bpm */, [] /* keys */, playlist.styles, [] /* songs to omit */, songLimit);
  }
  playlistsSongIds[playlist.gmusicId] = songs.map(s => s.googleSongId);
  console.info(playlistsSongIds);
}

// TODO Fix; as this only processes maxReturned at a time.
function processResults(err, x) {
  let entriesToRemove = [];
  console.info('Processing ' + x.data.items.length + ' Google Music playlist entries.');
  for (let i = 0; i < x.data.items.length; ++i) {
    let entry = x.data.items[i];
    if (!playlistsSongIds[entry.playlistId]) continue;
    if (entry.deleted) {
      console.info('track ' + entry.trackId + ' deleted in playlist ' + entry.playlistId);
      continue;
    }
    let found = false;
    for (let i = 0; i < playlistsSongIds[entry.playlistId].length; ++i) {
      let songId = playlistsSongIds[entry.playlistId][i];
      if (songId == entry.trackId) {
        console.info('Track ' + entry.trackId + ' found in playlist ' + entry.playlistId);
        found = true;
        playlistsSongIds[entry.playlistId].splice(i, 1);
      }
    }
    if (!found) {
      console.info('Track ' + entry.trackId + ' not found in playlist ' + entry.playlistId);
      entriesToRemove.push(entry.id);
    }
  }
  // remove old tracks
  if (entriesToRemove.length > 0) {
    console.info('Want to remove ' + entriesToRemove.length + ' entries.');
    playmusic.removePlayListEntry(entriesToRemove, function(err, status) {
      if (err) console.error('Error removing entries.');
      else console.info('Successfully removed entries.');
      console.info(status);
    });
  } else {
    console.info('No entries to remove.');
  }
  // add missing tracks
  for (let [playlistId, songIds] of Object.entries(playlistsSongIds)) {
    let tracksToAdd = [];
    for (let i = 0; i < songIds.length; ++i) {
      if (!!songIds[i]) tracksToAdd.push(songIds[i]);
    }
    if (tracksToAdd.length) {
      console.info('Want to add ' + tracksToAdd.length + ' tracks for playlist ' + playlistId);
      playmusic.addTrackToPlayList(tracksToAdd, playlistId, function(err, status) {
        if (err) console.error('Unable to add tracks to playlist ' + playlistId);
        else console.info('Tracks added to playlist ' + playlistId);
        console.info(status);
      });
    } else {
      console.info('No tracks to add for ' + playlistId);
    }
  }
}

// compute differences of goldens with current
playmusic.login({email: email, password: appKey, androidId: androidId}, function(err, x) {
  if (err) {
    console.error(err);
    return;
  }
  console.info('Logged in to Google Music.');
  masterToken = x.masterToken;
  playmusic.init({androidId: androidId, masterToken: masterToken}, function(err, x) {
    if (err) {
      console.error(err);
      return;
    }
    console.info('Initialized Google Music.');
    playmusic.getPlayListEntries({limit: maxReturned, androidId: androidId, masterToken: masterToken}, processResults);
  });
});