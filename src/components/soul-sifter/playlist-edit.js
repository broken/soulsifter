// <link href="../polymer/polymer.html" rel="import">

// <link href="../iron-flex-layout/iron-flex-layout.html" rel="import">
// <link href="../paper-checkbox/paper-checkbox.html" rel="import">
// <link href="../paper-input/paper-input.html" rel="import">

// <link href="abstract-action-page.html" rel="import">
// <link href="genre-list.html" rel="import">
// <link href="ss-googleplaymusic.html" rel="import">

import { html, PolymerElement } from "../polymer/polymer-element.js";

class PlaylistEdit extends PolymerElement {
  static get template() {
    return html`
    <custom-style>
      <style>
      </style>
    </custom-style>
    <ss-googleplaymusic id="gpm"></ss-googleplaymusic>
    <abstract-action-page id="abstractActionPage">
      <div class="fields">
        <paper-input floatingLabel label="Name" value="{{playlist.name}}"></paper-input>
        <paper-input floatingLabel label="Query" value="{{playlist.query}}"></paper-input>
        <br>
        <paper-checkbox checked="{{fromSongTrail}}">from Song Trail</paper-checkbox>
        <paper-checkbox checked="{{gmusicSync}}">sync with Google Music</paper-checkbox>
      </div>
      <div class="genres">
        <genre-list id="genreList" selection="{{playlist.styles}}" single-select></genre-list>
      </div>
    </abstract-action-page>
    `;
  }
  static get properties() {
    return {
      playlist: {
        type: Object,
        observer: '_playlistChanged',
      },
      fromSongTrail: {
        type: Boolean,
        value: false
      },
      gmusicSync: {
        type: Boolean,
        value: false,
      },
    }
  }

    attached() {
      Polymer.RenderStatus.afterNextRender(this, function() {
        this.$.abstractActionPage.setAcceptAction(this.save);
      }.bind(this));
    }

    save(e, detail, sender) {
      if (this.playlist.id) {
        this.playlist.update();
      } else {
        this.playlist.save();
        if (this.fromSongTrail) {
          this.fire('iron-signal', {name: 'save-song-trail', data: {playlist: this.playlist} });
        }
      }
      if (this.gmusicSync && !this.playlist.gmusicId) {
        this.$.gpm.createPlaylist(this.playlist);
      }
      this.fire('iron-signal', {name: 'playlists-changed'});
    }

    _playlistChanged() {
      this.gmusicSync = !!this.playlist.gmusicId;
    }
  }

window.customElements.define('playlist-edit', PlaylistEdit);
