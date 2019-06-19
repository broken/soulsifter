// <link href="../polymer/polymer.html" rel="import">

// <link href="../iron-flex-layout/iron-flex-layout.html" rel="import">
// <link href="../paper-checkbox/paper-checkbox.html" rel="import">
// <link href="../paper-dropdown-menu/paper-dropdown-menu.html" rel="import">
// <link href="../paper-input/paper-input.html" rel="import">
// <link href="../paper-item/paper-item.html" rel="import">
// <link href="../paper-menu/paper-menu.html" rel="import">

// <link href="abstract-action-page.html" rel="import">
// <link href="genre-list.html" rel="import">
// <link href="ss-audio.html" rel="import">
// <link href="ss-star-rating.html" rel="import">

import { html, PolymerElement } from "../polymer/polymer-element.js";

class SongEdit extends PolymerElement {
  static get template() {
    return html`
    <custom-style>
      <style>
        :host {
          font-size: 16px;
        }

        paper-input {
          position: relative;
          width: 240px;
        }
        paper-input::shadow .label-is-floating label {
          text-align: right;
        }
        paper-dropdown-menu::shadow paper-input::shadow label {
          text-align: right;
        }

        paper-checkbox {
          margin: 10px 0;
        }

        #ratingContainer {
          position: relative;
          padding: 13px 0;
          width: 240px;
        }
        #ratingContainer .label {
          position: absolute;
          right: 260px;
          top: 15px;
        }
        .label {
          font-size: 0.75em;
        }
        .prev {
          font-size: 13px;
          margin-top: 8px;
          margin-bottom: -28px;
          text-align: right;
          color: #666;  /* TODO pull into theme */
        }
        .metadata {
          display: flex;
          flex-direction: row;
          position: absolute;
          align-content: flex-end;
          bottom: 0;
          right: 0;
          left: 0;
          font-size: 13px;
          color: #777777;  /* TODO put into theme */
        }
        .metadata div {
          padding: 0 20px;
          white-space: nowrap;
        }
        .audio {
          height: 24px;
          width: 100%;
          flex-grow: 10;
        }

        .cols {
          display: flex;
          flex-direction: row;
          justify-content: space-between;
        }
        .rows {
          display: flex;
          flex-direction: column;
        }
        #cover {
          background-position: center center;
          background-size: cover;
          background-color: #333;  /* TODO put into theme */
          height: 108px;
          width: 108px;
        }
      </style>
    </custom-style>
    <abstract-action-page id="abstractActionPage" do-not-call-exit>
      <div class="fields">
        <div class="prev">&nbsp;<span>[[_taggedSong.artist]]</span></div>
        <paper-input label="Artist" value="{{_editedSong.artist}}" required="true" floatingLabel></paper-input>
        <div class="prev">&nbsp;<span>[[_taggedSong.track]]</span></div>
        <paper-input label="Track Num" value="{{_editedSong.track}}" floatingLabel></paper-input>
        <div class="prev">&nbsp;<span>[[_taggedSong.title]]</span></div>
        <paper-input label="Title" value="{{_editedSong.title}}" required="true" floatingLabel></paper-input>
        <div class="prev">&nbsp;<span>[[_taggedSong.remixer]]</span></div>
        <paper-input label="Remixer" value="{{_editedSong.remixer}}" floatingLabel></paper-input>
        <paper-input label="Comments" value="{{_editedSong.comments}}" floatingLabel></paper-input>
        <paper-input label="Curator" value="{{_editedSong.curator}}" floatingLabel></paper-input>
        <div id="ratingContainer">
          <div class="label">Rating</div>
          <ss-star-rating value="{{_editedSong.rating}}"></ss-star-rating>
        </div>
        <div class="prev">&nbsp;<span>[[_taggedSong.bpm]]</span></div>
        <paper-input label="BPM" value="{{_editedSong.bpm}}" floatingLabel></paper-input>
        <paper-input label="Key" value="{{_editedSong.tonicKey}}" floatingLabel></paper-input>
        <div class="cols">
          <div class="rows">
            <paper-checkbox checked="{{_editedSong.lowQuality}}">Low Quality</paper-checkbox>
            <paper-checkbox checked="{{_editedSong.album.mixed}}">Mixed</paper-checkbox>
            <paper-checkbox checked="{{_editedSong.trashed}}" disabled$="[[song.trashed]]">Trash</paper-checkbox>
          </div>
          <div id="cover" on-click="_changeCover"></div>
          <input style="display:none;" id="coverFileDialog" type="file" nwworkingdir="[[_pathOfSong(_editedSong.filepath)]]"/>
        </div>
      </div>
      <div class="fields">
        <div class="prev">&nbsp;<span>[[_taggedSong.album.artist]]</span></div>
        <paper-input label="Album Artist" value="{{_editedSong.album.artist}}" floatingLabel></paper-input>
        <div class="prev">&nbsp;<span>[[_taggedSong.album.name]]</span></div>
        <paper-input label="Album Name" value="{{_editedSong.album.name}}" required="true" floatingLabel></paper-input>
        <div class="prev">&nbsp;<span>[[_taggedSong.albumPart.pos]]</span></div>
        <paper-input label="POS" value="{{_editedSong.albumPart.pos}}" floatingLabel></paper-input>
        <div class="prev">&nbsp;<span>[[_taggedSong.albumPart.name]]</span></div>
        <paper-input label="Subtitle" value="{{_editedSong.albumPart.name}}" floatingLabel></paper-input>
        <div class="prev">&nbsp;<span>[[_taggedSong.album.label]]</span></div>
        <paper-input label="Label" value="{{_editedSong.album.label}}" floatingLabel></paper-input>
        <div class="prev">&nbsp;<span>[[_taggedSong.album.catalogId]]</span></div>
        <paper-input label="Catalog ID" value="{{_editedSong.album.catalogId}}" floatingLabel></paper-input>
        <paper-dropdown-menu label="Artist Genre" required>
          <paper-menu class="dropdown-content" selected="{{basicgenreName}}" attr-for-selected="label">
            <template is="dom-repeat" items="[[_basicGenreList]]">
              <paper-item label="[[item.name]]">[[item.name]]</paper-item>
            </template>
          </paper-menu>
        </paper-dropdown-menu>
        <div class="prev">&nbsp;<span>[[_taggedSong.album.releaseDateYear]]</span></div>
        <paper-input label="Release Year" value="{{_editedSong.album.releaseDateYear}}" required="true" type="number" min="1600" max="2099" floatingLabel></paper-input>
        <div class="prev">&nbsp;<span>[[_taggedSong.album.releaseDateMonth]]</span></div>
        <paper-input label="Release Month" value="{{_editedSong.album.releaseDateMonth}}" type="number" min="0" max="12" floatingLabel></paper-input>
        <div class="prev">&nbsp;<span>[[_taggedSong.album.releaseDateDay]]</span></div>
        <paper-input label="Release Day" value="{{_editedSong.album.releaseDateDay}}" type="number" min="0" max="31" floatingLabel></paper-input>
      </div>
      <div class="genres">
        <genre-list id="genreList" selection="{{_styles}}" single-select></genre-list>
      </div>
    </abstract-action-page>
    <div class="metadata">
      <div class="audio"><ss-audio id="audio" song="[[song]]"></ss-audio></div>
      <div>[[_editedSong.id]]</div>
      <div on-click="_changeSong">[[_editedSong.filepath]]</div>
      <input style="display:none;" id="songFileDialog" type="file" nwworkingdir="[[_pathOfSong(_editedSong.filepath)]]"/>
    </div>
    `;
  }
  static get properties() {
    return {
      song: {
        type: Object,
        observer: '_songChanged'
      },
      _newSongManager: {
        type: Object,
        value() { return new ss.NewSongManager(); },
        readOnly: true
      },
      _taggedSong: {
        type: Object,
        value() { return new ss.Song(); }
      },
      _editedSong: Object,
      filepaths: {
        type: Array,
        observer: '_filepathsChanged'
      },
      _styles: {
        type: Array,
        value() { return []; }
      },
      debounceTime: {
        type: Number,
        value: 750
      },
      _changedAlbumCover: {
        type: Boolean,
        value: false
      },
      _changedSongFile: {
        type: Boolean,
        value: false
      },
      _basicGenreList: {
        type: Array,
        value() { return ss.BasicGenre.findAll(); },
        readOnly: true
      },
      _soulSifterSettings: {
        type: Object,
        value() { return new ss.SoulSifterSettings(); },
        readOnly: true
      },
      _albumArtistCompilation: {
        type: Boolean,
        value: false
      },
    }
  }

