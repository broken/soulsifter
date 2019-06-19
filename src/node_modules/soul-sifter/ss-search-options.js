// <link href="../polymer/polymer.html" rel="import">

// <link href="../paper-toggle-button/paper-toggle-button.html" rel="import">

import { html, PolymerElement } from "../polymer/polymer-element.js";

class SearchOptions extends PolymerElement {
  static get template() {
    return html`
    <custom-style>
      <style>
        :host {
          display: flex;
          flex-direction: column;
          white-space: nowrap;
        }
        section {
          display: flex;
          flex-direction: row;
        }
        paper-toggle-button {
          padding-top: 3px;
          margin-left: 15px;
        }
        span {
          padding-left: 10px;
          margin-right: 15px;
        }
      </style>
    </custom-style>
    <section>
      <paper-toggle-button checked="{{searchOptionBpmRestrict}}"></paper-toggle-button>
      <span>BPM restrict</span>
      <paper-toggle-button checked="{{searchOptionKeyRestrict}}"></paper-toggle-button>
      <span>Key restrict</span>
      <paper-toggle-button checked="{{searchOptionTrashedRestrict}}"></paper-toggle-button>
      <span>Trashed restrict</span>
      <paper-toggle-button checked="{{searchOptionRepeatRestrict}}"></paper-toggle-button>
      <span>Repeat restrict</span>
    <section>
    `;
  }
  static get properties() {
    return {
      searchOptionBpmRestrict: {
        type: Boolean,
        notify: true,
        value: false
      },
      searchOptionKeyRestrict: {
        type: Boolean,
        notify: true,
        value: false
      },
      searchOptionTrashedRestrict: {
        type: Boolean,
        notify: true,
        value: false
      },
      searchOptionRepeatRestrict: {
        type: Boolean,
        notify: true,
        value: false
      },
    }
  }
}

window.customElements.define('ss-search-options', SearchOptions);
