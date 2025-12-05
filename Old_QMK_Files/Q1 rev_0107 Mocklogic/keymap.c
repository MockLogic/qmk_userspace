/* Copyright 2021 @ Keychron (https://www.keychron.com)
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

#include "rgb_matrix_map.h"

#define MAC_BASE 0
#define MAC_FN 1
#define _BASE 2
#define _SPACE 3
#define _MOUSE 4
#define _FN1 5
#define _GAME 6
#define _FN2 7
#define _LEADER 8
#define _RGB 9
#define _ASHIFT 10
#define _NUM 11
#define _KID 12

// Tap Dance declarations
enum {
	TD_ESC_GM,
	TD_ESC_KID
};

enum custom_keycodes {
    KC_MISSION_CONTROL = SAFE_RANGE,
    KC_LAUNCHPAD,
    KC_LOPTN,
    KC_ROPTN,
    KC_LCMMD,
    KC_RCMMD,
    KC_TASK_VIEW,
    KC_FILE_EXPLORER,
	MRED,
	MORN,
	MYEL,
	MCRT,
	MGRN,
	MSGN,
	MCYN,
	MAZR,
	MBLU,
	MVLT,
	MMAG,
	MRSE,
	MFAC,
	MFCW,
	MFWHT,
	TJIGGLE,
	SELWORD
};

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for layer toggle
	[TD_ESC_GM] = ACTION_TAP_DANCE_LAYER_TOGGLE(KC_ESC, _GAME),
	// Tap once for nothing, twice for layer toggle
	[TD_ESC_KID] = ACTION_TAP_DANCE_LAYER_TOGGLE(KC_NO, _KID)
};

typedef struct PACKED {
    uint8_t len;
    uint8_t keycode[2];
} key_combination_t;

key_combination_t key_comb_list[2] = {
    {2, {KC_LWIN, KC_TAB}},
    {2, {KC_LWIN, KC_E}}
};

#define KC_MCTL KC_MISSION_CONTROL
#define KC_LPAD KC_LAUNCHPAD
#define KC_TASK KC_TASK_VIEW
#define KC_FLXP KC_FILE_EXPLORER

static uint8_t mac_keycode[4] = { KC_LOPT, KC_ROPT, KC_LCMD, KC_RCMD };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_ansi_82(
        KC_ESC,   KC_BRID,  KC_BRIU,  KC_MCTL,  KC_LPAD,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,   KC_VOLU,  KC_DEL,             KC_MUTE,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,   KC_EQL,   KC_BSPC,            KC_PGUP,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,   KC_RBRC,  KC_BSLS,            KC_PGDN,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,             KC_ENT,             KC_HOME,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,             KC_RSFT,  KC_UP,
        KC_LCTL,  KC_LOPTN, KC_LCMMD,                               KC_SPC,                                 KC_RCMMD,MO(MAC_FN), KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [MAC_FN] = LAYOUT_ansi_82(
        _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,    KC_F12,   _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,            _______,
        RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  NK_TOGG,  _______,  _______,  _______,  _______,  _______,   _______,  RESET,              _______,
        _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  _______,  _______,  _______,  _______,  _______,  _______,             _______,            _______,
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,             _______,  _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,   _______,  _______,  _______,  _______),

    [_BASE] = LAYOUT_ansi_82(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,          KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_MYCM,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          G(KC_V),
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           G(KC_D),
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(_FN1), SELWORD, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    // Space Cadet Shift overlay. Double tap Esc or re-use Function 9 or 0 to turn off.
    [_SPACE] = LAYOUT_ansi_82(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        KC_LSPO,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_RSPC, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),

    // Mouse Layer where arrow keys move the mouse, Right Control is left click, and End is Right click.
    [_MOUSE] = LAYOUT_ansi_82(
        TG(_MOUSE), _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______, _______,          _______,
        _______,  _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______, _______,            KC_NO,  
        _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______, _______,            KC_NO,  
        _______,  _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,            _______,          KC_BTN2,  
        KC_LSFT,             _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______, KC_RSFT,   KC_MS_U,		
        _______,  _______,   _______,                              _______,                               _______,   _______,   KC_BTN1,   KC_MS_L, KC_MS_D, KC_MS_R
    ),

    // The function keys.
	// Space Cadet Shift and the Mouse Layer are over ridden on this layer.  
    [_FN1] = LAYOUT_ansi_82(
        DM_RSTP, DM_REC1, DM_REC2, _______, RCS(KC_ESC), _______, _______, _______, _______, KC_MPLY, KC_MPRV, KC_MNXT, KC_MSTP, KC_INS,          LCTL(KC_0),
        _______, DM_PLY1, DM_PLY2, _______, _______, _______, _______, _______, _______, TG(_SPACE), TG(_SPACE), _______, _______, EEP_RST,         KC_HOME,
        _______, _______, MFCW,    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RESET,                 KC_PGUP,
        _______,    _______, KC_ASTG, _______, _______, _______, _______, TJIGGLE, _______, KC_LOCK, _______, _______,          _______,            KC_PGDN,
        KC_LSFT,          _______, _______, MFAC,    _______, _______, NK_TOGG, _______, _______, _______, _______,          KC_RSFT, KC_UP,
        _______, _______, _______,                            _______,                            _______, _______, KC_LEAD, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    // Gaming overlay. Capslock, Spacecadet Shift, Function, Mouse Layer, and Windows Key all disabled. CapsWord is not disabled!
    [_GAME] = LAYOUT_ansi_82(
        TD(TD_ESC_GM), _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_HOME,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_PGUP,
        KC_NO,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          KC_PGDN,
        KC_LSFT,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_RSFT, KC_UP,
        _______, KC_NO,   _______,                            _______,                            _______, MO(_FN2),   _______,   KC_LEFT, KC_DOWN, KC_RGHT
    ),
	
	// The Gamer function keys.
	// Mostly Transparent to the Gamer level
    [_FN2] = LAYOUT_ansi_82(
        TO(_BASE), _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_INS,          _______,
        _______, DM_PLY1, DM_PLY1, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_LOCK, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, NK_TOGG, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),

    // Layer used when the Leader key is active. helpful to prevent mistakes, but also for rgb highlights. No Space Cadet or mouse layer here.
    [_LEADER] = LAYOUT_ansi_82(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_HOME,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_PGUP,
        KC_NO,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          KC_PGDN,
        KC_LSFT,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_RSFT, KC_UP,
        _______, KC_NO,   _______,                            _______,                            _______, KC_NO,   _______,   KC_LEFT, KC_DOWN, KC_RGHT
    ),

    // Layer used to configure RGB settings
	// Left Side of board changes Hue, Saturation, and Brightness. Arrows change mode and speed. Function Keys are color presets.
    [_RGB] = LAYOUT_ansi_82(
       TG(_RGB), MMAG,    MRSE,    MRED,    MORN,    MYEL,    MCRT,    MGRN,    MSGN,    MCYN,    MAZR,    MBLU,    MVLT,    MFWHT,            RGB_TOG,  
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,            KC_NO,  
        KC_NO,   RGB_HUD, RGB_HUI, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,            KC_NO,  
        KC_NO,   RGB_SAI, RGB_SAD, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,            KC_NO,            KC_NO,  
        KC_NO,            RGB_VAI, RGB_VAD, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,            KC_NO,   RGB_MOD,
        KC_NO,   KC_NO,   KC_NO,                              KC_NO,                              KC_NO,   KC_NO,   KC_NO,   RGB_SPD, RGB_RMOD, RGB_SPI
    ),
	
	// Layer used to configure Auto Shift. Space Cadet and Mouse Layer disabled.
    [_ASHIFT] = LAYOUT_ansi_82(
        TG(_ASHIFT), _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_ASRP,          KC_ASTG,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_ASTG,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_ASUP,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          KC_ASDN,
        KC_LSFT,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_RSFT, KC_UP,
        _______, _______, _______,                            _______,                            _______, KC_NO,   _______,   KC_LEFT, KC_DOWN, KC_RGHT
    ),
	
	 /* _NUM (Numpad) Layout
     *  Note: A symbol preceeded by "P" is a Numpad-encoded version of the key -- any app that differentiates will recognize the char as coming from a physical numpad.
     * ,-------------------------------------------------------------------------------------------------------------.
     * | Exit || ____ | ____ | ____ | ____ || ____ | ____ | ____ | ____ || ____ | ____ | ____ | ____ || ____ || ____ |
     * |=============================================================================================================|
     * | ____ |  P1  |  P2  |  P3  |  P4  |  P5  |  P6  |  P7  |  P8  |  P9  |  P0  |  P-  |  P+  | ________ || None |
     * |------+------+------+------+------+------+------+------+------+------+------+------+------+----------++------|
     * |  ______ | None |  Up  | None | None | None | None |  P4  |  P5  |  P6  |  P+  | ____ | ____ | _____ || None |
     * |---------+------+------+------+------+------+------+------+------+------+------+------+------+-------++------|
     * |  ________  | Left | Down | Rght | None| None | None |  P1  |  P2  |  P3  |  P*  | ____ |   P-Enter  || None |
     * |------------+------+------+------+-----+------+------+------+------+------+------+------|----+========+------|
     * |  __________  | None | ____ | ____ | ____ | None | None |  P0  |  P0  |  P.  |  P/  | ______ || None || PEnt |
     * |--------------+------+------+------+------+------+------+------+------+------+------+--+=====++------++======|
     * |  ____  |  ____  |  ____  |               _____                  | ____ | None | ____ || None | None | PEnt |
     * `------------------------------------------------------------------------------------------------------------'
     */

    [_NUM] = LAYOUT_ansi_82(
        TG(_NUM), _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, KC_P1,   KC_P2,   KC_P3,   KC_P4,   KC_P5,   KC_P6,   KC_P7,   KC_P8,   KC_P9,   KC_P0,   KC_PMNS, KC_PPLS, _______,          KC_NO,
        _______, KC_NO,   KC_UP,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_P4,   KC_P5,   KC_P6,   KC_PPLS, _______, _______, _______,          KC_NO,
        _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO,   KC_NO,   KC_NO,   KC_P1,   KC_P2,   KC_P3,   KC_PAST, _______,          KC_PENT,          KC_NO,
        _______,          KC_NO,   _______, _______, _______, KC_NO,   KC_NO,   KC_P0,   KC_P0,   KC_PDOT, KC_PSLS,          _______, KC_NO,
        _______, _______, _______,                            _______,                            _______, KC_NO,   _______, KC_NO,   KC_NO,   KC_PENT
    ),
	
	/* _KID layout
	* RGB play mode where none of the buttons do anything inportant so a toddler can mess with it as a distraction durring zoom calls.
	* Press ESC twice to exit the mode.
	*/
	[_KID] = LAYOUT_ansi_82(
        TD(TD_ESC_KID), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,          KC_NO,
        KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO, KC_NO,          KC_NO,
        KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,          KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,          KC_NO,          KC_NO,
        KC_NO,          KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,          KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO,                            KC_NO,                            KC_NO, KC_NO,   KC_NO, KC_NO,   KC_NO,   KC_NO
    ),


};


