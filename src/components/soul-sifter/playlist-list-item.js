// <link href="../polymer/polymer.html" rel="import">

// <link href="../iron-flex-layout/iron-flex-layout.html" rel="import">
// <link href="../iron-icon/iron-icon.html" rel="import">
// <link href="../paper-icon-button/paper-icon-button.html" rel="import">
// <link href="../paper-menu/paper-menu.html" rel="import">
// <link href="../paper-ripple/paper-ripple.html" rel="import">
// <link href="../paper-material/paper-material.html" rel="import">

// <link href="ss-global-behavior.html" rel="import">
// <link href="ss-googleplaymusic.html" rel="import">
// <link href="ss-options-menu.html" rel="import">
// <link href="ss-options-menu-item.html" rel="import">

import { html, PolymerElement } from "../polymer/polymer-element.js";

class PlaylistListItem extends PolymerElement {
  static get template() {
    return html`
    <custom-style>
      <style>
        :host[selected] #itemContainer {
          background-color: var(--ss-playlist-list-item-selected-background-color);
        }

        #itemContainer {
          border-radius: 2px;
          margin: 7px 20px;
          height: 30px;
        }
        #item {
          height: 30px;
          padding-left: 40px;
          @apply --layout-horizontal;
          @apply --layout-center;
        }
        #item iron-icon {
          display: none;
          vertical-align: top;
          --iron-icon-height: 16px;
          --iron-icon-width: 16px;
        }
        #item iron-icon.smart {
          display: block;
        }

        #item paper-icon-button paper-icon-button {
          margin-top: 4px;
          padding: 0;
        }

        .content {
          @apply --layout-flex;
          @apply --layout-horizontal;
        }
        ss-options-menu {
          --iron-icon-height: 16px;
          --iron-icon-width: 16px;
        }
        #item ss-options-menu::shadow #btn {
          display: none;
        }
        #item:hover ss-options-menu::shadow #btn {
          display: block;
        }
      </style>
    </custom-style>
    <ss-googleplaymusic id="gpm"></ss-googleplaymusic>

    <div id="itemContainer" on-drop="_handleDrop">
      <paper-material animated id="material" elevation="[[_computeElevation(selected)]]">
        <div id="item" on-click="_onClick">
          <paper-ripple fit></paper-ripple>
          <div class="content">
            <span>[[playlist.name]]</span>
            <iron-icon icon="find-replace" alt="smart playlist" class$="[[_isSmart(playlist)]]"></iron-icon>
          </div>
          <ss-options-menu>
            <ss-options-menu-item on-click="_editAction">Edit playlist</ss-options-menu-item>
            <ss-options-menu-item on-click="_deleteAction">Delete playlist</ss-options-menu-item>
          </ss-options-menu>
        </div>
      </paper-material>
    </div>
    `;
  }
  static get properties() {
    return {
      playlist: Object,
      selected: {
        type: Boolean,
        value: false
      }
    }
  }
  /** Fires events:
   *      playlist-select
   *      page-playlist-edit
   */

    behaviors: [
      GlobalBehavior
    ],

    _onClick(e, detail, sender) {
      if (!event.defaultPrevented) {
        this.fire('playlist-select', this);
      }
    }

    _editAction(e, detail, sender) {
      e.preventDefault();
      this.fire('page-playlist-edit', {playlist: this.playlist});
    }

    _deleteAction(e, detail, sender) {
      e.preventDefault();
      // this.playlist.erase();
      // this.fire('iron-signal', {name: 'playlists-changed'});
    }

    _isSmart(playlist) {
      return !!playlist.query ? "smart" : "";
    }

    _computeElevation(selected) {
      return selected ? "3" : "0";
    }

    _handleDrop(e) {
      // only makes sense to drag & drop songs for non-smart playlists
      if (!this.playlist.query) {
        // this must be in multiple steps for it to save correctly
        let entries = this.playlist.playlistEntries;
        let entry = new ss.PlaylistEntry();
        entry.playlist = this.playlist;
        entry.song = this.global.draggedobj;
        for (let i = 0; i < entries.length; ++i) {
          if (entries[i].position >= entry.position) {
            entry.position = entries[i].position + 1;
          }
        }
        entry.save();
        entries.push(entry);
        this.playlist.playlistEntries = entries;
      }
    }
  }

window.customElements.define('playlist-list-item', PlaylistListItem);
