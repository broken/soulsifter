var ss = require('../soulsifter/build/Release/soulsifter');
var pm = require('playmusic');

var settings = new ss.SoulSifterSettings();
var playmusic = new pm();

var email = settings.getString('google.email');
var appKey = settings.getString('google.appKey');

var maxReturned = 500;
var nextPageToken = undefined;

var total = 0;

var processResults = function(err, library) {
  let count = 0;
  if (err) {
    console.error(err);
    return;
  }
  nextPageToken = library.nextPageToken;
  for (let i = 0; i < library.data.items.length; ++i) {
    count++;
    total++;
    let song = library.data.items[i];
    let query = "a:\"" + song.artist + "\"";
    let title = song.title.replace(/ \((ft|feat).? \)*\)/i, '');
    let remixRegex = / \(([\)]*) (remix|rmx|refix|re-fix|mix)\)/i;
    let matches = title.match(remixRegex);
    if (!!matches) {
      query += " t:\"" + matches[1] + "\"";
      title = title.replace(remixRegex, '');
    }
    query += " t:\"" + title + "\"";
    let songs = ss.SearchUtil.searchSongs(query, 0, [], [], [], 2);
    if (songs.length == 1) {
      if (songs[0].googleSongId && songs[0].googleSongId != song.id) {
        console.warn('song ' + songs[0].id + ' has a different id than found ' + song.id);
      } else if (!songs[0].googleSongId) {
        songs[0].googleSongId = song.id;
        songs[0].update();
      }
    } else {
      console.info('found ' + songs.length + ' songs for ' + song.artist + ' - ' + song.title);
    }
  }
  if (maxReturned == count) {
    playmusic.getLibrary({limit: maxReturned, nextPageToken: nextPageToken}, processResults);
  } else {
    console.info('processed ' + total + ' songs');
  }
};

playmusic.init({email: email,  password: appKey}, function(err) {
  if (err) {
    console.error(err);
    return;
  }
  playmusic.getLibrary({limit: maxReturned, nextPageToken: nextPageToken}, processResults);
});