#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
	// Change the encoder knob function based on highest layer.
    
	switch (get_highest_layer(layer_state)) {
	
	case _RGB: 
	if (clockwise) {
          rgb_matrix_increase_hue();
        } else {
          rgb_matrix_decrease_hue();
        }
		break;
		
	case _KID:
		if (clockwise) {
          rgb_matrix_increase_hue_noeeprom();
        } else {
          rgb_matrix_decrease_hue_noeeprom();
        }
		break;
		
	case _FN1:
	    if (clockwise) {
          tap_code16(LCTL(KC_PPLS)); // + when combined with Left Control should zoom in.
        } else {
          tap_code16(LCTL(KC_PMNS)); // - when combined with Left Control should zoom out.
        }
		break;
		
	case _BASE:
	    if (clockwise) {
          tap_code(KC_VOLU);
        } else {
          tap_code(KC_VOLD);
        }
        break;
	
	case _SPACE:
	    if (clockwise) {
          tap_code(KC_VOLU);
        } else {
          tap_code(KC_VOLD);
        }
        break;
	
	case _MOUSE:
	    if (clockwise) {
          tap_code(KC_VOLU);
        } else {
          tap_code(KC_VOLD);
        }
        break;
	
	case _GAME:
	    if (clockwise) {
          tap_code(KC_VOLU);
        } else {
          tap_code(KC_VOLD);
        }
        break;
	
	case _FN2:
	    if (clockwise) {
          tap_code(KC_VOLU);
        } else {
          tap_code(KC_VOLD);
        }
        break;
	
	case _LEADER:
	    if (clockwise) {
          tap_code(KC_VOLU);
        } else {
          tap_code(KC_VOLD);
        }
        break;
		
	case _NUM:
	    if (clockwise) {
          tap_code(KC_VOLU);
        } else {
          tap_code(KC_VOLD);
        }
        break;
		
	case _ASHIFT:
	    if (clockwise) {
          tap_code(KC_VOLU);
        } else {
          tap_code(KC_VOLD);
        }
        break;

	case MAC_BASE:
	    if (clockwise) {
          tap_code(KC_VOLU);
        } else {
          tap_code(KC_VOLD);
        }
        break;
		
    case MAC_FN:
	    if (clockwise) {
          tap_code(KC_VOLU);
        } else {
          tap_code(KC_VOLD);
        }
        break;
	
	default:
	    break;
	};
	
    return false;
}
#endif // ENCODER_ENABLE

