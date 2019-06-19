// <link href="../polymer/polymer.html" rel="import">

// <link href="../paper-icon-button/paper-icon-button.html" rel="import">
// <link href="../paper-material/paper-material.html" rel="import">

import { html, PolymerElement } from "../polymer/polymer-element.js";

class OptionsMenu extends PolymerElement {
  static get template() {
    return html`
    <custom-style>
      <style>
        :host {
          position: relative;
          height: 33px;
        }
        #btn {
          line-height: inherit;
          vertical-align: top;
        }
        #menu {
          background-color: var(--ss-options-button-menu-background-color);
          padding: 15px;
          position: absolute;
          top: 6px;
          right: 8px;
          border-radius: 2px;
          display: block;
          opacity: 1;
          transition: opacity 1s;
          z-index: 1;
        }
        #menu.hide {
          display: none;
          opacity: 0;
        }
      </style>
    </custom-style>
    <paper-icon-button id="btn" icon="more-vert"></paper-icon-button>
    <paper-material id="menu" class="hide" elevation="3">
      <slot></slot>
    </paper-material>
    </div>
    `;
  }
    listeners: {
      'click': '_openMenu',
    }

    _openMenu(e) {
      this.$.menu.classList.toggle('hide');
      this._closeMenu = function(e) {
        this.$.menu.classList.toggle('hide');
        document.removeEventListener('click', this._closeMenu, true);
      }.bind(this);
      document.addEventListener('click', this._closeMenu, true);
      e.stopPropagation();
    }
  }
}

window.customElements.define('ss-options-menu', OptionsMenu);