    observers: [
      '_albumArtistChanged(_editedSong.album.artist)',
      '_artistChanged(_editedSong.artist)',
    ],

    attached() {
      Polymer.RenderStatus.afterNextRender(this, function() {
        this.$.abstractActionPage.setAcceptAction(this.save);
        this.$.abstractActionPage.setCancelAction(this.skip);
        // select file dialog
        var that = this;
        this.$.coverFileDialog.addEventListener("change", function(e) {
          that.$.cover.style.backgroundImage = 'url("file://' + this.value + '")';
          // TODO should move cover file in place
          that._editedSong.album.coverFilepath = that._editedSong.id ? this.value.replace(that._soulSifterSettings.getString('music.dir'), '') : this.value;
          that._changedAlbumCover = true;
        }, false);
        this.$.songFileDialog.addEventListener("change", function(e) {
          // TODO move song in place if out of place
          that._editedSong.filepath = that._editedSong.id ? this.value.replace(that._soulSifterSettings.getString('music.dir'), '') : this.value;
          that.notifyPath('_editedSong.filepath', that._editedSong.filepath);
          if (!!that._editedSong.id) that._changedSongFile = true;
        }, false);
      }.bind(this));
    }

    ready() {
      // used for moving cover files
      this.fs = require('fs');
      this.path = require('path');
    }

