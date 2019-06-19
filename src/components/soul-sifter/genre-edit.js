// <link href="../polymer/polymer.html" rel="import">

// <link href="../paper-input/paper-input.html" rel="import">

// <link href="abstract-action-page.html" rel="import">
// <link href="genre-list.html" rel="import">

import { html, PolymerElement } from "../polymer/polymer-element.js";

class GenreEdit extends PolymerElement {
  static get template() {
    return html`
    <custom-style>
      <style>
      </style>
    </custom-style>
    <abstract-action-page id="abstractActionPage">
      <div class="fields">
        <paper-input floatingLabel label="Name" value="{{genre.name}}"></paper-input>
      </div>
      <div class="genres">
        <genre-list id="genreList" selection="{{_genreParents}}" single-select></genre-list>
      </div>
    </abstract-action-page>
    `;
  }
  static get properties() {
    return {
      genre: {
        type: Object,
        observer: '_genereChanged'
      },
      _genreParents: {
        type: Array,
        value() { return []; }
      },
    }
  }

    attached() {
      Polymer.RenderStatus.afterNextRender(this, function() {
        this.$.abstractActionPage.setAcceptAction(this.save);
      }.bind(this));
    }

    save(e, detail, sender) {
      var genreParentIds = this._genreParents.map(function(g) { return g.id; });
      this.genre.parentIds = genreParentIds;
      if (this.genre.id) {
        this.genre.update();
      } else {
        this.genre.save();
      }
      this.fire('iron-signal', {name: 'genres-changed'});
    }

    _genereChanged() {
      // this does not seem to play well when working straight on the array object
      this._genreParents = this.genre.parents;
    }
  }

window.customElements.define('genre-edit', GenreEdit);
