// <link href="../polymer/polymer.html" rel="import">

// <link href="../iron-flex-layout/iron-flex-layout.html" rel="import">
// <link href="../iron-icon/iron-icon.html" rel="import">
// <link href="../iron-icons/av-icons.html" rel="import">
// <link href="../paper-slider/paper-slider.html" rel="import">

// <link href="ss-googleplaymusic.html" rel="import">

import { html, PolymerElement } from "../polymer/polymer-element.js";

class Audio extends PolymerElement {
  static get template() {
    return html`
    <custom-style>
      <style>
        :host {
          margin: 4px 0;
        }

        paper-slider {
          width: 100%;
        }
        paper-slider::shadow #sliderContainer {
          margin: 0;
          height: 4px;
          width: 100%;
        }
        paper-slider::shadow .bar-container {
          left: 4px;
          width: calc(100% - 4px);
        }
        paper-slider::shadow .bar-container #sliderBar{
          top: 0;
          height: 4px;
          margin: 0;
          padding: 0;
        }
        paper-slider::shadow #sliderKnob {
          display: none;
        }

        .horizontal {
          @apply --layout-horizontal;
        }

        .timebar {
          width: 100%;
          @apply --layout-vertical --layout-flex;
        }
      </style>
    </custom-style>
    <ss-googleplaymusic id="gpm"></ss-googleplaymusic>
    <div class$="{{computeIsDisabled(disabled)}}">
      <iron-icon id="playPause" icon="av:play-arrow" on-click="playAction"></iron-icon>
      <div class="timebar">
        <div id="time" self-end>[[_currentTimeStr]]</div>
        <paper-slider id="slider" min="0" max="{{duration}}" value="{{currentTime}}" on-change="changeCurrentTime" disabled="{{disabled}}"></paper-slider>
      </div>
    </div>
    `;
  }
  static get properties() {
    return {
      song: {
        type: Object,
        observer: '_songChanged'
      },
      src: {
        type: String,
        observer: '_srcChanged'
      },
      _soulSifterSettings: {
        type: Object,
        value() { return new ss.SoulSifterSettings(); },
        readOnly: true
      },
      _currentTimeStr: {
        type: String,
        value: 'Ø',
      },
      disabled: {
        type: Boolean,
        value: true,
      },
      duration: {
        type: Number,
        value: 1,
      },
      currentTime: {
        type: Number,
        value: 0,
      },
    }
  }

    ready() {
      this.fs = require('fs');
    }

    _songChanged(newValue, oldValue) {
      this.set('_currentTimeStr', 'Ø');
      if (!newValue) {
        this.set('src', null);
        return;
      }

      // audio source; use local, otherwise contact google api
      var filepath = this.song.filepath.charAt(0) === '/' ? this.song.filepath : this._soulSifterSettings.getString('music.dir') + this.song.filepath;
      this.fs.access(filepath, this.fs.F_OK | this.fs.R_OK, (err) => {
        if (!err) {
          this.set('src', 'file://' + filepath);
        } else {
          if (!this.song.googleSongId) {
            console.warn('Unable to play song ' + this.song.id + ' because it does not have a Google song ID associated with it.');
          } else {
            this.$.gpm.getStreamUrl(this.song.googleSongId, (err, url) => {
              if (err) {
                console.error('Unable to get stream URL for song ' + this.song.id);
                console.error(err);
              } else {
                this.set('src', url);
              }
            });
          }
        }
      });

    }

    _srcChanged(newValue, oldValue) {
      this.currentTime = 0;
      if (!newValue) {
        this.disabled = true;
        return;
      }

      this.audio = new Audio(newValue);
      var that = this;
      this.audio.addEventListener('durationchange', function() {
        that.duration = that.audio.duration;
        that.disabled = false;
      });
      this.audio.addEventListener('ended', function() {
        that.$.playPause.icon = 'av:play-arrow';
      });
      this.audio.addEventListener('error', function (mediaError) {
        window.console.log('Audio error: ' + mediaError.code);
        that._currentTimeStr = 'Ø',
        that.disabled = true;
      });
      this.audio.addEventListener('timeupdate', function () {
        that.currentTime = that.audio.currentTime;

        // set the current time in readable string format
        var str = '';
        var time = that.currentTime|0;
        var hours = Math.floor(time / 3600);
        if (hours) str += hours + ':';
        time %= 3600;
        var mins = Math.floor(time / 60);
        if (hours || mins) str += (mins < 10 && hours ? '0' : '') + mins + ':';
        var secs = time % 60;
        str += (secs < 10 && (hours || mins) ? '0' : '') + secs;
        that._currentTimeStr = str;
      });
    }

    playAction() {
      if (this.$.playPause.icon === 'av:play-arrow') {
        this.play();
      } else {
        this.pause();
      }
    }

    play() {
      if (this.disabled) return;
      this.audio.play();
      this.$.playPause.icon = 'av:pause';
    }

    pause() {
      if (this.disabled) return;
      this.audio.pause();
      this.$.playPause.icon = 'av:play-arrow';
    }

    changeCurrentTime(event, detail, sender) {
      this.audio.currentTime = this.$.slider.immediateValue;
    }

    computeIsDisabled(isDisabled) {
      return (isDisabled ? "disabled " : "") + "horizontal";
    }
  }

window.customElements.define('ss-audio', Audio);
