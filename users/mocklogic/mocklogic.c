// Copyright 2025 MockLogic (@mocklogic)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "mocklogic.h"
#include "features/select_word.h"
#include "features/rgb_presets.h"
#include "eeconfig.h"
#include <string.h>

// Global userspace configuration
userspace_config_t userspace_config;

// ============================================================================
// EEPROM Configuration Management
// ============================================================================

void eeconfig_init_user_datablock(void) {
    // Initialize default values
    userspace_config.raw = 0;
    userspace_config.autocorrect_enabled = true;   // Autocorrect ON by default
    userspace_config.mouse_jiggler_enabled = true; // Jiggler ON by default
    userspace_config.active_rgb_preset = 1;        // Preset 2 (dim white) by default
    userspace_config_save();
}

void userspace_config_save(void) {
    eeconfig_update_user(userspace_config.raw);
}

void userspace_config_load(void) {
    userspace_config.raw = eeconfig_read_user();

    // Validate preset value
    if (userspace_config.active_rgb_preset > 3) {
        userspace_config.active_rgb_preset = 1;
        userspace_config_save();
    }
}

// QMK hook: called after keyboard init
void keyboard_post_init_user(void) {
    userspace_config_load();
    rgb_preset_init();
    rgb_preset_apply(userspace_config.active_rgb_preset);
}

// Optional helper (declared in mocklogic.h) if you want a separate hook
void keyboard_post_init_user_rgb(void) {
    keyboard_post_init_user();
}


// -----------------------------------------------------------------------------
// Mouse Jiggler Implementation (custom pointing device driver stubs)
// -----------------------------------------------------------------------------

// Driver init must return bool (true = initialized)
bool pointing_device_driver_init(void) {
    return true;
}

report_mouse_t pointing_device_driver_get_report(report_mouse_t mouse_report) {
    // Pass-through (you could inject movement here when jiggler is enabled)
    return mouse_report;
}

uint16_t pointing_device_driver_get_cpi(void) {
    return 0;
}

void pointing_device_driver_set_cpi(uint16_t cpi) {
    (void)cpi;
}

// Override to force mouse reports when jiggler is active
bool has_mouse_report_changed(report_mouse_t *new_report, report_mouse_t *old_report) {
    if (userspace_config.mouse_jiggler_enabled) {
        // Force a report so the host sees motion and doesn't go idle
        return true;
    }
    return memcmp(new_report, old_report, sizeof(report_mouse_t)) != 0;
}

bool get_mouse_jiggler_enabled(void) {
    return userspace_config.mouse_jiggler_enabled;
}

void set_mouse_jiggler_enabled(bool enabled) {
    userspace_config.mouse_jiggler_enabled = enabled;
    userspace_config_save();
}



// -----------------------------------------------------------------------------
// Autocorrect Management
// -----------------------------------------------------------------------------

bool get_autocorrect_enabled(void) {
    return userspace_config.autocorrect_enabled;
}

void set_autocorrect_enabled(bool enabled) {
    userspace_config.autocorrect_enabled = enabled;
    if (enabled) {
        autocorrect_enable();   // current API: no argument
    } else {
        autocorrect_disable();
    }
    userspace_config_save();
}

// User hook signature for autocorrect on current QMK:
//   bool process_autocorrect_user(uint16_t *keycode, keyrecord_t *record,
//                                 uint8_t *typo_buffer_size, uint8_t *mods);
bool process_autocorrect_user(uint16_t *keycode, keyrecord_t *record,
                              uint8_t *typo_buffer_size, uint8_t *mods) {
    (void)keycode;
    (void)typo_buffer_size;
    (void)mods;

    // Skip autocorrect if disabled or in Gaming layer
    if (!userspace_config.autocorrect_enabled || layer_state_is(_GAMING)) {
        return false;
    }
    return true;
}

// -----------------------------------------------------------------------------
// Leader Key Sequences
// -----------------------------------------------------------------------------