// Include Features
#include "features/caps_word.h"
bool fet_cw_on = true;
#include "features/autocorrection.h"
bool fet_ac_on = true;
#include "features/select_word.h"

// Mouse Jiggler
// Custom Pointing Device Driver First
void           pointing_device_driver_init(void) {}
report_mouse_t pointing_device_driver_get_report(report_mouse_t mouse_report) { return mouse_report; }
uint16_t       pointing_device_driver_get_cpi(void) { return 0; }
void           pointing_device_driver_set_cpi(uint16_t cpi) {}
//Jiggle Stuff Now
bool mouse_jiggle_mode = false;
// Un-fixing a bug to make mouse data reported
bool has_mouse_report_changed(report_mouse_t new_report, report_mouse_t old_report) {
    return memcmp(&new_report, &old_report, sizeof(new_report)) || mouse_jiggle_mode;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	
  // Select Word
  if (!process_select_word(keycode, record, SELWORD)) { return false; }

  // CapsWord
  if (fet_cw_on) {
    if (!process_caps_word(keycode, record)) { return false; }
  }

  // Autocorrection
  if (fet_ac_on) {
    if (!process_autocorrection(keycode, record)) { return false; }
  }
	
    switch (keycode) {
        case KC_MISSION_CONTROL:
            if (record->event.pressed) {
                host_consumer_send(0x29F);
            } else {
                host_consumer_send(0);
            }
            return false;  // Skip all further processing of this key
        case KC_LAUNCHPAD:
            if (record->event.pressed) {
                host_consumer_send(0x2A0);
            } else {
                host_consumer_send(0);
            }
            return false;  // Skip all further processing of this key
        case KC_LOPTN:
        case KC_ROPTN:
        case KC_LCMMD:
        case KC_RCMMD:
            if (record->event.pressed) {
                register_code(mac_keycode[keycode - KC_LOPTN]);
            } else {
                unregister_code(mac_keycode[keycode - KC_LOPTN]);
            }
            return false;  // Skip all further processing of this key
        case KC_TASK:
        case KC_FLXP:
            if (record->event.pressed) {
                for (uint8_t i = 0; i < key_comb_list[keycode - KC_TASK].len; i++) {
                    register_code(key_comb_list[keycode - KC_TASK].keycode[i]);
                }
            } else {
                for (uint8_t i = 0; i < key_comb_list[keycode - KC_TASK].len; i++) {
                    unregister_code(key_comb_list[keycode - KC_TASK].keycode[i]);
                }
            }
            return false;  // Skip all further processing of this key
		case MFCW:
            if (record->event.pressed) {
                // when keycode is pressed
                if(fet_cw_on) {
	    			fet_cw_on = false;
	    		} else {
	    			fet_cw_on = true;
	    		}
            } else {
                // when keycode is released
            }
            break;

	    case MFAC:
            if (record->event.pressed) {
                // when keycode is pressed
                if(fet_ac_on) {
    				fet_ac_on = false;
	    		} else {
	    			fet_ac_on = true;
	    		}
            } else {
                // when keycode is released
            }
            break;
	
      // RGB Macros
        case MRED:
            if (record->event.pressed) {
                // when keycode is pressed
                rgb_matrix_sethsv(0, 255, 255);
            } else {
                // when keycode is released
            }
            break;

    	case MORN:
            if (record->event.pressed) {
                // when keycode is pressed
                rgb_matrix_sethsv(21, 255, 255);
            } else {
                // when keycode is released
            }
            break;
	
    	case MYEL:
            if (record->event.pressed) {
                // when keycode is pressed
                rgb_matrix_sethsv(43, 255, 255);
            } else {
                // when keycode is released
            }
            break;
	
    	case MCRT:
            if (record->event.pressed) {
                // when keycode is pressed
                rgb_matrix_sethsv(64, 255, 255);
            } else {
                // when keycode is released
            }
            break;

    	case MGRN:
            if (record->event.pressed) {
                // when keycode is pressed
                rgb_matrix_sethsv(85, 255, 255);
            } else {
                // when keycode is released
            }
            break;
	
    	case MSGN:
            if (record->event.pressed) {
                // when keycode is pressed
                rgb_matrix_sethsv(106, 255, 255);
            } else {
                // when keycode is released
            }
            break;
	
	    case MCYN:
            if (record->event.pressed) {
                // when keycode is pressed
                rgb_matrix_sethsv(127, 255, 255);
            } else {
                // when keycode is released
            }
            break;
	
    	case MAZR:
            if (record->event.pressed) {
                // when keycode is pressed
                rgb_matrix_sethsv(148, 255, 255);
            } else {
                // when keycode is released
            }
            break;
	
    	case MBLU:
            if (record->event.pressed) {
                // when keycode is pressed
                rgb_matrix_sethsv(169, 255, 255);
            } else {
                // when keycode is released
            }
            break;
	
    	case MVLT:
            if (record->event.pressed) {
                // when keycode is pressed
                rgb_matrix_sethsv(180, 255, 255);
            } else {
                // when keycode is released
            }
            break;
	
    	case MMAG:
            if (record->event.pressed) {
                // when keycode is pressed
                rgb_matrix_sethsv(201, 255, 255);
            } else {
                // when keycode is released
            }
            break;
	
    	case MRSE:
            if (record->event.pressed) {
                // when keycode is pressed
                rgb_matrix_sethsv(222, 255, 255);
            } else {
                // when keycode is released
            }
            break;
	
    	case MFWHT:
	        if (record->event.pressed) {
                // when keycode is pressed
                rgb_matrix_sethsv(255, 0, 255);
            } else {
                // when keycode is released
            }
            break;
		
	    // Mouse Jiggler
        case TJIGGLE:
            if (record->event.pressed) {
                // when keycode is pressed
    			if (mouse_jiggle_mode) {
	    			mouse_jiggle_mode = false;
		    	} else {
			    	mouse_jiggle_mode = true;
			    }
            } else {
                // when keycode is released
            }
            break;
			
        default:
            return true;   // Process all other keycodes normally
    }
	return true;
}

