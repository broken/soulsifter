// <link href="../polymer/polymer.html" rel="import">

// <link href="../iron-collapse/iron-collapse.html" rel="import">
// <link href="../iron-flex-layout/iron-flex-layout.html" rel="import">
// <link href="../paper-icon-button/paper-icon-button.html" rel="import">
// <link href="../paper-material/paper-material.html" rel="import">
// <link href="../paper-ripple/paper-ripple.html" rel="import">

// <link href="ss-options-menu.html" rel="import">
// <link href="ss-options-menu-item.html" rel="import">

import { html, PolymerElement } from "../polymer/polymer-element.js";

class GenreListItem extends PolymerElement {
  static get template() {
    return html`
    <custom-style>
      <style>
        paper-ripple {
          color: var(--ss-genre-list-item-ripple-color);
        }
        paper-icon-button {
          transform: scale(.6);
        }

        iron-collapse {
          margin-top: -7px;
          margin-bottom: -7px;
        }

        #itemContainer {
          margin: 7px 20px 0 20px;
          height: 30px;
        }
        #item {
          height: 30px;
          @apply --layout-horizontal;
          @apply --layout-center;
        }

        .flex {
          @apply --layout-flex;
        }

        .selected {
          background-color: var(--ss-genre-list-item-select-color);
        }

        ss-options-menu {
          --iron-icon-height: 16px;
          --iron-icon-width: 16px;
        }
        #item ss-options-menu::shadow #btn {
          display: none;
        }
        #item:hover ss-options-menu::shadow #btn {
          display: block;
        }
      </style>
    </custom-style>
    <div id="itemContainer">
      <paper-material class$="[[_computeSelectedClass(isSelected)]]" style$="[[_computePaddingLeftStyle(indent)]]" on-tap="_toggleSelect" id="item" elevation="0">
        <paper-ripple></paper-ripple>
        <paper-icon-button icon="[[icon]]" on-tap="_toggleExpansion"></paper-icon-button>
        <div class="flex">[[genre.name]]</div>
        <ss-options-menu hidden$="[[!main]]">
          <ss-options-menu-item on-click="_editAction">Edit genre</ss-options-menu-item>
        </ss-options-menu>
      </paper-material>
    </div>
    <iron-collapse id="collapse" opened="{{opened}}">
      <template is="dom-repeat" items="[[_getSubGenres(genre)]]" id="subGenreTpl">
        <genre-list-item genre="[[item]]" indent="[[_incIndent(indent)]]" on-expand-parents="expand" single-select="[[singleSelect]]" main="[[main]]"></genre-list-item>
      </template>
    </iron-collapse>
    `;
  }
  static get properties() {
    return {
      genre: Object,
      indent: {
        type: Number,
        value: 0
      },
      isSelected: {
        type: Boolean,
        value: false
      },
      opened: {
        type: Boolean,
        value: false
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

    _getSubGenres(genre) {
      return genre.children.sort(this._compareGenres);
    }

    /** @event genre-select */

    select(isSelected) {
      if ((isSelected && !this.isSelected) ||
          (!isSelected && this.isSelected)) {
        this.isSelected = !this.isSelected;
        this._signalGenreToggle();
      }
      if (!this.singleSelect && this.genre.subGenre && this.genre.subGenre.length > 0) {
        for (var i = 0, childNodes = Polymer.dom(this.$.collapse).childNodes;
             i < childNodes.length; ++i) {
          if (childNodes[i].nodeName === 'GENRE-LIST-ITEM') {
            childNodes[i].select(isSelected);
          }
        }
      }
    }

    selectIffInArray(genres) {
      if (!genres) return;
      // select this and request parents to expand if found in array
      var selected = false;
      for (var i = 0; i < genres.length; ++i) {
        if (genres[i].id === this.genre.id) {
          selected = true;
          this.fire('expand-parents');
        }
      }
      this.opened = false;
      this.isSelected = selected;
      // have all child elements check if they're in the array
      for (var i = 0, childNodes = this.$.collapse.querySelectorAll('genre-list-item');
           i < childNodes.length; ++i) {
        childNodes[i].selectIffInArray(genres);
      }
    }

    expand() {
      this.opened = true;
      this.fire('expand-parents');
    }

    ready() {
      var children = this.genre.children.sort(this._compareGenres);
      if (children.length > 0) {
        this.genre.subGenre = children;
      }
      if (this.genre.subGenre) {
        this.icon = 'expand-more';
      } else {
        this.icon = 'invis';
      }
    }

    _toggleSelect(e, detail, sender) {
      this.select(!this.isSelected);
    }

    _toggleExpansion(e, detail, sender) {
      if (!this.genre.subGenre || this.genre.subGenre.length <= 0) return;
      this.$.collapse.toggle();
      this.icon = this.opened ? 'expand-less' : 'expand-more';
      e.stopPropagation();  // TODO remove
    }

    _signalGenreToggle() {
      this.fire('genre-select', {genre: this.genre});
    }

    _incIndent(indent) {
      return indent + 20;
    }

    _computeSelectedClass(isSelected) {
      return isSelected ? "selected" : "";
    }

    _computePaddingLeftStyle(indent) {
      return 'padding-left: ' + indent + 'px;';
    }

    _compareGenres(a, b) {
      return a.name.localeCompare(b.name);
    }

    _editAction(e, detail, sender) {
      e.preventDefault();
      this.fire('page-genre-edit', {genre: this.genre});
    }
  }

window.customElements.define('genre-list-item', GenreListItem);
