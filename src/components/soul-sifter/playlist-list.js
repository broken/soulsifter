// <link href="../polymer/polymer.html" rel="import">

// <link href="../iron-signals/iron-signals.html" rel="import">
// <link href="../paper-button/paper-button.html" rel="import">
// <link href="../paper-dialog/paper-dialog.html" rel="import">
// <link href="../paper-fab/paper-fab.html" rel="import">
// <link href="../paper-input/paper-input.html" rel="import">

// <link href="playlist-list-item.html" rel="import">
// <link href="ss-global-behavior.html" rel="import">

import { html, PolymerElement } from "../polymer/polymer-element.js";

class PlaylistList extends PolymerElement {
  static get template() {
    return html`
    <custom-style>
      <style>
        paper-fab {
          bottom: 60px;
          position: absolute;
          right: 12px;
        }
      </style>
    </custom-style>
    <iron-signals on-iron-signal-playlists-changed="updatePlaylists"></iron-signals>

    <template is="dom-repeat" items="[[playlists]]" id="playlistTpl">
      <playlist-list-item playlist="[[item]]" on-playlist-select="_selectPlaylist" selected$="[[_isSelected(item, selected)]]"></playlist-list-item>
    </template>
    <paper-fab mini icon="add" on-click="_createPlaylist"></paper-fab>
    `;
  }
  static get properties() {
    return {
      selected: Object
    }
  }

    behaviors: [
      GlobalBehavior
    ],

    attached() {
      Polymer.RenderStatus.afterNextRender(this, function() {
        this.updatePlaylists();
      }.bind(this));
    }

    updatePlaylists(e, detail, sender) {
      this.playlists = ss.Playlist.findAll();
    }

    _createPlaylist(e, detail, sender) {
      var playlist = new ss.Playlist();
      this.fire('page-playlist-edit', {playlist: playlist});
    }

    _selectPlaylist(e, detail, sender) {
      this.selected = (this.selected === e.model.item) ? null : e.model.item;
      this.set('global.playlist', this.selected);
    }

    _isSelected(item, selected) {
      return item === selected;
    }
  }

window.customElements.define('playlist-list', PlaylistList);
