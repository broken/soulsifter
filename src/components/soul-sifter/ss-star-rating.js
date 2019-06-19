// <link href="../polymer/polymer.html" rel="import">

// <link href="../iron-icon/iron-icon.html" rel="import">

import { html, PolymerElement } from "../polymer/polymer-element.js";

class StarRating extends PolymerElement {
  static get template() {
    return html`
    <custom-style>
      <style>
        :host {
          white-space: nowrap;
          color: var(--ss-star-rating-color);
        }
        :host(.trashed) {
          color: var(--ss-star-rating-trashed-color);
        }
        iron-icon {
          height: 13px;
          width: 13px;
          color: inherit;
        }
        iron-icon[selected] {
          color: var(--ss-star-rating-selected-color);
        }
      </style>
    </custom-style>
    <template is="dom-repeat" items="[[stars]]">
      <iron-icon icon="star" selected$="[[_isSelected(item, value)]]" on-click="_select"></iron-icon>
    </template>
    `;
  }
  static get properties() {
    return {
      count: {
        type: Number,
        value: 5
      },
      value: {
        type: Number,
        value: 0,
        notify: true
      },
      readOnly: {
        type: Boolean,
        value: false
      },
      stars: {
        type: Array,
        computed: '_computeStars(count)',
        readOnly: true
      }
    }
  }

    _computeStars(count) {
      var stars = [];
      for (var i = 0; i < count; ++i) {
        stars.push(i);
      }
      return stars;
    }

    _isSelected(item, value) {
      return item < value;
    }

    _select(e) {
      if (!this.readOnly)
        this.value = e.model.item + 1;
    }
}

window.customElements.define('ss-star-rating', StarRating);
