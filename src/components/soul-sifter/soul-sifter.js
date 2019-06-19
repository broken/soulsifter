// <link href="../polymer/polymer.html" rel="import">

// <link href="../iron-flex-layout/iron-flex-layout.html" rel="import">
// <link href="../neon-animation/neon-animatable.html" rel="import">
// <link href="../neon-animation/neon-animated-pages.html" rel="import">
// <link href="../neon-animation/neon-animations.html" rel="import">
// <link href="../paper-drawer-panel/paper-drawer-panel.html" rel="import">
// <link href="../paper-header-panel/paper-header-panel.html" rel="import">
// <link href="../paper-tabs/paper-tab.html" rel="import">
// <link href="../paper-tabs/paper-tabs.html" rel="import">
// <link href="../paper-toast/paper-toast.html" rel="import">
// <link href="../paper-icon-button/paper-icon-button.html" rel="import">

// <link href="genre-edit.html" rel="import">
// <link href="genre-list.html" rel="import">
// <link href="playlist-edit.html" rel="import">
// <link href="playlist-list.html" rel="import">
// <link href="song-edit.html" rel="import">
// <link href="song-list.html" rel="import">
// <link href="song-section.html" rel="import">
// <link href="search-toolbar.html" rel="import">
// <link href="ss-settings.html" rel="import">

import { html, PolymerElement } from "../polymer/polymer-element.js";

class SoulSifter extends PolymerElement {
  static get template() {
    return html`
        <custom-style>
          <style>
            :host {
              position: absolute;
              top: 0;
              right: 0;
              bottom: 0;
              left: 0;
              color: var(--primary-text-color);
              background-color: var(--primary-background-color);
              font-size: 13px;
            }
            #pageAnimatedPages {
              height: 100%;
            }
            #drawer {
              display: flex;
              flex-direction: column;
              background-color: var(--primary-background-color);
            }
            #drawer neon-animated-pages {
              flex: 1;
              overflow-y: scroll;
            }
            /* placed here since less preprocessor fails mixins. */
            paper-tab {
              --paper-tab: {
                background-color: var(--paper-tab-bg);
              };
              --paper-tab-content: {
                font-weight: 500 !important;
              };
            }


            /* remove preset colors */
        /*    :host /deep/ input {
              color: inherit;
            }
            :host /deep/ core-field {
              color: inherit;
            }
            :host /deep/ paper-toolbar {
              background-color: inherit;
              font-size: 1em;
            }
            :host /deep/ paper-input {
              color: inherit;
            }
        */

            paper-icon-button {
              position: absolute;
              display: none;
              width: 24px;
              height: 24px;
              font-size: 16px;
              margin: 8px;
            }

            paper-toast {
              left: auto;
              right: 20px;
            }

            .vertical {
              display: flex;
              flex-direction: column;
            }
            .flex {
              @apply --layout-flex;
            }
          </style>
      </custom-style>
          <paper-drawer-panel>
            <section drawer id="drawer">
              <paper-tabs selected="{{selectedTab}}">
                <paper-tab id="paper_tab-song">Song</paper-tab>
                <paper-tab id="paper_tab-genres" active>Genres</paper-tab>
                <paper-tab id="paper_tab-playlists">Playlists</paper-tab>
              </paper-tabs>
              <neon-animated-pages selected="{{selectedTab}}" entry-animation="slide-from-right-animation" exit-animation="slide-left-animation">
                <neon-animatable><song-section id="songSection" song-trail="{{songTrail}}"></song-section></neon-animatable>
                <neon-animatable><genre-list selection="{{genres}}" main></genre-list></neon-animatable>
                <neon-animatable><playlist-list on-query-change="changeQuery" on-genre-change="updateGenres"></playlist-list></neon-animatable>
              </neon-animated-pages>
            </section>
            <paper-header-panel main>
              <search-toolbar query="{{query}}" search-option-bpm-restrict="{{searchOptionBpmRestrict}}" search-option-key-restrict="{{searchOptionKeyRestrict}}" search-option-trashed-restrict="{{searchOptionTrashedRestrict}}" search-option-repeat-restrict="{{searchOptionRepeatRestrict}}" class="paper-header">
                <paper-icon-button paper-drawer-toggle icon="menu"></paper-icon-button>
              </search-toolbar>
              <song-list query="{{query}}" song-trail="[[songTrail]]" genres="[[genres]]" search-option-bpm-restrict="[[searchOptionBpmRestrict]]" search-option-key-restrict="[[searchOptionKeyRestrict]]" search-option-trashed-restrict="[[searchOptionTrashedRestrict]]" search-option-repeat-restrict="[[searchOptionRepeatRestrict]]" class="fit"></song-list>
            </paper-header-panel>
    `;
  }
  static get properties() {
    return {
      selectedPage: {
        type: Number,
        value: 0
      },
      pageEntryAnimation: String,
      pageExitAnimation: String,
      selectedTab: {
        type: Number,
        value: 1,
        observer: '_selectedTabChanged'
      },
      notifiedSongSection: {
        type: Boolean,
        value: false
      },
      genres: Array,
      songTrail: Array,
    };
  }

  // https://github.com/PolymerElements/paper-scroll-header-panel/issues/33
  _selectedTabChanged(val, notified) {
    if (!this.notifiedSongSection && val === 0) {
      this.$.songSection.setupHeaderSize();
      this.notifiedSongSection = true;
    }
  }

  attached() {
    Polymer.RenderStatus.afterNextRender(this, function() {
      // setup page listeners
      var that = this;
      var mainEntry = 'slide-from-left-animation', mainExit = 'slide-left-animation';
      var subEntry = 'slide-from-right-animation', subExit = 'slide-right-animation';
      this.addEventListener('page-main', function(e) {
        that.pageEntryAnimation = mainEntry;
        that.pageExitAnimation = subExit;
        that.selectedPage = 0;
      });
      this.addEventListener('page-genre-edit', function(e) {
        that.pageEntryAnimation = subEntry;
        that.pageExitAnimation = mainExit;
        that.selectedPage = 1;
        that.genre = e.detail.genre;
      });
      this.addEventListener('page-playlist-edit', function(e) {
        that.pageEntryAnimation = subEntry;
        that.pageExitAnimation = mainExit;
        that.selectedPage = 2;
        that.playlist = e.detail.playlist;
      });
      this.addEventListener('page-song-edit', function(e) {
        that.pageEntryAnimation = subEntry;
        that.pageExitAnimation = mainExit;
        that.selectedPage = 3;
        if (e.detail.song) that.song = e.detail.song;
        if (e.detail.filepaths) that.newSongFilepaths = e.detail.filepaths;
      });
      this.addEventListener('page-settings', function(e) {
        that.pageEntryAnimation = subEntry;
        that.pageExitAnimation = mainExit;
        that.selectedPage = 4;
      });
      this.addEventListener('error-alert', function(e) {
        console.log(e.detail.msg);
        that.errorText = e.detail.msg;
        that.$.toast.show();
      });
    }.bind(this));
  }

  changeQuery(e, detail, sender) {
    this.query = detail;
  }

  updateGenres(e, detail, sender) {
    this.genres = detail;
  }
}

window.customElements.define('soul-sifter', SoulSifter);
