// Copyright 2025 MockLogic (@mocklogic)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include QMK_KEYBOARD_H

// Layer definitions - MUST be in same order for all keyboards
// Layers 0-3 are reserved for Keychron physical OS switch
enum mocklogic_layers {
    _MAC_BASE = 0,  // Mac base layer (physical OS switch position)
    _MAC_FN,        // Mac function layer (unused, reserved for OS switch)
    _WIN_BASE,      // Windows base layer (physical OS switch position)
    _WIN_FN,        // Windows function layer (unused, reserved for OS switch)
    _FEATURES,      // Feature control layer (momentary)
    _GAMING,        // Gaming mode layer
    _MOUSE,         // Mouse control layer
    _KIDDO,         // Kiddo layer (for toddler entertainment)
    _RGB_CFG,       // RGB configuration layer
    _LEADER         // Leader key active layer
};

// Custom keycodes
enum mocklogic_keycodes {
    // Windows/Mac-specific keys (note: KC_MISSION_CONTROL and KC_LAUNCHPAD are now built-in)
    KC_TASK_VIEW = SAFE_RANGE,
    KC_FILE_EXPLORER,

    // Feature toggles
    TOGGLE_AUTOCORRECT,  // Toggle autocorrect on/off
    TOGGLE_JIGGLER,      // Toggle mouse jiggler on/off

    // RGB preset selection
    RGB_PRESET_1,  // F5 - No backlighting
    RGB_PRESET_2,  // F6 - Dim warm white
    RGB_PRESET_3,  // F7 - Bright warm white
    RGB_PRESET_4,  // F8 - Fun RGB reactive

    // RGB config layer - effect selection
    RGB_EFF_SOLID,      // Solid color
    RGB_EFF_STARLIGHT,  // Starlight dual
    RGB_EFF_RAINDROPS,  // Raindrops
    RGB_EFF_DIGRAIN,    // Digital rain
    RGB_EFF_SPIRAL,     // Rainbow pinwheel
    RGB_EFF_SPLASH,     // Rainbow splash ripples
    RGB_EFF_RIVER,      // Riverflow
    RGB_EFF_HEATMAP,    // Typing heatmap
    RGB_CFG_RESET,      // Reset to saved RGB config

    // RGB config layer - adjustments
    RGB_BRIGHT_UP,      // Increase brightness
    RGB_BRIGHT_DOWN,    // Decrease brightness
    RGB_SPEED_UP,       // Increase animation speed
    RGB_SPEED_DOWN,     // Decrease animation speed
    RGB_SAT_UP,         // Increase saturation
    RGB_SAT_DOWN,       // Decrease saturation

    // Utility keys
    SELWORD,       // Select word/line
    TASK_MGR,      // Windows Task Manager (Ctrl+Shift+Esc)
    EEPROM_RESET,  // Reset EEPROM to defaults

    // Dual-layer function keys (activates OS-specific FN + Features layer)
    FN_MAC,        // Mac FN key (activates _MAC_FN + _FEATURES)
    FN_WIN,        // Windows FN key (activates _WIN_FN + _FEATURES)

    // Safe range for keyboard-specific keycodes
    MOCKLOGIC_SAFE_RANGE
};

// Tap Dance declarations
enum {
    TD_ESC_MOUSE,   // Double-tap ESC to exit mouse layer
    TD_ESC_KIDDO,   // Double-tap ESC to exit kiddo layer
    TD_ESC_RGB,     // Double-tap ESC to exit RGB config layer
    TD_ESC_GAMING   // Double-tap ESC to exit gaming layer
};

// Shorter aliases
#define KC_MCTL KC_MISSION_CONTROL
#define KC_LPAD KC_LAUNCHPAD
#define KC_TASK KC_TASK_VIEW
#define KC_FLXP KC_FILE_EXPLORER

// Mac modifier key codes
#define KC_LOPTN KC_LOPT
#define KC_ROPTN KC_ROPT
#define KC_LCMMD KC_LCMD
#define KC_RCMMD KC_RCMD

// Feature layer access
#define FN_FEAT MO(_FEATURES)

// EEPROM configuration structure
typedef union {
    uint64_t raw;  // Expanded to 64 bits to fit RGB preset data
    struct {
        bool     autocorrect_enabled :1;
        bool     mouse_jiggler_enabled :1;
        uint8_t  active_rgb_preset :2;  // 0-3 for 4 presets
        uint8_t  reserved :4;            // Reserved for future use
        // RGB Preset 4 (F8) custom configuration (5 bytes = 40 bits)
        uint8_t  rgb_preset_mode;        // RGB effect mode
        uint8_t  rgb_preset_hue;         // Hue (0-255)
        uint8_t  rgb_preset_sat;         // Saturation (0-255)
        uint8_t  rgb_preset_val;         // Brightness (0-255)
        uint8_t  rgb_preset_speed;       // Animation speed (0-255)
    };
} userspace_config_t;

extern userspace_config_t userspace_config;

// Function declarations
void eeconfig_init_user_datablock(void);
void keyboard_post_init_user_rgb(void);
void userspace_config_save(void);
void userspace_config_load(void);

// Feature: Select Word
bool process_select_word(uint16_t keycode, keyrecord_t* record, uint16_t sel_keycode);

// Feature: RGB Presets
void rgb_preset_apply(uint8_t preset);
void rgb_preset_init(void);

// Feature: Mouse Jiggler
bool get_mouse_jiggler_enabled(void);
void set_mouse_jiggler_enabled(bool enabled);

// Feature: Autocorrect
bool get_autocorrect_enabled(void);
void set_autocorrect_enabled(bool enabled);

// RGB Indicator functions (implemented per-keyboard due to different LED mappings)
void rgb_matrix_indicators_features_layer(void);
void rgb_matrix_indicators_gaming_layer(void);
void rgb_matrix_indicators_mouse_layer(void);
void rgb_matrix_indicators_kiddo_layer(void);
void rgb_matrix_indicators_rgb_layer(void);
void rgb_matrix_indicators_leader_layer(void);
