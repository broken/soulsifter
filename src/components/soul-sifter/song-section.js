// <link href="../polymer/polymer.html" rel="import">

// <link href="../iron-flex-layout/iron-flex-layout.html" rel="import">
// <link href="../iron-signals/iron-signals.html" rel="import">
// <link href="../paper-scroll-header-panel/paper-scroll-header-panel.html" rel="import">
// <link href="../paper-icon-button/paper-icon-button.html" rel="import">
// <link href="../paper-toolbar/paper-toolbar.html" rel="import">

// <link href="pitch-slider.html" rel="import">
// <link href="ss-audio.html" rel="import">
// <link href="ss-global-behavior.html" rel="import">
// <link href="ss-options-menu.html" rel="import">
// <link href="ss-options-menu-item.html" rel="import">
// <link href="ss-star-rating.html" rel="import">

import { html, PolymerElement } from "../polymer/polymer-element.js";

class SongSection extends PolymerElement {
  static get template() {
    return html`
    <custom-style>
      <style>
        paper-scroll-header-panel {
          /*position: static;*/
          height: 100%;
        }
        #header {
          color: inherit;
          background-color: transparent;
          background-size: cover;
          height: 256px;
        }
        .content {
          margin: 10px 15px;
        }
        .title {
          color: var(--secondary-text-color);
        }
        .slider {
          @apply --layout-horizontal;
          @apply --layout-center;
        }
        .flex {
          @apply --layout-flex;
        }
        .self-end {
          @apply --layout-self-end;
        }
        .vertical {
          @apply --layout-vertical;
        }
        #nav {
          @apply --layout-horizontal;
          @apply --layout-justified;
          position: absolute;
          top: 0;
          left: 0;
          right: 0;
          margin: 0;
        }
        #nav paper-icon-button[disabled] {
          visibility: hidden;
        }
        audio {
          height: 30px;
          width: 100%;
        }
        .hasMusicVideo {
          display: none !important;
        }
        #musicVideoInput {
          display: flex;
          flex-direction: row;
        }
        #musicVideoThumbnail {
          width: 100%;
          height: 144px;
          background-size: cover;
        }
      </style>
    </custom-style>
    <iron-signals on-iron-signal-save-song-trail="saveSongTrail"></iron-signals>

    <paper-scroll-header-panel id="shp" condenses keepCondensedHeader condensedHeaderHeight="40" headerHeight="256">
      <paper-toolbar id="header" draggable="true" on-dragstart="dragSong">
        <div id="nav">
          <paper-icon-button icon="arrow-back" on-click="backAction" disabled$="[[_isArrayEmpty(songTrail.*)]]"></paper-icon-button>
          <paper-icon-button icon="arrow-forward" on-click="forwardAction" disabled$="[[_isArrayEmpty(_songTrailCache.*)]]"></paper-icon-button>
        </div>
      </paper-toolbar>
      <div class="content vertical">
        <div class="title">{{song.title}}</div>
        <div class="artist">{{song.artist}}</div>
        <ss-star-rating value="{{song.rating}}" read-only></ss-star-rating>
        <div class="track self-end">{{song.album.track}}</div>
        <div class="track self-end">{{song.album.name}}</div>
        <div class="released self-end"><span>{{song.album.releaseDateYear}}</span>-<span>{{song.album.releaseDateMonth}}</span>-<span>{{song.album.releaseDateDay}}</span></div>
        <div class="comments">{{song.comments}}</div>
        <div class="bpm">{{song.bpm}} bpm</div>
        <time class="added">{{localeDateTime}}</time>
        <div class="slider">
          <div>pitch</div>
          <pitch-slider></pitch-slider>
        </div>
        <div class="audio">
          <ss-audio id="audio" song="[[song]]"></ss-audio>
        </div>
        <div id="musicVideoInput">
          <paper-input label="video id" value="{{_videoId}}" class="flex" no-label-float></paper-input>
          <paper-icon-button icon="av:movie" on-click="_associateVideo"></paper-icon-button>
        </div>
        <div id="musicVideoThumbnail" draggable="true" on-dragstart="_dragMusicVideo"></div>
        <ss-options-menu class="self-end">
          <ss-options-menu-item on-click="_openEditSongPage">Edit song</ss-options-menu-item>
        </ss-options-menu>
      </div>
    </paper-scroll-header-panel>
    `;
  }
  static get properties() {
    return {
      songTrail: {
        type: Array,
        notify: true,
        value() { return []; }
      },
      _songTrailCache: {
        type: Array,
        value() { return []; }
      },
      localeDateTime: {
        type: String,
        value: ''
      },
      // do not clear the cache when the songtrail is changed using the fwd or back btns
      _clearCache: {
        type: Boolean,
        value: false
      },
      _musicVideo: Object,
      _videoId: String,
      _soulSifterSettings: {
        type: Object,
        value() { return new ss.SoulSifterSettings(); },
        readOnly: true
      },
    }
  }