LEADER_EXTERNS();
// Declare a boolean variable to keep track of whether any sequence
// will have been matched.
bool did_leader_succeed;

// Matrix Scan User
void matrix_scan_user(void) {

  caps_word_task();
  LEADER_DICTIONARY() {
    // Initialize did_leader_succeed as well as leading to be false
    did_leader_succeed = leading = false;
	leader_start();

    // Replace the sequences below with your own sequences.
    SEQ_FOUR_KEYS(KC_G, KC_A, KC_M, KC_E) {
      // When I press KC_LEAD and then GAME, enter game mode
      layer_on(_GAME);
	  did_leader_succeed = true;
    }
    // Note: This is not an array, you don't need to put any commas
    // or semicolons between sequences.
    SEQ_FIVE_KEYS(KC_M, KC_O, KC_U, KC_S, KC_E) {
      // When I press KC_LEAD and then MOUSE, go to mouse layer
	  layer_on(_MOUSE);
	  did_leader_succeed = true;
    }
	SEQ_FIVE_KEYS(KC_C, KC_O, KC_L, KC_O, KC_R) {
      // When I press KC_LEAD and then COLOR
	  rgb_matrix_mode_noeeprom(RGB_MATRIX_CYCLE_LEFT_RIGHT);
	  rgb_matrix_sethsv_noeeprom(255, 255, 255);
	  did_leader_succeed = true;
    }
    SEQ_FIVE_KEYS(KC_W, KC_H, KC_I, KC_T, KC_E) {
      // When I press KC_LEAD and then WHITE
	  rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
	  rgb_matrix_sethsv(15, 40, 60);
	  did_leader_succeed = true;
    }
	
	SEQ_THREE_KEYS(KC_R, KC_G, KC_B) {
      // When I press KC_LEAD and then RGB
      layer_on(_RGB);
	  did_leader_succeed = true;
    }
	
	SEQ_FIVE_KEYS(KC_S, KC_P, KC_A, KC_C, KC_E) {
      // When I press KC_LEAD and then SPACE
      layer_invert(_SPACE);
	  did_leader_succeed = true;
    }
	
	SEQ_FIVE_KEYS(KC_S, KC_H, KC_I, KC_F, KC_T) {
      // When I press KC_LEAD and then SHIFT
      layer_on(_ASHIFT);
	  did_leader_succeed = true;
    }
	
	SEQ_THREE_KEYS(KC_N, KC_U, KC_M) {
      // When I press KC_LEAD and then NUM
      layer_on(_NUM);
	  did_leader_succeed = true;
    }
	
	SEQ_FIVE_KEYS(KC_K, KC_I, KC_D, KC_D, KC_O) {
      // When I press KC_LEAD and then KIDDO
      layer_on(_KID);
	  rgb_matrix_mode_noeeprom(RGB_MATRIX_SPLASH);
	  rgb_matrix_sethsv_noeeprom(255, 255, 255);
	  did_leader_succeed = true;
    }
	
	// Call leader_end at the end of the function, instead of at
    // the start. This way, we're sure we have set did_leader_succeed.
	leader_end();
  }
  // Other tasks...
}