    save() {
      if (!this._validate()) return;
      // perhaps allow genre list to select a set of IDs in the future?
      var styleIds = this._styles.map(function(g) { return g.id; });
      this._editedSong.styleIds = styleIds;
      // If there is no album part, we should clear this object out so it is
      // not saved. Setting the ID deletes the object, and having an ID of 0
      // indicates a NULL value upon save.
      if (!this._editedSong.albumPart.pos && !this._editedSong.albumPart.name) {
        this._editedSong.albumPartId = 0;
      } else {
        // make sure this albumPart's album matches this edited album
        if (!!this._editedSong.album.id) this._editedSong.albumPart.albumId = this._editedSong.album.id;
        else this._editedSong.albumPart.album = this._editedSong.album;
      }
      // Since basicGenre objects should not be shared between objects, we will be
      // creating another basicGenre here regardless if we selected an object in the dropdown.
      this._editedSong.album.basicGenre = ss.BasicGenre.findByName(this.basicgenreName);

      // Moves files after song change
      if (this._changedSongFile && !!this._editedSong.id) {
        // TODO the file moving should be done externally
        // remove current song (copied to /var/tmp)
        var currentSongFilepath = this._soulSifterSettings.getString('music.dir') + this.song.filepath;
        var albumFilepath = this.path.dirname(this.song.filepath);
        var rmToTmpFilename = '/var/tmp/' + this.path.basename(this.song.filepath);
        this.fs.rename(currentSongFilepath, rmToTmpFilename);
        window.console.log('Renamed ' + currentSongFilepath + ' to ' + rmToTmpFilename);
        // copy new file to current albumFilepaths location
        var basename = this.path.basename(this._editedSong.filepath);
        var newpath = this._soulSifterSettings.getString('music.dir') + albumFilepath + '/' + basename;
        this.fs.rename(this._editedSong.filepath, newpath);
        window.console.log('Renamed ' + this._editedSong.filepath + ' to ' + newpath);
        this._editedSong.filepath = albumFilepath + '/' + basename;
      }

      if (this._editedSong.id) {
        this._editedSong.update();
        // TODO update song with changes
      } else {
        this._newSongManager.processSong(this._editedSong);
        this._albumArtistCompilation = !this._editedSong.album.albumArtist;
        if (this._hasMoreSongs()) {
          this.$.audio.pause();
          return;  // stay on this page
        }
        this._albumArtistCompilation = false;
      }

      // Currently you cannot edit the cover of newly added songs. The
      // NewSongManager processes it last, so anything changed will just be
      // overwritten.
      if (this._changedAlbumCover) {
        // TODO the file moving should be done externally
        var basename = this.path.basename(this._editedSong.album.coverFilepath);
        var dirname = this.path.dirname(this._editedSong.filepath);
        var newpath = this._soulSifterSettings.getString('music.dir') + dirname + '/' + basename;
        this.fs.rename(this._editedSong.album.coverFilepath, newpath);
        this._editedSong.album.coverFilepath = dirname + '/' + basename;
        this._editedSong.album.update();
      }

      this.$.audio.pause();
      this.$.abstractActionPage.exit();
    }