    behaviors: [
      GlobalBehavior
    ],

    observers: [
      'globalSongChanged(global.song)'
    ],

    ready() {
      this.fs = require('fs');
    }

    // https://github.com/PolymerElements/paper-scroll-header-panel/issues/33
    setupHeaderSize() {
      this.$.shp.measureHeaderHeight();
    }

    globalSongChanged(song) {
      this.$.audio.pause();
      this.song = song;
      if (!song) {
        this._setCoverImage();
        this._setMusicVideo();
        return;
      }

      var entry = new ss.PlaylistEntry();
      entry.song = song;
      entry.position = this.songTrail.length;
      this.push('songTrail', entry);
      if (this._clearCache) this._songTrailCache = [];
      else this._clearCache = true;

      this.localeDateTime = new Date(this.song.dateAdded).toLocaleString();

      this._setCoverImage(this._soulSifterSettings.getString('music.dir') + this.song.album.coverFilepath);
      this._setMusicVideo(ss.MusicVideo.findBySongId(this.song.id));
    }

    dragSong(e) {
      e.dataTransfer.effectAllowed = 'move';
      e.dataTransfer.setData('text/plain', 'extensis-filenames-type:' + this._soulSifterSettings.getString('music.dir') + this.song.filepath);
    }

    backAction(e, detail, sender) {
      var entry = this.pop('songTrail');
      if (!!entry) {
        this.push('_songTrailCache', entry);
      }
      this._clearCache = false;
      if (this.songTrail.length) {
        this.set('global.song', this.pop('songTrail').song);
      } else {
        this.set('global.song', undefined);
      }
    }

    forwardAction(e, detail, sender) {
      this._clearCache = false;
      this.set('global.song', this.pop('_songTrailCache').song);
    }

    saveSongTrail(e, detail, sender) {
      var playlist = detail.playlist;
      for (var i = 0; i < this.songTrail.length; ++i) {
        var entry = this.songTrail[i];
        entry.playlist = playlist;
        entry.save();
      }
    }

    _setCoverImage(img) {
      var url = '';
      if (img) {
        url = 'url("file://' + img + '")';
      }
      var root = this.$.shp.shadowRoot || this.$.shp;
      root.querySelector('#headerBg').style.backgroundImage = url;
    }

    _setMusicVideo(mv) {
      this._musicVideo = mv;
      var url = '';
      if (!!mv && !!mv.thumbnailFilePath) {
        url = 'url("file://' + this._soulSifterSettings.getString('mv.dir') + mv.thumbnailFilePath + '")';
      }
      this.$.musicVideoThumbnail.style.backgroundImage = url;
      this.toggleClass('hasMusicVideo', !mv, this.$.musicVideoThumbnail);
      this.toggleClass('hasMusicVideo', !!mv, this.$.musicVideoInput);
    }

    _associateVideo() {
      if (!this.global.song) return;
      this._setMusicVideo(ss.MusicVideoService.associateYouTubeVideo(this.global.song, this._videoId));
    }

    _dragMusicVideo(e) {
      e.dataTransfer.effectAllowed = 'move';
      e.dataTransfer.setData('text/plain', 'extensis-filenames-type:' + this._soulSifterSettings.getString('mv.dir') + this._musicVideo.filePath);
    }

    _openEditSongPage(e, detail, sender) {
      this.fire('page-song-edit', {song: this.song});
      e.stopPropagation();
    }

    stopPropagation(e, detail, sender) {
      e.stopPropagation();
    }

    _isArrayEmpty(arrayChange) {
      return arrayChange.base.length === 0;
    }
  }

window.customElements.define('song-section', SongSection);