void leader_start_user(void) {
    // Turn on leader layer for visual feedback
    layer_on(_LEADER);
}

void leader_end_user(void) {
    // Turn off leader layer when done
    layer_off(_LEADER);

    // GAME  — Toggle gaming layer
    if (leader_sequence_four_keys(KC_G, KC_A, KC_M, KC_E)) {
        layer_invert(_GAMING);
    }
    // MOUSE — Activate mouse layer
    else if (leader_sequence_five_keys(KC_M, KC_O, KC_U, KC_S, KC_E)) {
        layer_on(_MOUSE);
    }
    // KIDDO — Activate kiddo layer with rainbow splash
    else if (leader_sequence_five_keys(KC_K, KC_I, KC_D, KC_D, KC_O)) {
        layer_on(_KIDDO);
#ifdef RGB_MATRIX_ENABLE
        rgb_matrix_mode_noeeprom(RGB_MATRIX_SPLASH);
        rgb_matrix_sethsv_noeeprom(0, 255, 255);
#endif
    }
    // RGB   — Activate RGB configuration layer
    else if (leader_sequence_three_keys(KC_R, KC_G, KC_B)) {
        layer_on(_RGB_CFG);
    }
}

// -----------------------------------------------------------------------------
// Key Processing
// -----------------------------------------------------------------------------

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Select-word feature (returns false when it consumes the event)
    if (!process_select_word(keycode, record, SELWORD)) {
        return false;
    }

    switch (keycode) {
        // Windows-specific shortcuts
        case KC_TASK_VIEW:
            if (record->event.pressed) {
                register_code(KC_LWIN);
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
                unregister_code(KC_LWIN);
            }
            return false;

        case KC_FILE_EXPLORER:
            if (record->event.pressed) {
                register_code(KC_LWIN);
                register_code(KC_E);
            } else {
                unregister_code(KC_E);
                unregister_code(KC_LWIN);
            }
            return false;

        // Toggle autocorrect
        case TOGGLE_AUTOCORRECT:
            if (record->event.pressed) {
                set_autocorrect_enabled(!get_autocorrect_enabled());
            }
            return false;

        // Toggle mouse jiggler
        case TOGGLE_JIGGLER:
            if (record->event.pressed) {
                set_mouse_jiggler_enabled(!get_mouse_jiggler_enabled());
            }
            return false;

        // RGB Presets
        case RGB_PRESET_1:
            if (record->event.pressed) {
                userspace_config.active_rgb_preset = 0;
                rgb_preset_apply(0);
                userspace_config_save();
            }
            return false;

        case RGB_PRESET_2:
            if (record->event.pressed) {
                userspace_config.active_rgb_preset = 1;
                rgb_preset_apply(1);
                userspace_config_save();
            }
            return false;

        case RGB_PRESET_3:
            if (record->event.pressed) {
                userspace_config.active_rgb_preset = 2;
                rgb_preset_apply(2);
                userspace_config_save();
            }
            return false;

        case RGB_PRESET_4:
            if (record->event.pressed) {
                userspace_config.active_rgb_preset = 3;
                rgb_preset_apply(3);
                userspace_config_save();
            }
            return false;

        // Task Manager (Ctrl+Shift+Esc)
        case TASK_MGR:
            if (record->event.pressed) {
                register_code(KC_LCTL);
                register_code(KC_LSFT);
                register_code(KC_ESC);
            } else {
                unregister_code(KC_ESC);
                unregister_code(KC_LSFT);
                unregister_code(KC_LCTL);
            }
            return false;
    }

    return true;
}

// -----------------------------------------------------------------------------
// RGB Matrix Indicators (portable, keycode-based)
// -----------------------------------------------------------------------------
#ifdef RGB_MATRIX_ENABLE

