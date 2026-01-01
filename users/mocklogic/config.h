// Copyright 2025 MockLogic (@mocklogic)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// ============================================================================
// Firmware Size Optimizations
// ============================================================================

// Disable unused features to save space
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

// ============================================================================
// Leader Key Settings
// ============================================================================

#define LEADER_TIMEOUT 500
#define LEADER_PER_KEY_TIMING // Timing is between key presses not overall
#define LEADER_NO_TIMEOUT     // No time out after leader key to start sequence

// ============================================================================
// Tapping Settings
// ============================================================================

#define TAPPING_TERM 200
#define TAPPING_TOGGLE 2  // TT set to two taps

// ============================================================================
// Autocorrect Settings
// ============================================================================

#define AUTOCORRECT_MIN_LENGTH 5

// ============================================================================
// RGB Matrix Settings - Only enable effects we actually use
// ============================================================================

#ifdef RGB_MATRIX_ENABLE
    #define RGB_MATRIX_FRAMEBUFFER_EFFECTS
    #define RGB_MATRIX_KEYPRESSES

    // Enable ONLY the 8 RGB effects used in _RGB_CFG layer (F1-F4, F9-F12)
    #define ENABLE_RGB_MATRIX_SOLID_COLOR           // F1: Solid color
    #define ENABLE_RGB_MATRIX_STARLIGHT_DUAL_HUE    // F2: Starlight
    #define ENABLE_RGB_MATRIX_RAINDROPS             // F3: Raindrops
    #define ENABLE_RGB_MATRIX_DIGITAL_RAIN          // F4: Digital Rain
    #define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL        // F9: Spiral/Pinwheel
    #define ENABLE_RGB_MATRIX_MULTISPLASH           // F10: Splash ripples
    #define ENABLE_RGB_MATRIX_RIVERFLOW             // F11: Riverflow
    #define ENABLE_RGB_MATRIX_TYPING_HEATMAP        // F12: Typing Heatmap

    // Presets 1-3 use SOLID_COLOR, Preset 4 uses TYPING_HEATMAP
    // All 32+ other built-in effects are disabled to save ~18KB

    #define RGB_DISABLE_WHEN_USB_SUSPENDED
#endif