    skip() {
      if (this._hasMoreSongs()) {
        return;  // stay on this page
      }
      this._albumArtistCompilation = false;
      this.$.audio.pause();
      this.$.abstractActionPage.exit();
    }

    _filepathsChanged() {
      this._newSongManager.import(this.filepaths);
      if (!this._hasMoreSongs()) {
        // for some reason there is no song after importing filepaths, so just exit.
        this.$.audio.pause();
        this.$.abstractActionPage.exit();
      }
    }

    _songChanged() {
      if (!this.song) return;
      this._editedSong = new ss.Song(this.song);
      // Create album & album part for the song we are editing if there
      // currently does not exist one. It is not needed for the tagged song
      // since its purpose is only output.
      if (!this._editedSong.album) this._editedSong.album = new ss.Album();
      if (!this._editedSong.albumPart) {
        this._editedSong.albumPart = new ss.AlbumPart();
        this._editedSong.albumPart.album = this._editedSong.album;
      }
      if (!!this._editedSong.album.basicGenre) this.basicgenreName = this._editedSong.album.basicGenre.name;
      else this.basicgenreName = '';
      this.$.cover.style.backgroundImage = 'url("file://' + this._soulSifterSettings.getString('music.dir') + this._editedSong.album.coverFilepath + '")';
      this._changedAlbumCover = false;
      this._changedSongFile = false;
      // this does not seem to play well when working straight on the array object
      this._styles = this._editedSong.styles;
    }

    _hasMoreSongs() {
      // There is an issue to update the data bindings of the songs updated
      // from the nextSong call on NewSongManager. Because of the dirty
      // checking in notifyPath, and the internals of the object are updated
      // via a 3rd-party library, we cannot update the bindings.
      // There are two options:
      // 1. Create temporary song objects to get updated, then set the bound
      // objects to these values.
      // 2. Call _pathEffector which is the "private" method in polymer which
      // does the update calls of notifyPath without the dirty checking.
      // Going with option 1 for now. Even though it is creating extra objects,
      // it's relatively small, and we could make them private members ourself
      // if we care about memory that much. It should be better than being
      // bitten by using a method that is considered private and updated from
      // underneath us.
      var tmpSong = new ss.Song();
      var tmpTaggedSong = new ss.Song();
      if (this._newSongManager.nextSong(tmpSong, tmpTaggedSong)) {
        this._taggedSong = tmpTaggedSong;
        this.song = tmpSong;
        return true;
      }
      return false;
    }

    _validate() {
      var valid = 1;
      var inputs = this.shadowRoot.querySelectorAll('paper-input');
      for (var i = 0; i < inputs.length; ++i) {
        valid &= inputs[i].validate();
      }
      return valid;
    }

    _albumArtistChanged(artist) {
      if (!!artist && !this.basicgenreName) {
        this.debounce('findBasicGenreByArtist', function() {
          var basicGenre = ss.BasicGenre.findByArtist(artist);
          if (!!basicGenre) this.basicgenreName = basicGenre.name;
        }, this.debounceTime);
      }
    }

    _artistChanged(artist) {
      if (!!artist && !this._editedSong.album.artist && !this._albumArtistCompilation && !this._editedSong.album.id) {
        this.debounce('setAlbumArtist', function() {
          this._editedSong.album.artist = artist;
          this.notifyPath('_editedSong.album.artist', artist);
        }, this.debounceTime);
      }
    }

    _changeCover() {
      this.$.coverFileDialog.click();
    }

    _changeSong() {
      this.$.songFileDialog.click();
    }

    _pathOfSong(filename) {
      return this._soulSifterSettings.getString('music.dir') + this.path.dirname(filename);
    }
  }

window.customElements.define('song-edit', SongEdit);
