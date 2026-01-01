// Copyright 2025 MockLogic (@mocklogic)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "mocklogic.h"
#include "features/rgb_presets.h"

// ============================================================================
// Tap Dance Handlers
// ============================================================================

void td_esc_mouse_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        layer_off(_MOUSE);
    }
}

void td_esc_kiddo_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        layer_off(_KIDDO);
    }
}

void td_esc_rgb_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        rgb_config_layer_exit();
        layer_off(_RGB_CFG);
        // Preset 4 (F8) remains active with saved settings
        userspace_config.active_rgb_preset = 3;
        userspace_config_save();
    }
}

void td_esc_gaming_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        layer_off(_GAMING);
    }
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_ESC_MOUSE]  = ACTION_TAP_DANCE_FN(td_esc_mouse_finished),
    [TD_ESC_KIDDO]  = ACTION_TAP_DANCE_FN(td_esc_kiddo_finished),
    [TD_ESC_RGB]    = ACTION_TAP_DANCE_FN(td_esc_rgb_finished),
    [TD_ESC_GAMING] = ACTION_TAP_DANCE_FN(td_esc_gaming_finished)
};

// ============================================================================
// Keymap Layers
// GMMK Pro defaults to Windows mode (no physical OS switch)
// ============================================================================

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Mac Base Layer (Layer 0 - not used on GMMK Pro, but required for layer structure)
    [_MAC_BASE] = LAYOUT(
        KC_ESC,  KC_BRID, KC_BRIU, KC_MCTL, KC_LPAD, RM_VALD, RM_VALU, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, KC_DEL,           KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_HOME,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGUP,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_PGDN,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_LALT, KC_LCMMD,                           KC_SPC,                             KC_RCMMD, FN_MAC,  KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    // Mac Function Layer (Layer 1)
    [_MAC_FN] = LAYOUT(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),

    // Windows Base Layer (Layer 2 - DEFAULT on GMMK Pro)
    [_WIN_BASE] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,           KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_HOME,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGUP,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_PGDN,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, FN_WIN,  KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    // Windows Function Layer (Layer 3)
    [_WIN_FN] = LAYOUT(
        _______, _______, _______, _______, TASK_MGR,_______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, G(KC_D),
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),

    // Features Layer (Layer 4)
    [_FEATURES] = LAYOUT(
        _______, _______, _______, _______, _______, RGB_PRESET_1,RGB_PRESET_2,RGB_PRESET_3,RGB_PRESET_4,_______,_______,_______,_______,_______,  _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, EEPROM_RESET,_______, _______, QK_BOOT,          _______,
        _______, _______,_______,_______,_______, _______, _______, _______,_______,_______,_______, _______, _______, _______,          _______,
        _______, TOGGLE_AUTOCORRECT, _______, _______, _______, _______, _______, TOGGLE_JIGGLER,_______, _______, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, NK_TOGG, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, QK_LEAD, _______, _______, _______
    ),

    // Gaming Layer (disables Windows key and activates gaming RGB profile)
    [_GAMING] = LAYOUT(
        TD(TD_ESC_GAMING),_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,    _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, KC_W,    KC_E,    KC_R,    _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, KC_A,    KC_S,    KC_D,    _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, KC_NO,   _______,                            _______,                            _______, _______, KC_NO,   _______, _______, _______
    ),

    // Mouse Layer (allows normal typing plus mouse control via arrows)
    [_MOUSE] = LAYOUT(
        TD(TD_ESC_MOUSE),_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,    _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, MS_UP, MS_BTN2,
        _______, _______, _______,                            _______,                            _______, _______, MS_BTN1, MS_LEFT, MS_DOWN, MS_RGHT
    ),

    // Kiddo Layer (whack-a-mole game)
    [_KIDDO] = LAYOUT(
        TD(TD_ESC_KIDDO),KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,            KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,            KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,            KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,            KC_NO,            KC_NO,
        KC_NO,            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,            KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_NO,                              KC_NO,                              KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO
    ),

    // RGB Configuration Layer
    [_RGB_CFG] = LAYOUT(
        TD(TD_ESC_RGB),RGB_EFF_SOLID,RGB_EFF_STARLIGHT,RGB_EFF_RAINDROPS,RGB_EFF_DIGRAIN,KC_NO,   KC_NO,   KC_NO,   RGB_CFG_RESET,RGB_EFF_SPIRAL,RGB_EFF_SPLASH,RGB_EFF_RIVER,RGB_EFF_HEATMAP,KC_NO,            KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   RGB_SAT_DOWN,RGB_SAT_UP,KC_NO,            KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,            KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,            KC_NO,            KC_NO,
        KC_NO,            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,            KC_NO,   RGB_BRIGHT_UP,KC_NO,
        KC_NO,   KC_NO,   KC_NO,                              KC_NO,                              KC_NO,   KC_NO,   KC_NO,   RGB_SPEED_DOWN,RGB_BRIGHT_DOWN,RGB_SPEED_UP
    ),

    // Leader Layer (visual feedback when leader key is active)
    [_LEADER] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        KC_NO,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, KC_NO,   _______,                            _______,                            _______, _______, _______, _______, _______, _______
    )
};

// ============================================================================
// Encoder Map
// ============================================================================

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_MAC_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_MAC_FN]   = {ENCODER_CCW_CW(LCMD(KC_PMNS), LCMD(KC_PPLS))},  // Zoom in/out
    [_WIN_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_WIN_FN]   = {ENCODER_CCW_CW(C(KC_PMNS), C(KC_PPLS))},  // Zoom in/out
    [_FEATURES] = {ENCODER_CCW_CW(_______, _______)},
    [_GAMING]   = {ENCODER_CCW_CW(_______, _______)},
    [_MOUSE]    = {ENCODER_CCW_CW(_______, _______)},
    [_KIDDO]    = {ENCODER_CCW_CW(KC_NO, KC_NO)},  // Disabled
    [_RGB_CFG]  = {ENCODER_CCW_CW(RM_HUED, RM_HUEU)},  // Hue control
    [_LEADER]   = {ENCODER_CCW_CW(_______, _______)}
};
#endif

// ============================================================================
// GMMK Pro Specific: OS Detection (no physical OS switch)
// ============================================================================

void keyboard_post_init_kb(void) {
    // Call the userspace init (which handles RGB presets)
    keyboard_post_init_user();

    // GMMK Pro doesn't have a physical OS switch, so we start in Windows mode
    // OS detection will switch to Mac mode if macOS is detected
    set_single_persistent_default_layer(_WIN_BASE);
}

// OS Detection callback - called when OS is detected
bool process_detected_host_os_kb(os_variant_t detected_os) {
    switch (detected_os) {
        case OS_MACOS:
        case OS_IOS:
            // Switch to Mac base layer
            set_single_persistent_default_layer(_MAC_BASE);
            break;
        case OS_WINDOWS:
        case OS_LINUX:
        case OS_UNSURE:
        default:
            // Default to Windows base layer
            set_single_persistent_default_layer(_WIN_BASE);
            break;
    }
    // Call the userspace handler if it exists
    return process_detected_host_os_user(detected_os);
}

// Note: All RGB indicator logic is now centralized in userspace (users/mocklogic/mocklogic.c)
// using keycode-based LED control for portability across different keyboards.
