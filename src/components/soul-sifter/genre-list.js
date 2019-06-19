// <link href="../polymer/polymer.html" rel="import">

// <link href="genre-list-item.html" rel="import">

import { html, PolymerElement } from "../polymer/polymer-element.js";

class GenreList extends PolymerElement {
  static get template() {
    return html`
    <custom-style>
      <style>
        paper-fab {
          bottom: 15px;
          position: relative;
          left: 182px;
        }
      </style>
    </custom-style>
    <template is="dom-repeat" items="[[genreParents]]">
      <genre-list-item genre="[[item]]" on-genre-select="_selectGenre" single-select="[[singleSelect]]" main="[[main]]"></genre-list-item>
    </template>
    <paper-fab mini icon="add" on-click="_createGenre" hidden$="[[!main]]"></paper-fab>
    `;
  }
  static get properties() {
    return {
      genreParents: {
        type: Array,
        value() { return ss.Style.findAllParents().sort(this._compareGenres); }
      },
      selection: {
        type: Array,
        value() { return []; },
        notify: true,
        observer: '_selectionChanged'
      },
      singleSelect: {
        type: Boolean,
        value: false,
      },
      main: {
        type: Boolean,
        value: false,
      },
    }
  }

    _selectionChanged(genres) {
      for (var i = 0, childNodes = this.shadowRoot.querySelectorAll('genre-list-item');
           i < childNodes.length; ++i) {
        childNodes[i].selectIffInArray(genres);
      }
    }

    _selectGenre(e, detail) {
      for (var i = 0; i < this.selection.length; ++i) {
        if (this.selection[i].id == detail.genre.id) {
          this.splice('selection', i, 1);
          return;
        }
      }
      var g = new ss.Style(detail.genre);
      this.push('selection', g);
    }

    _createGenre(e, detail, sender) {
      var genre = new ss.Style();
      this.fire('page-genre-edit', {genre: genre});
    }
    
    _compareGenres(a, b) {
      return a.name.localeCompare(b.name);
    }
  }

window.customElements.define('genre-list', GenreList);