// Helper: Set LED color for a specific keycode on a given layer
static void set_led_color_for_keycode(uint8_t layer, uint16_t keycode,
                                      uint8_t r, uint8_t g, uint8_t b) {
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            uint16_t key = keymap_key_to_keycode(layer, (keypos_t){col, row});
            if (key == keycode) {
                uint8_t led_index = g_led_config.matrix_co[row][col];
                if (led_index != NO_LED) {
                    rgb_matrix_set_color(led_index, r, g, b);
                }
            }
        }
    }
}

// Features Layer indicators
void rgb_matrix_indicators_features_layer(void) {
    // F4 — Task Manager (chartreuse)
    set_led_color_for_keycode(_FEATURES, TASK_MGR, RGB_CHARTREUSE);
    // F5–F8 — RGB Presets (chartreuse)
    set_led_color_for_keycode(_FEATURES, RGB_PRESET_1, RGB_CHARTREUSE);
    set_led_color_for_keycode(_FEATURES, RGB_PRESET_2, RGB_CHARTREUSE);
    set_led_color_for_keycode(_FEATURES, RGB_PRESET_3, RGB_CHARTREUSE);
    set_led_color_for_keycode(_FEATURES, RGB_PRESET_4, RGB_CHARTREUSE);

    // Autocorrect toggle (blue=on, orange=off)
    if (get_autocorrect_enabled()) {
        set_led_color_for_keycode(_FEATURES, TOGGLE_AUTOCORRECT, RGB_BLUE);
    } else {
        set_led_color_for_keycode(_FEATURES, TOGGLE_AUTOCORRECT, RGB_ORANGE);
    }

    // Mouse Jiggler toggle (blue=on, orange=off)
    if (get_mouse_jiggler_enabled()) {
        set_led_color_for_keycode(_FEATURES, TOGGLE_JIGGLER, RGB_BLUE);
    } else {
        set_led_color_for_keycode(_FEATURES, TOGGLE_JIGGLER, RGB_ORANGE);
    }

    // NKRO toggle (blue=on, orange=off)
    if (keymap_config.nkro) {
        set_led_color_for_keycode(_FEATURES, NK_TOGG, RGB_BLUE);
    } else {
        set_led_color_for_keycode(_FEATURES, NK_TOGG, RGB_ORANGE);
    }

    // Firmware reset (red — dangerous)
    set_led_color_for_keycode(_FEATURES, QK_BOOT, RGB_RED);

    // Leader key (purple)
    set_led_color_for_keycode(_FEATURES, QK_LEAD, RGB_PURPLE);

    // Features layer key itself (purple)
    set_led_color_for_keycode(_FEATURES, FN_FEAT, RGB_PURPLE);
}

// Gaming Layer indicators
void rgb_matrix_indicators_gaming_layer(void) {
    // Highlight WASD
    set_led_color_for_keycode(_GAMING, KC_W, RGB_GREEN);
    set_led_color_for_keycode(_GAMING, KC_A, RGB_GREEN);
    set_led_color_for_keycode(_GAMING, KC_S, RGB_GREEN);
    set_led_color_for_keycode(_GAMING, KC_D, RGB_GREEN);

    // Surrounding keys
    set_led_color_for_keycode(_GAMING, KC_Q, RGB_WHITE);
    set_led_color_for_keycode(_GAMING, KC_E, RGB_ORANGE);
    set_led_color_for_keycode(_GAMING, KC_R, RGB_WHITE);
    set_led_color_for_keycode(_GAMING, KC_F, RGB_WHITE);
    set_led_color_for_keycode(_GAMING, KC_Z, RGB_WHITE);
    set_led_color_for_keycode(_GAMING, KC_X, RGB_WHITE);
    set_led_color_for_keycode(_GAMING, KC_C, RGB_WHITE);
    set_led_color_for_keycode(_GAMING, KC_V, RGB_WHITE);
    set_led_color_for_keycode(_GAMING, KC_TAB, RGB_WHITE);
    set_led_color_for_keycode(_GAMING, KC_LSFT, RGB_WHITE);
    set_led_color_for_keycode(_GAMING, KC_LCTL, RGB_WHITE);
    set_led_color_for_keycode(_GAMING, KC_SPC, RGB_GREEN);

    // Number keys + grave
    set_led_color_for_keycode(_GAMING, KC_1, RGB_ORANGE);
    set_led_color_for_keycode(_GAMING, KC_2, RGB_ORANGE);
    set_led_color_for_keycode(_GAMING, KC_3, RGB_ORANGE);
    set_led_color_for_keycode(_GAMING, KC_4, RGB_ORANGE);
    set_led_color_for_keycode(_GAMING, KC_GRV, RGB_WHITE);

    // Disabled keys in dark red
    set_led_color_for_keycode(_GAMING, KC_NO, 0x28, 0x00, 0x00);
}