void leader_start(void) {
    // Add your code to run when pressing the leader key here
    // rgb_matrix_set_color(LED_LEAD, RGB_PURPLE2); // light up Leader when active? Didn't work
	layer_on(_LEADER);
}
void leader_end(void) {
    // Add your code to run when a leader key sequence ends here
    layer_off(_LEADER);
	if (did_leader_succeed) {
    // It Worked
    } else {
    // It didn't work
    }
}

bool caps_word_press_user(uint16_t keycode) {
  switch (keycode) {
    // Keycodes that continue Caps Word, with shift applied.
    case KC_A ... KC_Z:
	case KC_MINS:  // Make Caps Word shift the '-' key to write '_'
      add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to the next key.
      return true;

    // Keycodes that continue Caps Word, without shifting.
    case KC_1 ... KC_0:
    case KC_BSPC:
    case KC_UNDS:
      return true;

    default:
      return false;  // Deactivate Caps Word.
  }
}

// CapsWord Engaged Indicator
bool CapsWordEngaged = false;
void caps_word_set_user(bool active) {
  if (active) {
    // Do something when Caps Word activates.
	CapsWordEngaged = true;
	// RGB is turned on based on this farther down.
  } else {
    // Do something when Caps Word deactivates.
	CapsWordEngaged = false;
  }
}

// Dynamic Macro Recording Indicator
bool isRecording = false;
bool isRecordingLedOn = false;
static uint16_t recording_timer;

// Matrix scan function constantly running => Similar to "do () while (keyboard is powered on)"
void rgb_matrix_indicators_user(void) 
{	
    if (isRecording)
    {
        // timer_elapsed() is a built-in function in qmk => it calculates in ms the time elapsed with timer_read()
        if (timer_elapsed(recording_timer) > 500) 
        {
            isRecordingLedOn = !isRecordingLedOn;
            recording_timer = timer_read();
        }
        if (isRecordingLedOn)
        {
			// This sets the FN key to blue and the ESC key to red.
            rgb_matrix_set_color(LED_ESC, RGB_RED);
			rgb_matrix_set_color(LED_FN, RGB_BLUE);
        }
    }
}

// Listener function => Triggered when you start recording a macro.
void dynamic_macro_record_start_user(void) 
{
    isRecording = true;
    isRecordingLedOn = true;
    // timer_read() is a built-in function in qmk. => It read the current time
    recording_timer = timer_read();
}

// Listener function => Triggered when the macro recording is stopped.
void dynamic_macro_record_end_user(int8_t direction) 
{
    isRecording = false;
    isRecordingLedOn = false;
}

