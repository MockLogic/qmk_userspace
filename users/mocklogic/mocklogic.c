// Copyright 2025 MockLogic (@mocklogic)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "mocklogic.h"
#include "features/select_word.h"
#include "features/rgb_presets.h"
#include "features/whack_a_mole.h"
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

    // Initialize RGB preset 4 (F8) defaults
    userspace_config.rgb_preset_mode = RGB_MATRIX_TYPING_HEATMAP;
    userspace_config.rgb_preset_hue = 0;
    userspace_config.rgb_preset_sat = 255;
    userspace_config.rgb_preset_val = 255;
    userspace_config.rgb_preset_speed = RGB_MATRIX_SPD_STEP * 2;

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

    // GAME  — Enter gaming layer (exit with double-tap ESC)
    if (leader_sequence_four_keys(KC_G, KC_A, KC_M, KC_E)) {
        layer_on(_GAMING);
    }
    // MOUSE — Activate mouse layer
    else if (leader_sequence_five_keys(KC_M, KC_O, KC_U, KC_S, KC_E)) {
        layer_on(_MOUSE);
    }
    // KIDDO — Activate kiddo layer with whack-a-mole game
    else if (leader_sequence_five_keys(KC_K, KC_I, KC_D, KC_D, KC_O)) {
        layer_on(_KIDDO);
#ifdef RGB_MATRIX_ENABLE
        // Set to solid black background so only custom indicators show (mole key + ESC)
        // Reactive rainbow ripple still works due to RGB_MATRIX_KEYPRESSES
        rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
        rgb_matrix_sethsv_noeeprom(0, 0, 0);  // Black background
#endif
    }
    // RGB   — Activate RGB configuration layer
    else if (leader_sequence_three_keys(KC_R, KC_G, KC_B)) {
        layer_on(_RGB_CFG);
        rgb_config_layer_enter();
    }
    // END   — Send End key (for 75% keyboards missing this key)
    else if (leader_sequence_three_keys(KC_E, KC_N, KC_D)) {
        tap_code(KC_END);
    }
    // INS   — Send Insert key (for 75% keyboards missing this key)
    else if (leader_sequence_three_keys(KC_I, KC_N, KC_S)) {
        tap_code(KC_INS);
    }
    // PRINT — Send Print Screen key (for 75% keyboards missing this key)
    else if (leader_sequence_five_keys(KC_P, KC_R, KC_I, KC_N, KC_T)) {
        tap_code(KC_PSCR);
    }
}

