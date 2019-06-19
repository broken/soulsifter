// <link href="../polymer/polymer.html" rel="import">

// <link href="../iron-icons/iron-icons.html" rel="import">
// <link href="../paper-dialog/paper-dialog.html" rel="import">
// <link href="../paper-icon-button/paper-icon-button.html" rel="import">
// <link href="../paper-input/paper-input.html" rel="import">
// <link href="../paper-toggle-button/paper-toggle-button.html" rel="import">

// <link href="search-info.html" rel="import">
// <link href="ss-global-behavior.html" rel="import">
// <link href="ss-options-menu.html" rel="import">
// <link href="ss-options-menu-item.html" rel="import">
// <link href="ss-search-options.html" rel="import">

import { html, PolymerElement } from "../polymer/polymer-element.js";

class SearchToolbar extends PolymerElement {
  static get template() {
    return html`
    <custom-style>
      <style>
        :host {
          background-color: var(--search-toolbar-background);
          display: flex;
          flex-direction: row;
          height: 42px;
          padding-top: 5px;
          padding-left: 17px;
        }
        paper-icon-button {
          color: var(--primary-text-color);
        }
        #searchInfoDialog {
          max-width: none !important;
        }
        #bpm {
          width: 64px;
        }
        .flex {
          flex: 1;
          flex-basis: auto;
        }
        .menuItem {
          white-space: nowrap;
        }
      </style>
    </custom-style>
    <slot></slot>  <!-- for drawer icon. needed? -->
    <paper-icon-button icon="search" on-click="search"></paper-icon-button>
    <paper-input label="search" value="{{query}}" class="flex" no-label-float></paper-input>
    <paper-icon-button icon="info-outline" on-click="_toggleSearchInfoDialog"></paper-icon-button>
    <paper-icon-button icon="build" on-click="_toggleSearchOptionsDialog"></paper-icon-button>
    <paper-input label="bpm" value="{{global.bpm}}" id="bpm" no-label-float></paper-input>
    <paper-icon-button icon="add-circle" on-click="_openCreateSongPage" id="createSongButton"></paper-icon-button>
    <paper-icon-button icon="settings" on-click="_openSettingsPage"></paper-icon-button>
    <ss-options-menu>
      <ss-options-menu-item on-click="addSongFromUrl">Add Song From URL</ss-options-menu-item>
      <ss-options-menu-item on-click="updateSongAttributesFromTags">Update Song Attributes From Tags</ss-options-menu-item>
      <ss-options-menu-item on-click="analyzeBpms">Analyze BPMs</ss-options-menu-item>
      <ss-options-menu-item on-click="analyzeDurations">Analyze Durations</ss-options-menu-item>
      <ss-options-menu-item on-click="syncGoogleMusic">Sync Google Music</ss-options-menu-item>
      <ss-options-menu-item on-click="syncGoogleMusicPlaylists">Sync Google Music Playlists</ss-options-menu-item>
      <ss-options-menu-item on-click="showDevTools">View Developer Tools</ss-options-menu-item>
    </ss-options-menu>
    <paper-dialog id="searchInfoDialog" entry-animation="fade-in-animation" exit-animation="fade-out-animation">
      <search-info></search-info>
    </paper-dialog>
    <paper-dialog id="searchOptionsDialog" entry-animation="fade-in-animation" exit-animation="fade-out-animation">
      <ss-search-options search-option-bpm-restrict="{{searchOptionBpmRestrict}}" search-option-key-restrict="{{searchOptionKeyRestrict}}" search-option-trashed-restrict="{{searchOptionTrashedRestrict}}" search-option-repeat-restrict="{{searchOptionRepeatRestrict}}"></ss-search-options>
    </paper-dialog>
    `;
  }
  static get properties() {
    return {
      query: {
        type: String,
        notify: true
      },
      searchOptionBpmRestrict: {
        type: Boolean,
        notify: true
      },
      searchOptionKeyRestrict: {
        type: Boolean,
        notify: true
      },
      searchOptionTrashedRestrict: {
        type: Boolean,
        notify: true
      },
      searchOptionRepeatRestrict: {
        type: Boolean,
        notify: true
      },
      _nwGui: {
        type: Object,
        value() { return require('nw.gui'); },
        readOnly: true
      },
    }
  }

    behaviors: [
      GlobalBehavior
    ],

    attached() {
      Polymer.RenderStatus.afterNextRender(this, function() {
        this.$.createSongButton.ondragover = function() {
          this.icon = 'add-circle-outline';
          return false;
        };
        this.$.createSongButton.ondragleave = function() {
          this.icon = 'add-circle';
          return false;
        };
        this.$.createSongButton.ondrop = function(e) {
          e.preventDefault();
          this.icon = 'add-circle';
          var files = e.dataTransfer.files;
          var filepaths = new Array();
          for (var i = 0; i < files.length; ++i) {
            filepaths.push(files[i].path);
          }
          this.fire('page-song-edit', {filepaths: filepaths});
          return false;
        };
      }.bind(this));
    }

    search(e, detail, sender) {
      this.fire('iron-signal', {name: 'search'});
    }

    analyzeBpms(e, detail, sender) {
      ss.AudioAnalyzer.analyzeBpms();
    }

    analyzeDurations(e, detail, sender) {
      ss.AudioAnalyzer.analyzeDurations();
    }

    updateSongAttributesFromTags(e, detail, sender) {
      ss.TagService.updateSongAttributesFromTags();
    }

    showDevTools(e, detail, sender) {
      this._nwGui.Window.get().showDevTools();
    }

    syncGoogleMusic(e, detail, sender) {
      var child_process = require('child_process');
      var path = require('path');
      var downloadProcess = child_process.fork(path.join(nw.__dirname, 'workers', 'syncgooglemusic.js'), [], {cwd: nw.__dirname});
    }

    syncGoogleMusicPlaylists(e, detail, sender) {
      var child_process = require('child_process');
      var path = require('path');
      var downloadProcess = child_process.fork(path.join(nw.__dirname, 'workers', 'syncgooglemusicplaylists.js'), [], {cwd: nw.__dirname});
    }

    addSongFromUrl(e, detail, sender) {
      var url = nw.Clipboard.get().get('text');
      window.console.log('Audio url = ' + url);

      var filepaths = ss.MusicVideoService.downloadAudio(url);
      if (filepaths.length > 0) {
        this.fire('page-song-edit', {filepaths: filepaths});
      } else {
        window.console.log('Failed to download audio from url ' + url);
      }
    }

    _toggleSearchInfoDialog(e, detail, sender) {
      this.$.searchInfoDialog.toggle();
    }

    _toggleSearchOptionsDialog(e, detail, sender) {
      this.$.searchOptionsDialog.toggle();
    }

    _openSettingsPage(e, detail, sender) {
      this.fire('page-settings');
    }

    _openCreateSongPage(e, detail, sender) {
      // var song = new ss.Song();
      // this.fire('page-song-edit', {song: song});
    }
  }

window.customElements.define('search-toolbar', SearchToolbar);
