// <link href="../polymer/polymer.html" rel="import">

// <link href="../iron-flex-layout/iron-flex-layout.html" rel="import">

// <link href="ss-global-behavior.html" rel="import">
// <link href="ss-options-menu.html" rel="import">
// <link href="ss-options-menu-item.html" rel="import">
// <link href="ss-star-rating.html" rel="import">

import { html, PolymerElement } from "../polymer/polymer-element.js";

class SongListItem extends PolymerElement {
  static get template() {
    return html`
    <custom-style>
      <style>
        ss-star-rating {
          margin: 0 6px;
        }

        .song-item {
          @apply --layout-horizontal;
          @apply --layout-center;
          height: 30px;
          padding: 0 8px;
          margin: 0 10px;
          border-bottom: var(--ss-song-list-item-border-bottom);
        }
        .song-item div {
          margin: 3px;
        }
        .song-item:hover {
          background-color: var(--ss-song-list-item-hover-background-color);
        }
        .song-item ss-options-menu::shadow #btn {
          display: none;
        }
        .song-item:hover ss-options-menu::shadow #btn {
          display: block;
        }
        ss-options-menu {
          --iron-icon-height: 16px;
          --iron-icon-width: 16px;
          top: -4px;
        }
        /*.song-item #menuButton {
          margin-top: 4px;
          padding: 0;
        }*/
        .song-item .artist {
          color: var(--ss-song-list-item-artist-color);
        }
        .song-item .title {
          color: var(--ss-song-list-item-title-color);
        }
        .song-item .fade-out:after {
          background: var(--ss-song-list-item-fade-out);
        }
        .song-item:hover .fade-out:after {
          background: var(--ss-song-list-item-hover-fade-out);
        }
        .song-item #menuButton {
          border: var(--ss-song-list-item-button-border);
        }
        .song-item #menuButton:hover {
          border: var(--ss-song-list-item-button-hover-border);
        }

        #cover {
          background-position: center center;
          background-size: cover;
          height: 30px;
          width: 30px;
        }

        .key {
          position: relative;
          overflow: hidden;
          white-space: nowrap;
        }

        .energy-0 {
          color: var(--ss-song-list-item-energy-0);
        }
        .energy-1 {
          color: var(--ss-song-list-item-energy-1);
        }
        .energy-2 {
          color: var(--ss-song-list-item-energy-2);
        }
        .energy-3 {
          color: var(--ss-song-list-item-energy-3);
        }
        .energy-4 {
          color: var(--ss-song-list-item-energy-4);
        }
        .energy-5 {
          color: var(--ss-song-list-item-energy-5);
        }
        .energy-6 {
          color: var(--ss-song-list-item-energy-6);
        }
        .energy-7 {
          color: var(--ss-song-list-item-energy-7);
        }
        .energy-8 {
          color: var(--ss-song-list-item-energy-8);
        }
        .energy-9 {
          color: var(--ss-song-list-item-energy-9);
        }
        .energy-10 {
          color: var(--ss-song-list-item-energy-10);
        }

        .fade-out:after {
          display: block;
          position: absolute;
          top: 0;
          bottom: 0;
          right: 0;
          width: 30px;
          content: "";
        }

        time {
          text-align: right;
          width: 64px;
        }

        .flex {
          @apply --layout-flex;
        }
      </style>
    </custom-style>
    <div class="song-item" draggable="true" on-dragstart="_dragSong" id="draggableItem">
      <div id="cover"></div>
      <div class="key fade-out flex">
        <span class="artist">[[song.artist]]</span>
        <span> - </span>
        <span class="title">[[song.title]]</span>
      </div>
      <ss-options-menu>
        <ss-options-menu-item on-click="_openEditSongPage">Edit song</ss-options-menu-item>
      </ss-options-menu>
      <div>[[_computeBpmShift(song, global.bpm)]]</div>
      <div class$="energy-[[song.energy]]">[[song.energy]]</div>
      <div>[[_computeDuration(song)]]</div>
      <ss-star-rating value="[[song.rating]]" class$="[[_trashedClass(song.trashed)]]" read-only></ss-star-rating>
      <time class="added">[[_computeLocaleDateString(song)]]</time>
    </div>
    `;
  }
  static get properties() {
    return {
      song: {
        type: Object,
        observer: '_songChanged'
      },
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

    listeners: {
      'click': '_selectSong',
    }

    _songChanged() {
      this.$.cover.style.backgroundImage = 'url("file://' + this._soulSifterSettings.getString('music.dir') + this.song.album.coverFilepath + '")';
    }

    _computeLocaleDateString(song) {
      return new Date(this.song.dateAdded).toLocaleDateString();
    }

    _computeBpmShift(song, bpm) {
      if (!bpm) return '0.00';
      var songBpm = song ? song.bpm : undefined;
      if (!songBpm) return 'n/a';
      if (Math.abs(songBpm - bpm) > Math.abs(songBpm/2 - bpm)) songBpm = songBpm / 2;
      else if (Math.abs(songBpm - bpm) > Math.abs(songBpm * 2 - bpm)) songBpm = songBpm * 2;
      return ((bpm / songBpm - 1) * 100).toFixed(2);
    }

    _dragSong(e) {
      e.dataTransfer.effectAllowed = 'move';
      e.dataTransfer.setData('text/plain', 'extensis-filenames-type:' + this._soulSifterSettings.getString('music.dir') + this.song.filepath);
      this.set('global.draggedobj', this.song);
    }

    _openEditSongPage(e, detail, sender) {
      this.fire('page-song-edit', {song: this.song});
      e.stopPropagation();
    }

    _trashedClass(trashed) {
      return trashed ? 'trashed' : '';
    }

    _selectSong(e) {
      this.set('global.song', this.song);
    }

    _computeDuration(song) {
      let duration = Math.round(song.durationInMs / 1000);
      let secs = duration % 60;
      let mins = ((duration - secs) / 60) % 60;
      let hours = (duration - secs - mins * 60) / 60 / 60;
      if (secs < 10 && mins) secs = '0' + secs;
      let result = secs;
      if (mins < 10 && hours) mins = '0' + mins;
      if (mins) result = '' + mins + ':' + result;
      if (hours) result = '' + hours + ':' + result;
      return result;
    }
  }

window.customElements.define('song-list-item', SongListItem);