// Mouse Layer indicators
void rgb_matrix_indicators_mouse_layer(void) {
    // Mouse movement via arrow keys
    set_led_color_for_keycode(_MOUSE, MS_UP,   RGB_CHARTREUSE);
    set_led_color_for_keycode(_MOUSE, MS_DOWN, RGB_CHARTREUSE);
    set_led_color_for_keycode(_MOUSE, MS_LEFT, RGB_CHARTREUSE);
    set_led_color_for_keycode(_MOUSE, MS_RGHT, RGB_CHARTREUSE);

    // Mouse buttons
    set_led_color_for_keycode(_MOUSE, MS_BTN1, RGB_SPRINGGREEN);
    set_led_color_for_keycode(_MOUSE, MS_BTN2, RGB_SPRINGGREEN);

    // Tap-dance ESC to exit (purple)
    set_led_color_for_keycode(_MOUSE, TD(TD_ESC_MOUSE), RGB_PURPLE);

    // Disabled keys
    set_led_color_for_keycode(_MOUSE, KC_NO, 0x28, 0x00, 0x00);
}

// Kiddo Layer indicators
void rgb_matrix_indicators_kiddo_layer(void) {
    // ESC to exit (purple)
    set_led_color_for_keycode(_KIDDO, TD(TD_ESC_KIDDO), RGB_PURPLE);
}

// RGB Config Layer indicators
void rgb_matrix_indicators_rgb_layer(void) {
    // ESC to exit (purple)
    set_led_color_for_keycode(_RGB_CFG, TD(TD_ESC_RGB), RGB_PURPLE);
}

// Leader Layer indicators
void rgb_matrix_indicators_leader_layer(void) {
    // Leader key glowing when active
    set_led_color_for_keycode(_LEADER, QK_LEAD, RGB_BLUE);
    // Disabled keys
    set_led_color_for_keycode(_LEADER, KC_NO, 0x28, 0x00, 0x00);
}

// Main RGB indicator hook
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    (void)led_min;
    (void)led_max;

    // CapsLock indicator: light the Caps key blue when active
    if (host_keyboard_led_state().caps_lock) {
        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            for (uint8_t col = 0; col < MATRIX_COLS; col++) {
                uint16_t key = keymap_key_to_keycode(0, (keypos_t){col, row});
                if (key == KC_CAPS) {
                    uint8_t led_index = g_led_config.matrix_co[row][col];
                    if (led_index != NO_LED) {
                        rgb_matrix_set_color(led_index, RGB_BLUE);
                    }
                }
            }
        }
    }

    // Layer-specific indicators
    switch (get_highest_layer(layer_state)) {
        case _FEATURES:
            rgb_matrix_indicators_features_layer();
            break;
        case _GAMING:
            rgb_matrix_indicators_gaming_layer();
            break;
        case _MOUSE:
            rgb_matrix_indicators_mouse_layer();
            break;
        case _KIDDO:
            rgb_matrix_indicators_kiddo_layer();
            break;
        case _RGB_CFG:
            rgb_matrix_indicators_rgb_layer();
            break;
        case _LEADER:
            rgb_matrix_indicators_leader_layer();
            break;
    }

    return false;
}
#endif  // RGB_MATRIX_ENABLE

