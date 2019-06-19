// <link href="../polymer/polymer.html" rel="import">

// <link href="../paper-ripple/paper-ripple.html" rel="import">

import { html, PolymerElement } from "../polymer/polymer-element.js";

class OptionsMenuItem extends PolymerElement {
  static get template() {
    return html`
    <custom-style>
      <style>
        :host {
          line-height: 22px;
          margin: 2px;
          position: relative;
          display: block;
          white-space: nowrap;
        }
        :host:hover {
          color: var(--secondary-text-color);
          background-color: var(--ss-options-button-menu-item-hover-color);
        }
      </style>
    </custom-style>
    <slot></slot>
    <paper-ripple></paper-ripple>
    `;
  }
}

window.customElements.define('ss-options-menu-item', OptionsMenuItem);

