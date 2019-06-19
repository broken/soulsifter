// <link href="../polymer/polymer.html" rel="import">

// <link href="../paper-button/paper-button.html" rel="import">

import { html, PolymerElement } from "../polymer/polymer-element.js";

class AbstractActionPage extends PolymerElement {
  static get template() {
    return html`
    <custom-style>
      <style>
        :host {
          margin: 18px;
          position: absolute;
          top: 0;
          bottom: 0;
          right: 0;
          left: 0;
          display: flex;
          flex-direction: column;
          align-items: center;
          justify-content: center;
        }
        #layout {
          display: flex;
          flex-direction: row;
        }
        #abstractActions {
          padding-top: 30px;
          flex-shrink: 0;
        }
        paper-button.accent {
          color: var(--paper-button-accent);
        }

        /* customized paper-input styles so the label appears to the left */
        :host::shadow paper-input {
          position: relative;
          width: 240px;
        }
        :host::shadow paper-input::shadow paper-input-container {
          padding: 3px 0;
        }
        :host::shadow paper-input::shadow paper-input-container.paper-input div.input-content.label-is-floating.paper-input-container label {
          position: absolute;
          left: inherit !important;
          right: 260px;
          top: 23px;
          white-space: nowrap;
          transform-origin: right top;
        }
        /* mark the vertical blocks with class fields */
        :host::shadow .fields {
          @apply --layout-vertical;
          justify-content: center;
          margin-left: 200px;
        }
        :host::shadow .genres {
          padding-left: 30px;
          padding-right: 60px;
          overflow-y: scroll;
        }
      </style>
    </custom-style>
    <div id="layout">
      <slot></slot>
    </div>
    <div id="abstractActions">
      <paper-button on-click="cancel">Cancel</paper-button>
      <paper-button on-click="accept" class="accent">Accept</paper-button>
    </div>
    `;
  }
  static get properties() {
    return {
      doNotCallExit: {
        type: Boolean,
        value: false
      }
    }
  }

    setAcceptAction(a) {
      this.acceptAction = a;
    }

    setCancelAction(a) {
      this.cancelAction = a;
    }

    accept() {
      if (this.acceptAction) this.acceptAction.call(this.parentNode);
      if (!this.doNotCallExit) this.exit();
    }

    cancel() {
      if (this.cancelAction) this.cancelAction.call(this.parentNode);
      if (!this.doNotCallExit) this.exit();
    }

    exit() {
      this.fire('page-main');
    }
  }

window.customElements.define('abstract-action-page', AbstractActionPage);
