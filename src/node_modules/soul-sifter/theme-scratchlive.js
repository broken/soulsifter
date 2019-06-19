@inherit: inherit;
@black: black;
@osx_grey: #B1B1B1;

@sl_blue: #1EC8FA;
@sl_brown: #6E330A;
@sl_green: #39FF7E;
@sl_grey: #292929;
@sl_orange: #FDC443;
@sl_purple: #AC1AFA;

// main
@bg: @sl_grey;
@clr: #999999;
@clr_bold: #CCCCCC;
@err: #F92772;
// star rating
@sr_clr: #666;
@sr_selected: #EEE;
@sr_trashed: #833;
// paper menu
@pm_bg: #161616;
@pm_bghover: @black;
// paper input
@pi_accent: @sl_blue;
// paper toggle button
@pb_clr: @sl_blue;
// paper alert toast
@pt_bg: @sl_orange;
@pt_clr: @black;
// abstract actions
@aa_ok: @sl_orange;
// drawer tabs
@dt_bg: #1F1F1F;
@dt_clr: @inherit;
@dt_bar: @sl_orange;
@dt_ink: @sl_orange;
// genre list
@gl_ink: @sl_orange;
@gl_select: @sl_brown;
// playlist list
@pl_fab: @sl_brown;
// search toolbar
@st_bg: @black;
// pitch slider
@ps_clr: @sl_blue;
@ps_bg: #999;
// search info
@si_heading: #CCC;
@si_emphasis: @sl_green;
// song list
@sl_border: 1px solid #2F2F2F;
@sl_hover: rgb(20,20,20);
@sl_fadeout: linear-gradient(to right, rgba(41,41,41,0), rgba(41,41,41,1));
@sl_hoverfadeout: linear-gradient(to right, rgba(20,20,20,0), rgba(20,20,20,1));
@sl_btnborder: 1px solid rgb(20,20,20);
@sl_btnborderhover: 1px solid #999999;
@sl_energy0: @bg;
@sl_energy1: #0066ff;
@sl_energy2: #00ccff;
@sl_energy3: #00ffff;
@sl_energy4: #00ffb0;
@sl_energy5: #00ff00;
@sl_energy6: #99ff00;
@sl_energy7: #ffff00;
@sl_energy8: #ff9900;
@sl_energy9: #ff5500;
@sl_energy10: #ff2266;
// audio
@au_play: #CCC;
@au_disabled: #999;

// <script>
//   CoreStyle.g.theme.init = function() {
//     CoreStyle.g.paperInput.labelColor = CoreStyle.g.theme.clr;
//     CoreStyle.g.paperInput.focusedColor = CoreStyle.g.theme.pi_accent;
//   };
// </script>

/*<style is="custom-style">*/
  /** main **/
  soul-sifter {
    --dark-primary-color: #303f9f;
    --default-primary-color: #3f51b5;
    --light-primary-color: #c5cae9;
    --text-primary-color: #ffffff;
    --accent-color: #ff4081;
    --primary-background-color: @bg;
    --primary-text-color: @clr;
    --secondary-text-color: @clr_bold;
    --disabled-text-color: #bdbdbd;
    --divider-color: #e0e0e0;

    /* paper elements */
    --paper-button-accent: @aa_ok;
    --paper-input-container-color: @clr;
    --paper-input-container-focus-color: @pi_accent;
    --paper-input-container-invalid-color: @err;
    --paper-input-container-input-color: @clr;
    --paper-item-min-height: 13px;
    --paper-tab-ink: @dt_ink;
    --paper-tabs-selection-bar-color: @dt_bar;

    /* paper mixins */
    --paper-tab-bg: @dt_bg;

    /* soulsifter elements */
    --ss-genre-list-item-ripple-color: @gl_ink;
    --ss-genre-list-item-select-color: @gl_select;
    --ss-options-button-menu-background-color: @pm_bg;
    --ss-options-button-menu-item-hover-color: @pm_bghover;
    --ss-playlist-list-item-selected-background-color: @gl_select;
    --ss-search-info-heading-color: @si_heading;
    --ss-search-info-emphasis-color: @si_emphasis;
    --search-toolbar-background: @st_bg;
    --ss-song-list-item-border-bottom: @sl_border;
    --ss-song-list-item-hover-background-color: @sl_hover;
    --ss-song-list-item-artist-color: @clr;
    --ss-song-list-item-title-color: @clr_bold;
    --ss-song-list-item-fade-out: @sl_fadeout;
    --ss-song-list-item-hover-fade-out: @sl_hoverfadeout;
    --ss-song-list-item-button-border: @sl_btnborder;
    --ss-song-list-item-button-hover-border: @sl_btnborderhover;
    --ss-song-list-item-energy-0: @sl_energy0;
    --ss-song-list-item-energy-1: @sl_energy1;
    --ss-song-list-item-energy-2: @sl_energy2;
    --ss-song-list-item-energy-3: @sl_energy3;
    --ss-song-list-item-energy-4: @sl_energy4;
    --ss-song-list-item-energy-5: @sl_energy5;
    --ss-song-list-item-energy-6: @sl_energy6;
    --ss-song-list-item-energy-7: @sl_energy7;
    --ss-song-list-item-energy-8: @sl_energy8;
    --ss-song-list-item-energy-9: @sl_energy9;
    --ss-song-list-item-energy-10: @sl_energy10;
    --ss-star-rating-color: @sr_clr;
    --ss-star-rating-selected-color: @sr_selected;
    --ss-star-rating-trashed-color: @sr_trashed;
  }

  /** paper toggle button **/
  paper-toggle-button::shadow [checked] .toggle-ink {
    color: @pb_clr;
  }
  paper-toggle-button::shadow [checked] .toggle {
    background-color: @pb_clr;
  }

  /** paper toast (alert) **/
  paper-toast {
    background-color: @pt_bg;
    color: @pt_clr;
  }

  /** playlist list **/
  paper-fab {
    background-color: @pl_fab;
    color: @clr_bold;
  }
  playlist-list-item::shadow paper-ripple {
    color: @gl_ink;
  }

  /** pitch slider **/
  paper-slider::shadow #sliderBar::shadow #activeProgress {
    background-color: @ps_clr;
  }
  paper-slider::shadow #sliderKnobInner {
    background-color: @ps_clr;
  }
  paper-slider::shadow #sliderKnobInner::before {
    background-color: @ps_clr;
  }
  paper-slider::shadow #sliderBar::shadow #secondaryProgress {
    background-color: @ps_bg;
  }
  paper-slider::shadow #sliderBar::shadow #progressContainer {
    background-color: @ps_bg;
  }

  /** audio **/
  ss-audio::shadow core-icon {
    color: @au_play;
  }
  ss-audio::shadow .disabled core-icon {
    color: @au_disabled;
  }
/*</style>*/
