// <link href="../polymer/polymer.html" rel="import">

// <link href="ss-global-behavior.html" rel="import">

import { html, PolymerElement } from "../polymer/polymer-element.js";

class GooglePlayMusic extends PolymerElement {

    attached() {
      if (!this.global.playmusic) {
        var PlayMusic = require('playmusic');
        var playmusic = new PlayMusic();
        var settings = new ss.SoulSifterSettings();
        var email = settings.getString('google.email');
        var appKey = settings.getString('google.appKey');
        if (!email) {
          return;
        }
        playmusic.init({email: email, password: appKey}, function(err) {
          if(err) {
            console.error('Login to Google Music failed.');
            console.error(err);
          } else {
            console.info('Succesfully connected to Google Music.');
          }
        }.bind(this));
        this.global.playmusic = playmusic;
      }
    }

    behaviors: [
      GlobalBehavior
    ],

    /**
     * Success callback takes a song.
     * Failure callback takes message, body, err, httpResonse
     * WARNING: Nothing uses this, and before usage, should verify it still works.
     */
    findSong(song, success, failure) {
      if (!this.connected) {
        return;
      }
      var maxResults = 3;
      this.playmusic.search(song.artist + ' ' + song.title, maxResults,
          function(err, data) {
            if (err) {
              console.error('Unable to search for song ' + song.artist + ' - ' + song.title);
              console.error(err);
              return;
            }
            console.log(data);
            if (!data.entries) {
              failure('No results in Google Play Music for ' + song.artist + ' - ' + song.title, '', 1);
              return;
            }
            // We first filter by type. Types are:
            // 1 : track result
            // 2 : artist result
            // 3 : album result
            // Then we take the result with the highest score.
            var track = data.entries
                .filter(function(val) { return val.type == 1; })
                .sort(function(a, b) { return a.score < b.score; })
                .shift();
            if (!track) {
              failure('No track results in Google Play Music for ' + song.artist + ' - ' + song.title, '', 2);
              return;
            }
            success(track);
          },
          function(message, body, err, httpResponse) {
            console.warn('Error searching Google Play Music for ' + song.artist + ' - ' + song.title + '.  ' + message + '\
' + body + '\
' + err + '\
' + httpResponse);
            failure(message, body, err, httpResonse);
          }
      );
    }

    /**
     * Add a new playlist, save the playlist id, and add the songs.
     */
    createPlaylist(playlist) {
      if (!playlist.gmusicId) {
        this.global.playmusic.addPlayList(playlist.name, function(err, mutationStatus) {
          if (err) {
            console.error('Unable to create playlist ' + playlist.name);
            console.error(err);
          } else {
            console.info('Successfully created playlist ' + playlist.name);
            playlist.gmusicId = mutationStatus.mutate_response[0].id;
            playlist.update();
            // todo add songs
          }
        });
      }
    }

    /**
     * Callback returns err, streamUrl
     */
    getStreamUrl(gmid, callback) {
      th
  }
}

window.customElements.define('ss-googleplaymusic', GooglePlayMusic);
