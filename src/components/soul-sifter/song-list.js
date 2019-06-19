// <link href="../polymer/polymer.html" rel="import">

// <link href="../iron-signals/iron-signals.html" rel="import">
// <link href="../core-tooltip/core-tooltip.html" rel="import">

// <link href="song-list-item.html" rel="import">
// <link href="ss-global-behavior.html" rel="import">

import { html, PolymerElement } from "../polymer/polymer-element.js";

class SongList extends PolymerElement {
  static get template() {
    return html`
    <custom-style>
      <style>
        core-tooltip {
          position: absolute;
          left: 50%;
        }

        .song {
          height: 20px;
          padding-left: 5px;
        }
      </style>
    </custom-style>
    <iron-signals on-iron-signal-search="search"></iron-signals>

    <core-tooltip id="tooltip" label="Searching..." noarrow position top></core-tooltip>
    <template is="dom-repeat" items="{{songs}}">
      <song-list-item song="{{item}}"></song-list-item>
    `;
  }
  static get properties() {
    return {
      query: {
        type: String,
        observer: '_queryChanged'
      },
      songTrail: {
        type: Array,
        value() { return []; }
      },
      songs: {
        type: Array,
        value() { return []; }
      },
      genres: {
        type: Array,
        value() { return []; }
      },
      settings: {
        type: Object,
        value() { return new ss.SoulSifterSettings(); },
        readOnly: true
      },
      searchOptionBpmRestrict: Boolean,
      searchOptionKeyRestrict: Boolean,
      searchOptionTrashedRestrict: Boolean,
      searchOptionRepeatRestrict: Boolean,
    }
  }

    behaviors: [
      GlobalBehavior
    ],

    observers: [
      '_globalBpmChanged(global.bpm)',
      '_globalPlaylistChanged(global.playlist)'
    ],

    attached() {
      Polymer.RenderStatus.afterNextRender(this, function() {
        this.search();
      }.bind(this));
    }

    _globalBpmChanged(bpm) {
      if (this.searchOptionBpmRestrict) this.search();
    }

    _globalPlaylistChanged(playlist) {
      if (!!playlist) this.search();
    }

    _queryChanged(newValue, oldValue) {
      // only search if it's not actively being changed
      setTimeout(function(self, query) {
        return function() {
          if (self.query == query) {
            self.search();
          }
        };
      }(this, this.query), 750);
    }

    search(e, detail, sender) {
      this.$.tooltip.show = true;
      var that = this;
      // give the tooltip a chance to show
      setTimeout(function() {
        if (!!that.global.playlist) {
          var playlist = that.global.playlist;
          if (!playlist.query) {
            var entries = playlist.playlistEntries;
            that.songs = entries.sort(function(a, b) { return a.position - b.position; })
                                .map(function(x) { return x.song; });
            return;
          } else {
            that.query = playlist.query;
            that.genres = playlist.styles;
          }
        }
        var genreIds = that.genres.map(function(g) { return g.id; });
        var p = {q: that.query, genres: genreIds.join(',')};
        var omitSongs = [];
        p.bpm = that.searchOptionBpmRestrict && that.global.bpm ? that.global.bpm : 0;
        p.keys = that.searchOptionKeyRestrict && that.global.song ? that.global.song.tonicKeys : [];
        p.q += !that.searchOptionTrashedRestrict ? '' : (p.q.length ? ' ' : '') + 'trashed:0';
        omitSongs = !that.searchOptionRepeatRestrict ? [] : that.songTrail.map(function(e) { return e.song; });
        that.songs = ss.SearchUtil.searchSongs(p.q, p.bpm, p.keys, that.genres, omitSongs, that.settings.getInt('songList.limit'));
        // A couple things to note here. First, this timeout will activate when the template repeat has finished loading, which is 99% of the wait time here. Next, I would love to use paper-toast, but it appears that loading the template repeat consumes all the resources that would allow it to animate in. I could set a timeout for the toast animation, but what a waste.
        setTimeout(function() {
          that.$.tooltip.show = false;
        }, 1);
      }, 1);
    }
  }

window.customElements.define('song-list', SongList);