// -----------------------------------------------------------------------------
// Key Processing
// -----------------------------------------------------------------------------

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Whack-a-mole game (only active on Kiddo layer)
    if (layer_state_is(_KIDDO)) {
        // On Kiddo layer, all keys are KC_NO, so we need to look up the actual keycode
        // from the base layer to know what key was physically pressed
        uint16_t base_keycode = keycode;
        if (keycode == KC_NO) {
            // Look up the keycode from Mac or Windows base layer
            uint8_t base_layer = get_highest_layer(default_layer_state); // 0 for Mac, 2 for Windows
            base_keycode = keymap_key_to_keycode(base_layer, record->event.key);
        }

        if (whack_a_mole_process_key(base_keycode, record)) {
            return false; // Game consumed the keypress
        }
    }

    // RGB config layer - handle encoder hue controls
    if (layer_state_is(_RGB_CFG) && record->event.pressed) {
        switch (keycode) {
            case RM_HUEU:
                rgb_config_adjust_hue(RGB_MATRIX_HUE_STEP);
                return false;
            case RM_HUED:
                rgb_config_adjust_hue(-RGB_MATRIX_HUE_STEP);
                return false;
            default:
                break;
        }
    }

    // Select-word feature (returns false when it consumes the event)
    if (!process_select_word(keycode, record, SELWORD)) {
        return false;
    }

    switch (keycode) {
        // Dual-layer function keys
        case FN_MAC:
            if (record->event.pressed) {
                layer_on(_MAC_FN);
                layer_on(_FEATURES);
            } else {
                layer_off(_MAC_FN);
                layer_off(_FEATURES);
            }
            return false;

        case FN_WIN:
            if (record->event.pressed) {
                layer_on(_WIN_FN);
                layer_on(_FEATURES);
            } else {
                layer_off(_WIN_FN);
                layer_off(_FEATURES);
            }
            return false;

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

        // RGB Config Layer - Effect Selection
        case RGB_EFF_SOLID:
            if (record->event.pressed) {
                rgb_config_set_effect(RGB_MATRIX_SOLID_COLOR);
            }
            return false;

        case RGB_EFF_STARLIGHT:
            if (record->event.pressed) {
                rgb_config_set_effect(RGB_MATRIX_STARLIGHT_DUAL_HUE);
            }
            return false;

        case RGB_EFF_RAINDROPS:
            if (record->event.pressed) {
                rgb_config_set_effect(RGB_MATRIX_RAINDROPS);
            }
            return false;

        case RGB_EFF_DIGRAIN:
            if (record->event.pressed) {
                rgb_config_set_effect(RGB_MATRIX_DIGITAL_RAIN);
            }
            return false;

        case RGB_EFF_SPIRAL:
            if (record->event.pressed) {
                rgb_config_set_effect(RGB_MATRIX_CYCLE_PINWHEEL);
            }
            return false;

        case RGB_EFF_SPLASH:
            if (record->event.pressed) {
                rgb_config_set_effect(RGB_MATRIX_MULTISPLASH);
            }
            return false;

        case RGB_EFF_RIVER:
            if (record->event.pressed) {
                rgb_config_set_effect(RGB_MATRIX_RIVERFLOW);
            }
            return false;

        case RGB_EFF_HEATMAP:
            if (record->event.pressed) {
                rgb_config_set_effect(RGB_MATRIX_TYPING_HEATMAP);
            }
            return false;

        case RGB_CFG_RESET:
            if (record->event.pressed) {
                rgb_config_layer_reset();
            }
            return false;

        // RGB Config Layer - Adjustments
        case RGB_BRIGHT_UP:
            if (record->event.pressed) {
                rgb_config_adjust_val(RGB_MATRIX_VAL_STEP);
            }
            return false;

        case RGB_BRIGHT_DOWN:
            if (record->event.pressed) {
                rgb_config_adjust_val(-RGB_MATRIX_VAL_STEP);
            }
            return false;

        case RGB_SPEED_UP:
            if (record->event.pressed) {
                rgb_config_adjust_speed(RGB_MATRIX_SPD_STEP);
            }
            return false;

        case RGB_SPEED_DOWN:
            if (record->event.pressed) {
                rgb_config_adjust_speed(-RGB_MATRIX_SPD_STEP);
            }
            return false;

        case RGB_SAT_UP:
            if (record->event.pressed) {
                rgb_config_adjust_sat(RGB_MATRIX_SAT_STEP);
            }
            return false;

        case RGB_SAT_DOWN:
            if (record->event.pressed) {
                rgb_config_adjust_sat(-RGB_MATRIX_SAT_STEP);
            }
            return false;

        // EEPROM Reset
        case EEPROM_RESET:
            if (record->event.pressed) {
                eeconfig_init();  // Reset all EEPROM to defaults
                soft_reset_keyboard();  // Restart keyboard
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
// Layer State Management
// -----------------------------------------------------------------------------

layer_state_t layer_state_set_user(layer_state_t state) {
    // Initialize whack-a-mole game when entering Kiddo layer
    if (layer_state_cmp(state, _KIDDO) && !layer_state_cmp(layer_state, _KIDDO)) {
        whack_a_mole_init();
    }
    return state;
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

    // Only show these when the Win Fn layer is active
    if (layer_state_is(_WIN_FN)) {
        // F4 — Task Manager (green)
        set_led_color_for_keycode(_WIN_FN, TASK_MGR, RGB_GREEN);
        // Show Desktop (green)
        set_led_color_for_keycode(_WIN_FN, G(KC_D), RGB_GREEN);
        // Clipboard History (green)
        set_led_color_for_keycode(_WIN_FN, G(KC_V), RGB_GREEN);
    }

    // Only show these when the Mac Fn layer is active
    if (layer_state_is(_MAC_FN)) {
        // Paste (green)
        set_led_color_for_keycode(_MAC_FN, C(KC_V), RGB_GREEN);
    }

    // F5–F8 — RGB Presets (chartreuse)
    set_led_color_for_keycode(_FEATURES, RGB_PRESET_1, RGB_CHARTREUSE);
    set_led_color_for_keycode(_FEATURES, RGB_PRESET_2, RGB_CHARTREUSE);
    set_led_color_for_keycode(_FEATURES, RGB_PRESET_3, RGB_CHARTREUSE);
    set_led_color_for_keycode(_FEATURES, RGB_PRESET_4, RGB_CHARTREUSE);

    // EEPROM Reset (red) - on '0' key
    set_led_color_for_keycode(_FEATURES, EEPROM_RESET, RGB_RED);

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

    // Features layer keys (purple) - both Mac and Windows variants
    set_led_color_for_keycode(_FEATURES, FN_MAC, RGB_PURPLE);
    set_led_color_for_keycode(_FEATURES, FN_WIN, RGB_PURPLE);
}

// Gaming Layer indicators
void rgb_matrix_indicators_gaming_layer(void) {
    // ESC to exit (purple)
    set_led_color_for_keycode(_GAMING, TD(TD_ESC_GAMING), RGB_PURPLE);

    // Highlight WASD
    set_led_color_for_keycode(_GAMING, KC_W, RGB_GREEN);
    set_led_color_for_keycode(_GAMING, KC_A, RGB_GREEN);
    set_led_color_for_keycode(_GAMING, KC_S, RGB_GREEN);
    set_led_color_for_keycode(_GAMING, KC_D, RGB_GREEN);

    // A Few Surrounding keys
    set_led_color_for_keycode(_GAMING, KC_E, RGB_ORANGE);
    set_led_color_for_keycode(_GAMING, KC_R, RGB_WHITE);

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

// Helper: Find matrix position for a keycode by searching base layers
static bool find_keycode_position(uint16_t keycode, uint8_t *out_row, uint8_t *out_col) {
    // Search Mac base layer first, then Windows base layer
    for (uint8_t layer = 0; layer <= 2; layer += 2) {  // Layer 0 (Mac) and 2 (Windows)
        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            for (uint8_t col = 0; col < MATRIX_COLS; col++) {
                if (keymap_key_to_keycode(layer, (keypos_t){col, row}) == keycode) {
                    *out_row = row;
                    *out_col = col;
                    return true;
                }
            }
        }
    }
    return false;
}

// Kiddo Layer indicators
void rgb_matrix_indicators_kiddo_layer(void) {
    // Update whack-a-mole game state
    whack_a_mole_task();

    // Check if celebration ripple is active
    if (whack_a_mole_celebration_active()) {
        // Ripple effect - check all keys for ripple coloring
        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            for (uint8_t col = 0; col < MATRIX_COLS; col++) {
                uint8_t r, g, b;
                whack_a_mole_get_celebration_color(row, col, &r, &g, &b);
                // Only set color if it's non-black (within ripple)
                if (r != 0 || g != 0 || b != 0) {
                    uint8_t led = g_led_config.matrix_co[row][col];
                    if (led != NO_LED) {
                        rgb_matrix_set_color(led, r, g, b);
                    }
                }
            }
        }
    }
    // Show the active "mole" key
    else if (whack_a_mole_is_active()) {
        uint16_t active_key = whack_a_mole_get_active_key();
        uint8_t r, g, b;
        whack_a_mole_get_active_color(&r, &g, &b);

        // Find the matrix position for this keycode by searching base layers
        uint8_t row, col;
        if (find_keycode_position(active_key, &row, &col)) {
            uint8_t led = g_led_config.matrix_co[row][col];
            if (led != NO_LED) {
                rgb_matrix_set_color(led, r, g, b);
            }
        }
    }

    // ESC to exit (purple) - find ESC key position in base layer
    uint8_t esc_row, esc_col;
    if (find_keycode_position(KC_ESC, &esc_row, &esc_col)) {
        uint8_t led = g_led_config.matrix_co[esc_row][esc_col];
        if (led != NO_LED) {
            rgb_matrix_set_color(led, RGB_PURPLE);
        }
    }
}

// RGB Config Layer indicators
void rgb_matrix_indicators_rgb_layer(void) {
    // ESC to exit (purple)
    set_led_color_for_keycode(_RGB_CFG, TD(TD_ESC_RGB), RGB_PURPLE);

    // Effect selection keys (black/off to highlight against active effect)
    // Subtle effects
    set_led_color_for_keycode(_RGB_CFG, RGB_EFF_SOLID,     RGB_BLACK);
    set_led_color_for_keycode(_RGB_CFG, RGB_EFF_STARLIGHT, RGB_BLACK);
    set_led_color_for_keycode(_RGB_CFG, RGB_EFF_RAINDROPS, RGB_BLACK);
    set_led_color_for_keycode(_RGB_CFG, RGB_EFF_DIGRAIN,   RGB_BLACK);

    // Reset to saved preset
    set_led_color_for_keycode(_RGB_CFG, RGB_CFG_RESET, RGB_BLACK);

    // Crazy effects
    set_led_color_for_keycode(_RGB_CFG, RGB_EFF_SPIRAL,  RGB_BLACK);
    set_led_color_for_keycode(_RGB_CFG, RGB_EFF_SPLASH,  RGB_BLACK);
    set_led_color_for_keycode(_RGB_CFG, RGB_EFF_RIVER,   RGB_BLACK);
    set_led_color_for_keycode(_RGB_CFG, RGB_EFF_HEATMAP, RGB_BLACK);

    // Brightness, Speed, and Saturation controls
    set_led_color_for_keycode(_RGB_CFG, RGB_BRIGHT_UP,   RGB_BLACK);
    set_led_color_for_keycode(_RGB_CFG, RGB_BRIGHT_DOWN, RGB_BLACK);
    set_led_color_for_keycode(_RGB_CFG, RGB_SPEED_UP,    RGB_BLACK);
    set_led_color_for_keycode(_RGB_CFG, RGB_SPEED_DOWN,  RGB_BLACK);
    set_led_color_for_keycode(_RGB_CFG, RGB_SAT_UP,      RGB_BLACK);
    set_led_color_for_keycode(_RGB_CFG, RGB_SAT_DOWN,    RGB_BLACK);
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

