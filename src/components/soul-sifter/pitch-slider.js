// <link href="../polymer/polymer.html" rel="import">

// <link href="../paper-slider/paper-slider.html" rel="import">

// <link href="ss-global-behavior.html" rel="import">

import { html, PolymerElement } from "../polymer/polymer-element.js";

class PitchSlider extends PolymerElement {
  static get template() {
    return html`
    <custom-style>
      <style>
        paper-slider::shadow paper-input::shadow paper-input-decorator {
          padding: 0 0 2px 0;
        }
        paper-slider::shadow paper-input::shadow input[is="core-input"] {
          margin: 0.25em 0;
        }
        paper-slider::shadow #sliderContainer {
          margin: 0;
        }
      </style>
    </custom-style>
    <paper-slider editable pin value="{{pitch}}" step="0.1" min="{{pitchPctMin}}" max="{{pitchPctMax}}"></paper-slider>
    `;
  }
  static get properties() {
    return {
      pitch: {
        type: Number,
        value: 0,
        observer: '_pitchChanged'
      },
      pitchPctMax: {
        type: Number,
        value: 8
      },
      pitchPctMin: {
        type: Number,
        value: -8
      },
      // indicates whether the pitch was changed internally from a bpm or song change, or externally by a user moving the pitch bar. only a user initiated pitch change causes the bpm to update.
      _userPitchChange: {
        type: Boolean,
        value: true
      }
    }
  }

    behaviors: [
      GlobalBehavior
    ],

    observers: [
      '_globalBpmChanged(global.bpm)',
      '_globalSongChanged(global.song)'
    ],

    // Used for comparing BPMs when determining pitch shifts
    _canonicalizeBpm(bpm) {
      if (bpm === 0) return bpm;
      if (bpm >= 150) return this._canonicalizeBpm(bpm / 2);
      if (bpm < 75) return this._canonicalizeBpm(bpm * 2);
      return bpm;
    }

    _globalSongChanged(song) {
      if (!song || !song.bpm) return;
      if (!this.global.bpm) {
        this.set('global.bpm', parseFloat(song.bpm).toFixed(1));
      } else {
        this._updatePitch();
      }
    }

    _globalBpmChanged(bpm) {
      this._updatePitch();
    }

    _pitchChanged(newValue, oldValue) {
      if (this._userPitchChange && this.global && this.global.song && this.global.song.bpm) {
        this.set('global.bpm', (this.global.song.bpm * (this.pitch/100) + this.global.song.bpm * 1).toFixed(1));
      }
      // we debounce the reset here since changing the bpm can cause the pitchChanged observer to be called multiple times
      var that = this;
      this.debounce('pitch-changed', function() {
        that._userPitchChange = true;
      }, 50);
    }

    _updatePitch() {
      if (!this.global || !this.global.bpm || !this.global.song || !this.global.song.bpm) return;
      this._userPitchChange = false;
      var pitch = this._canonicalizeBpm(this.global.bpm) / this._canonicalizeBpm(this.global.song.bpm);
      pitch = (pitch - 1) * 100;
      if (pitch > this.pitchPctMax) pitch = this.pitchPctMax;
      if (pitch < this.pitchPctMin) pitch = this.pitchPctMin;
      this.pitch = pitch;
    }
  }

window.customElements.define('pitch-slider', PitchSlider);
