/* Copyright 2018 MechMerlin
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

enum layers {
  BASE = 0,
  FUN1,
  FUN2
};

//prefer 1-char macros
//split backspace is supported (not using), but want to make it easier to read in the keymaps
//L for layer
#define L(...) MO(__VA_ARGS__)

//can't remember, but I think there was a good reason
#define LAYOUT2(...) LAYOUT(__VA_ARGS__)

#define M_START LCTL(KC_HOME)
#define M_END LCTL(KC_END)


void tap_cap_fun2_fin(qk_tap_dance_state_t *state, void *user_data);
void tap_cap_fun2_rst(qk_tap_dance_state_t *state, void *user_data);
enum {
  TD_CP2
};
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_CP2]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tap_cap_fun2_fin, tap_cap_fun2_rst)
};

#define TP(td) TD(TD_##td)

bool has_mod(uint16_t mod) {
  return get_mods() & MOD_BIT(mod);
}
bool has_ime_mod(void) {
  return
    has_mod(KC_LALT) ||
    has_mod(KC_LCTL) ||
    has_mod(KC_LSFT);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void tap_cap_fun2_fin(qk_tap_dance_state_t *state, void *user_data) {
  //special case for IME
  if (state->count == 1 && !state->pressed && has_ime_mod()) {
    register_code(KC_CAPS);
    reset_tap_dance(state); //occassionally will double-tap caps to get to katakana
    return;
  }

  if (state->pressed) {
    layer_on(FUN2);
  }
  else if (state->count == 2) {
    register_code(KC_CAPS);
  }
  else if (state->count > 2)
  {
    //tap dance isnt working after the first double tap. though holding it works
    //I'm assuming this will help
    reset_tap_dance(state);
  }
}

void tap_cap_fun2_rst(qk_tap_dance_state_t *state, void *user_data) {
  layer_off(FUN2);
}

//note that the top two keys on the right are reversed

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[BASE] = LAYOUT_96_ansi(\
    KC_ESC , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 , KC_PSCR, KC_SLCK,     KC_DEL , KC_HOME, KC_PGUP, L(FUN2), \
    KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS, KC_EQL , KC_BSPC,              KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS, \
    KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_LBRC, KC_RBRC, KC_BSLS,              KC_P7  , KC_P8  , KC_P9  , KC_NO  , \
    TP(CP2), KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT, KC_ENT ,                       KC_P4  , KC_P5  , KC_P6  , KC_PPLS, \
    KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT, KC_NO  ,                       KC_P1  , KC_P2  , KC_P3  ,          \
    KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC ,                   KC_RALT, L(FUN1), KC_APP , KC_RCTL,                                KC_P0  , KC_P0  , KC_PDOT, KC_PENT
    ),

[FUN1] = LAYOUT_96_ansi(\
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
    KC_TRNS, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 , KC_TRNS,              KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
    KC_TRNS, KC_TRNS, KC_UP  , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,              KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
    KC_CAPS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                       KC_TRNS, KC_TRNS, KC_TRNS,          \
    KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),

[FUN2] = LAYOUT_96_ansi(\
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_VOLU, KC_MPRV, KC_MNXT, KC_TRNS, \
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,              KC_VOLD, KC_MSTP, KC_MPLY, KC_TRNS, \
    KC_TRNS, M_END  , KC_PGUP, M_START, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,              KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
    KC_TRNS, KC_HOME, KC_PGDN, KC_END , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                       KC_TRNS, KC_TRNS, KC_TRNS,          \
    KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                KC_TRNS, KC_TRNS, KC_TRNS, RESET
    ),
};

