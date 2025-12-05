// Copyright 2025 MockLogic (@mocklogic)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "mocklogic.h"

// ============================================================================
// Tap Dance Definitions
// Tap dance actions array must be in keymap file not userspace file
// ============================================================================

void td_esc_mouse_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        layer_off(_MOUSE);
    }
}

void td_esc_kiddo_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        layer_off(_KIDDO);
        // Reset RGB to active preset
        rgb_preset_apply(userspace_config.active_rgb_preset);
    }
}

void td_esc_rgb_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        layer_off(_RGB_CFG);
    }
}


tap_dance_action_t tap_dance_actions[] = {
    [TD_ESC_MOUSE] = ACTION_TAP_DANCE_FN(td_esc_mouse_finished),
    [TD_ESC_KIDDO] = ACTION_TAP_DANCE_FN(td_esc_kiddo_finished),
    [TD_ESC_RGB]   = ACTION_TAP_DANCE_FN(td_esc_rgb_finished)
};

// ============================================================================
// Keymap Layers
// Layers 0-3 are reserved for Keychron physical OS switch compatibility
// ============================================================================

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Mac Base Layer (Layer 0 - physical OS switch position)
    [_MAC_BASE] = LAYOUT_tkl_f13_ansi(
        KC_ESC,   KC_BRID, KC_BRIU, KC_MCTL, KC_LPAD, RM_VALD, RM_VALU, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU,    KC_MUTE,  KC_NO,    KC_NO,    KC_NO,
        KC_GRV,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,     KC_BSPC,  KC_MYCM,  KC_HOME,  KC_PGUP,
        KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,    KC_BSLS,  C(KC_V),  KC_END,   KC_PGDN,
        KC_CAPS,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,             KC_ENT,
        KC_LSFT,           KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,             KC_RSFT,            KC_UP,
        KC_LCTL,  KC_LOPTN,KC_LCMMD,                           KC_SPC,                              KC_RCMMD,FN_MAC,  SELWORD,    KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RIGHT),

    // Mac Function Layer (Layer 1 - unused for now - Mac specific functions can be added here)
    [_MAC_FN] = LAYOUT_tkl_f13_ansi(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,    _______,  _______,  _______,  _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,    _______,  _______,  _______,  _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,    _______,  _______,  _______,  _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,             _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,             _______,            _______,
        _______, _______, _______,                            _______,                             _______, _______, _______,    _______,  _______,  _______,  _______),

    // Windows Base Layer (Layer 2 - physical OS switch position)
    [_WIN_BASE] = LAYOUT_tkl_f13_ansi(
        KC_ESC,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,     KC_MUTE,  KC_PSCR,  KC_NO,    G(KC_D),
        KC_GRV,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,     KC_BSPC,  KC_MYCM,  KC_HOME,  KC_PGUP,
        KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,    KC_BSLS,  G(KC_V),  KC_END,   KC_PGDN,
        KC_CAPS,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,             KC_ENT,
        KC_LSFT,           KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,             KC_RSFT,            KC_UP,
        KC_LCTL,  KC_LWIN, KC_LALT,                            KC_SPC,                              KC_RALT, FN_WIN,  SELWORD,    KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RIGHT),

    // Windows Function Layer (Layer 3 - Windows specific functions)
    [_WIN_FN] = LAYOUT_tkl_f13_ansi(
        _______, _______, _______, _______, TASK_MGR, _______, _______, _______, _______, _______, _______, _______, _______,    _______,  _______,  _______,  _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,    _______,  _______,  _______,  _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,    _______,  _______,  _______,  _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,             _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,             _______,            _______,
        _______, _______, _______,                            _______,                             _______, _______, _______,    _______,  _______,  _______,  _______),

    // Features Layer (momentary, used with layers 1 or 3, this layer has non-OS specific features and is trigger detecting Function/Features layers active)
    [_FEATURES] = LAYOUT_tkl_f13_ansi(
        _______, _______, _______, _______, _______,RGB_PRESET_1,RGB_PRESET_2,RGB_PRESET_3,RGB_PRESET_4,_______,_______, _______, _______, _______,  _______,  _______,  _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,    QK_BOOT,  _______,  _______,  _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,    _______,  _______,  _______,  _______,
        _______, TOGGLE_AUTOCORRECT,_______,_______,_______, _______, _______, TOGGLE_JIGGLER,_______,_______,_______, _______,             _______,
        _______,          _______, _______, _______, _______, _______, NK_TOGG, _______, _______, _______, _______,             _______,            _______,
        _______, _______, _______,                            _______,                             _______, _______, QK_LEAD,    _______,  _______,  _______,  _______),

    // Gaming Layer (disables Windows key and actiavates gaming RGB profile)
    [_GAMING] = LAYOUT_tkl_f13_ansi(
        KC_ESC,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,    _______,  _______,  _______,  _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,    _______,  _______,  _______,  _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,    _______,  _______,  _______,  _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,             _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,             _______,            _______,
        _______, KC_NO,   _______,                            _______,                             _______, _______, _______,    _______,  _______,  _______,  _______),

    // Mouse Layer (provides mouse control keys)
    [_MOUSE] = LAYOUT_tkl_f13_ansi(
        TD(TD_ESC_MOUSE),_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,    _______,  _______,  _______,  _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,    _______,  KC_NO,    KC_NO,    KC_NO,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,    _______,  MS_BTN1,  KC_NO,    MS_BTN2,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,             _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,             _______,            MS_UP,
        _______, _______, _______,                            _______,                             _______, _______, _______,    _______,  MS_LEFT,  MS_DOWN,  MS_RGHT),

    // Kiddo Layer (disables most key inputs and adds fun RGB effects)
    [_KIDDO] = LAYOUT_tkl_f13_ansi(
        TD(TD_ESC_KIDDO),KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,      KC_NO,    KC_NO,    KC_NO,    KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,      KC_NO,    KC_NO,    KC_NO,    KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,      KC_NO,    KC_NO,    KC_NO,    KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,               KC_NO,
        KC_NO,            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,               KC_NO,              KC_NO,
        KC_NO,   KC_NO,   KC_NO,                              KC_NO,                               KC_NO,   KC_NO,   KC_NO,      KC_NO,    KC_NO,    KC_NO,    KC_NO),

    // RGB Configuration Layer
    [_RGB_CFG] = LAYOUT_tkl_f13_ansi(
        TD(TD_ESC_RGB),_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,    _______,  _______,  _______,  _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,    _______,  _______,  _______,  _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,    _______,  _______,  _______,  _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,             _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,             _______,            _______,
        _______, _______, _______,                            _______,                             _______, _______, _______,    _______,  _______,  _______,  _______),

    // Leader Key Layer (Used while leader key is active)
    [_LEADER] = LAYOUT_tkl_f13_ansi(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,    _______,  _______,  _______,  _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,    _______,  _______,  _______,  _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,    _______,  _______,  _______,  _______,
        KC_NO,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,             _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,             _______,            _______,
        _______, KC_NO,   _______,                            _______,                             _______, KC_NO,   _______,    _______,  _______,  _______,  _______)
};

// ============================================================================
// Encoder Configuration
// ============================================================================

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_MAC_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_MAC_FN]   = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_WIN_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_WIN_FN]   = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_FEATURES] = {ENCODER_CCW_CW(C(KC_PMNS), C(KC_PPLS))},  // Zoom in/out
    [_GAMING]   = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_MOUSE]    = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_KIDDO]    = {ENCODER_CCW_CW(RM_HUED, RM_HUEU)},  // Change hue for fun
    [_RGB_CFG]  = {ENCODER_CCW_CW(RM_HUED, RM_HUEU)},  // Hue control
    [_LEADER]   = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)}
};
#endif

// Note: All RGB indicator logic is now centralized in userspace (users/mocklogic/mocklogic.c)
// using keycode-based LED control for portability across different keyboards.