#ifdef RGB_MATRIX_ENABLE
// Inidcator Lights
void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {

    // CapsLock RGB
    if (IS_HOST_LED_ON(USB_LED_CAPS_LOCK)) {
        rgb_matrix_set_color(LED_CAPS, RGB_BLUE);
    }
	
	// CapsWord RGB Indicators
	if (CapsWordEngaged) {
		rgb_matrix_set_color(LED_LSFT, RGB_BLUE);
	    rgb_matrix_set_color(LED_RSFT, RGB_BLUE);
	}
 
    // Function Layer RGB
    switch (get_highest_layer(layer_state)) { // special handling per layer
    case _FN1: 
		rgb_matrix_set_color(LED_FN, RGB_PURPLE); // Light up FN Purple
		rgb_matrix_set_color(LED_LEAD, RGB_YELLOW); // Leader Key
		rgb_matrix_set_color(LED_L, RGB_YELLOW); // Key Lock
		rgb_matrix_set_color(LED_F1, RGB_YELLOW); // F1 record dynamic Macro 1
		rgb_matrix_set_color(LED_F2, RGB_YELLOW); // F2 record dynamic Macro 2
		rgb_matrix_set_color(LED_F4, RGB_CHARTREUSE); // F4 Task Manager
		// rgb_matrix_set_color(LED_F5, RGB_CHARTREUSE); // F5 
		// rgb_matrix_set_color(LED_F8, RGB_CHARTREUSE); // F8
		// rgb_matrix_set_color(LED_F9, RGB_CHARTREUSE); // F9
		rgb_matrix_set_color(LED_F10, RGB_CHARTREUSE); // F10 Media Previous
		rgb_matrix_set_color(LED_F11, RGB_SPRINGGREEN); // F11 Media Play/Pause
		rgb_matrix_set_color(LED_F12, RGB_CHARTREUSE); // F12 Media Next
		rgb_matrix_set_color(LED_HOME, RGB_GREEN); // Home
		rgb_matrix_set_color(LED_PGUP, RGB_GREEN); // Page Up
		rgb_matrix_set_color(LED_PGDN, RGB_GREEN); // Page Down
		rgb_matrix_set_color(LED_1, RGB_GREEN); // Play Macro Recording 1
		rgb_matrix_set_color(LED_2, RGB_GREEN); // Play Macro Recording 2
		rgb_matrix_set_color(LED_BSLS, RGB_RED); // Reset Key
		rgb_matrix_set_color(LED_BSPC, RGB_RED); // Clear EEPROM
		rgb_matrix_set_color(LED_DEL, RGB_GREEN); // Insert
		// If macro is recording, let blink through otherwise make dark red
		if(isRecording) {
			// Do nothing
		} else {
		    rgb_matrix_set_color(LED_ESC, RGB_DKRED); // Stop Macro Recording
		}
		if(layer_state_is(_SPACE)) {
		    rgb_matrix_set_color(LED_9, RGB_BLUE); // Space Cadet
            rgb_matrix_set_color(LED_0, RGB_BLUE); // Space Cadet
		} else {
			rgb_matrix_set_color(LED_9, RGB_ORANGE2); // Space Cadet
            rgb_matrix_set_color(LED_0, RGB_ORANGE2); // Space Cadet
		}
        if(keymap_config.nkro) {
		    rgb_matrix_set_color(LED_N, RGB_BLUE); // NKey Rollover
		} else {
			rgb_matrix_set_color(LED_N, RGB_ORANGE2);
		}
		// CapsWord
		if(fet_cw_on) {
			rgb_matrix_set_color(LED_W, RGB_BLUE);
		} else {
			rgb_matrix_set_color(LED_W, RGB_ORANGE2);
		}
		// Autocorrection
        if(fet_ac_on) {
			rgb_matrix_set_color(LED_C, RGB_BLUE);
		} else {
			rgb_matrix_set_color(LED_C, RGB_ORANGE2);
		}
        // Mouse Jiggler
        if(mouse_jiggle_mode) {
            rgb_matrix_set_color(LED_J, RGB_BLUE);
		} else {
			rgb_matrix_set_color(LED_J, RGB_ORANGE2);
		}
		// Autoshift
		if(get_autoshift_state()) {
			rgb_matrix_set_color(LED_S, RGB_BLUE);
		} else {
		    rgb_matrix_set_color(LED_S, RGB_ORANGE2);
		}
		break;
	
    // Game Mode Layer RGB
    case _GAME: 
        rgb_matrix_set_color(LED_LWIN, RGB_DKRED); //light up Winkey red when disabled
		rgb_matrix_set_color(LED_CAPS, RGB_DKRED); //light up Capslock red when disabled
		rgb_matrix_set_color(LED_ESC, RGB_PURPLE); //light up Esc Purple
        rgb_matrix_set_color(LED_W, RGB_GREEN); //light up gaming keys with WSAD higlighted
        rgb_matrix_set_color(LED_S, RGB_GREEN);
        rgb_matrix_set_color(LED_A, RGB_GREEN);
        rgb_matrix_set_color(LED_D, RGB_GREEN);
        rgb_matrix_set_color(LED_Q, RGB_WHITE);
        rgb_matrix_set_color(LED_E, RGB_ORANGE2);
        rgb_matrix_set_color(LED_R, RGB_WHITE);
        rgb_matrix_set_color(LED_TAB, RGB_WHITE);
        rgb_matrix_set_color(LED_F, RGB_WHITE);
        rgb_matrix_set_color(LED_Z, RGB_WHITE);
        rgb_matrix_set_color(LED_X, RGB_WHITE);
        rgb_matrix_set_color(LED_C, RGB_WHITE);
        rgb_matrix_set_color(LED_V, RGB_WHITE);
        rgb_matrix_set_color(LED_SPC, RGB_GREEN);
        rgb_matrix_set_color(LED_LCTL, RGB_WHITE);
        rgb_matrix_set_color(LED_LSFT, RGB_WHITE);
		rgb_matrix_set_color(LED_1, RGB_ORANGE2);
		rgb_matrix_set_color(LED_2, RGB_ORANGE2);
		rgb_matrix_set_color(LED_3, RGB_ORANGE2);
		rgb_matrix_set_color(LED_4, RGB_ORANGE2);
		rgb_matrix_set_color(LED_GRV, RGB_WHITE);
		break;

    // Gamer Function Layer RGB
    case _FN2: 
        rgb_matrix_set_color(LED_ESC, RGB_PURPLE); // Light up Esc Purple
	    rgb_matrix_set_color(LED_FN, RGB_PURPLE); // Light up FN Purple
		rgb_matrix_set_color(LED_L, RGB_YELLOW); // Key Lock
		rgb_matrix_set_color(LED_DEL, RGB_GREEN); // Insert
		rgb_matrix_set_color(LED_1, RGB_GREEN); // Play Macro Recording 1
		rgb_matrix_set_color(LED_2, RGB_GREEN); // Play Macro Recording 1
        if(keymap_config.nkro) {
		    rgb_matrix_set_color(LED_N, RGB_BLUE); // NKey Rollover
		} else {
			rgb_matrix_set_color(LED_N, RGB_ORANGE2);
		}
		break;
	
	// Leader key active RGB
    case _LEADER:
        rgb_matrix_set_color(LED_LEAD, RGB_BLUE);
		break;
	
	// Mouse Mode RGB
    case _MOUSE:
        rgb_matrix_set_color(LED_LEFT, RGB_CHARTREUSE);
        rgb_matrix_set_color(LED_RIGHT, RGB_CHARTREUSE);
		rgb_matrix_set_color(LED_UP, RGB_CHARTREUSE);
	    rgb_matrix_set_color(LED_DOWN, RGB_CHARTREUSE);
		rgb_matrix_set_color(LED_LEAD, RGB_GREEN);
		rgb_matrix_set_color(LED_ESC, RGB_PURPLE); //light up Esc Purple
		rgb_matrix_set_color(LED_PGDN, RGB_SPRINGGREEN);
		rgb_matrix_set_color(LED_PGUP, RGB_DKRED); 
		rgb_matrix_set_color(LED_HOME, RGB_DKRED);
		break;
	
	// RGB Control Board
	case _RGB:
        rgb_matrix_set_color(LED_F1, RGB_MAGENTA);
        rgb_matrix_set_color(LED_F2, RGB_PINK);
		rgb_matrix_set_color(LED_F3, RGB_RED);
	    rgb_matrix_set_color(LED_F4, RGB_ORANGE);
		rgb_matrix_set_color(LED_F5, RGB_YELLOW);
		rgb_matrix_set_color(LED_F6, RGB_CHARTREUSE);
		rgb_matrix_set_color(LED_F7, RGB_GREEN);
		rgb_matrix_set_color(LED_F8, RGB_SPRINGGREEN);
		rgb_matrix_set_color(LED_F9, RGB_CYAN);
		rgb_matrix_set_color(LED_F10, RGB_AZURE);
		rgb_matrix_set_color(LED_F11, RGB_BLUE);
		rgb_matrix_set_color(LED_F12, RGB_PURPLE);
		rgb_matrix_set_color(LED_ESC, RGB_PURPLE);
		rgb_matrix_set_color(LED_GRV, RGB_WHITE);
		rgb_matrix_set_color(LED_1, RGB_WHITE);
		rgb_matrix_set_color(LED_2, RGB_WHITE);
		rgb_matrix_set_color(LED_3, RGB_WHITE);
		rgb_matrix_set_color(LED_4, RGB_WHITE);
		rgb_matrix_set_color(LED_R, RGB_WHITE);
		rgb_matrix_set_color(LED_F, RGB_WHITE);
		rgb_matrix_set_color(LED_V, RGB_WHITE);
		rgb_matrix_set_color(LED_E, RGB_BLACK);
		rgb_matrix_set_color(LED_D, RGB_BLACK);
		rgb_matrix_set_color(LED_C, RGB_BLACK);
		rgb_matrix_set_color(LED_Q, RGB_ORANGE);
		rgb_matrix_set_color(LED_W, RGB_PURPLE);
		rgb_matrix_set_color(LED_A, RGB_BLUE);
		rgb_matrix_set_color(LED_S, RGB_AZURE);
		rgb_matrix_set_color(LED_Z, RGB_WHITE);
		rgb_matrix_set_color(LED_X, 100, 100, 100);
		rgb_matrix_set_color(LED_TAB, RGB_BLACK);
		rgb_matrix_set_color(LED_CAPS, RGB_BLACK);
		rgb_matrix_set_color(LED_LSFT, RGB_BLACK);
		rgb_matrix_set_color(LED_LCTL, RGB_BLACK);
		rgb_matrix_set_color(LED_LWIN, RGB_BLACK);
		rgb_matrix_set_color(LED_LALT, RGB_BLACK);
		rgb_matrix_set_color(LED_UP, RGB_BLUE);
		rgb_matrix_set_color(LED_DOWN, RGB_BLUE);
		rgb_matrix_set_color(LED_LEFT, RGB_RED);
		rgb_matrix_set_color(LED_RIGHT, RGB_GREEN);
		rgb_matrix_set_color(LED_DEL, RGB_WHITE);
		// rgb_matrix_set_color(LED_HOME, RGB_WHITE);
		// rgb_matrix_set_color(LED_PGUP, RGB_WHITE);
		// rgb_matrix_set_color(LED_PGDN, RGB_WHITE);
		break;

	
	// Auto Shift Configuration Layer RGB
    case _ASHIFT:
        rgb_matrix_set_color(LED_ESC, RGB_PURPLE); // ESC key is Purple
		rgb_matrix_set_color(LED_FN, RGB_DKRED); // Function Key Disabled
	    rgb_matrix_set_color(LED_PGUP, RGB_GREEN); // More time
	    rgb_matrix_set_color(LED_PGDN, RGB_RED); // Less time
	    rgb_matrix_set_color(LED_DEL, RGB_YELLOW); // Print Time
		// Autoshift On/Off
		if(get_autoshift_state()) {
			rgb_matrix_set_color(LED_HOME, RGB_BLUE);
		} else {
		    rgb_matrix_set_color(LED_HOME, RGB_ORANGE2);
		}
		break;
		
	// Numpad overlay RGB
    case _NUM:
        rgb_matrix_set_color(LED_ESC, RGB_PURPLE); // ESC key is Purple
		rgb_matrix_set_color(LED_FN, RGB_DKRED); // Function key disabled
        rgb_matrix_set_color(LED_1, RGB_SPRINGGREEN);
        rgb_matrix_set_color(LED_2, RGB_SPRINGGREEN);
        rgb_matrix_set_color(LED_3, RGB_SPRINGGREEN);
        rgb_matrix_set_color(LED_4, RGB_SPRINGGREEN);
        rgb_matrix_set_color(LED_5, RGB_SPRINGGREEN);
        rgb_matrix_set_color(LED_6, RGB_SPRINGGREEN);
        rgb_matrix_set_color(LED_7, RGB_GREEN);
        rgb_matrix_set_color(LED_8, RGB_GREEN);
        rgb_matrix_set_color(LED_9, RGB_GREEN);
        rgb_matrix_set_color(LED_0, RGB_SPRINGGREEN);
        rgb_matrix_set_color(LED_MINS, RGB_CHARTREUSE);
        rgb_matrix_set_color(LED_EQL, RGB_CHARTREUSE);
        rgb_matrix_set_color(LED_U, RGB_GREEN);
        rgb_matrix_set_color(LED_I, RGB_GREEN);
        rgb_matrix_set_color(LED_O, RGB_GREEN);
        rgb_matrix_set_color(LED_P, RGB_CHARTREUSE);
        rgb_matrix_set_color(LED_J, RGB_GREEN);
        rgb_matrix_set_color(LED_K, RGB_GREEN);
        rgb_matrix_set_color(LED_L, RGB_GREEN);
        rgb_matrix_set_color(LED_SCLN, RGB_CHARTREUSE);
        rgb_matrix_set_color(LED_ENT, RGB_CHARTREUSE);
        rgb_matrix_set_color(LED_M, RGB_SPRINGGREEN);
        rgb_matrix_set_color(LED_COMM, RGB_SPRINGGREEN);
        rgb_matrix_set_color(LED_DOT, RGB_CHARTREUSE);
        rgb_matrix_set_color(LED_SLSH, RGB_CHARTREUSE);
        rgb_matrix_set_color(LED_RIGHT, RGB_CHARTREUSE);
		rgb_matrix_set_color(LED_UP, RGB_DKRED);
		rgb_matrix_set_color(LED_DOWN, RGB_DKRED);
		rgb_matrix_set_color(LED_LEFT, RGB_DKRED);
		rgb_matrix_set_color(LED_HOME, RGB_DKRED);
		rgb_matrix_set_color(LED_PGUP, RGB_DKRED);
		rgb_matrix_set_color(LED_PGDN, RGB_DKRED);
		rgb_matrix_set_color(LED_W, RGB_GREEN); //light up WASD
        rgb_matrix_set_color(LED_S, RGB_GREEN);
        rgb_matrix_set_color(LED_A, RGB_GREEN);
        rgb_matrix_set_color(LED_D, RGB_GREEN);
		rgb_matrix_set_color(LED_Q, RGB_DKRED);
		rgb_matrix_set_color(LED_E, RGB_DKRED);
		rgb_matrix_set_color(LED_R, RGB_DKRED);
		rgb_matrix_set_color(LED_T, RGB_DKRED);
		rgb_matrix_set_color(LED_Y, RGB_DKRED);
		rgb_matrix_set_color(LED_F, RGB_DKRED);
		rgb_matrix_set_color(LED_G, RGB_DKRED);
		rgb_matrix_set_color(LED_H, RGB_DKRED);
		rgb_matrix_set_color(LED_Z, RGB_DKRED);
		rgb_matrix_set_color(LED_B, RGB_DKRED);
		rgb_matrix_set_color(LED_N, RGB_DKRED);
        break;
		
	// KID active RGB
    case _KID:
        rgb_matrix_set_color(LED_ESC, RGB_PURPLE);
		break;
		
	default:
        break;
    }
}
#endif

// #ifdef SPACECADET_ENABLE_AT_STARTUP
// Start up code to execute?
// void keyboard_post_init_user(void) {
//     // Turn on the Space Cadet layer at boot up.
// 	layer_on(_SPACE);
// }
// #endif