// Copyright 2025 MockLogic (@mocklogic)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Leader key settings
#define LEADER_TIMEOUT 500
#define LEADER_PER_KEY_TIMING // Timing is between key presses not overall
#define LEADER_NO_TIMEOUT     // No time out after leader key to start sequence

// Tapping settings
#define TAPPING_TERM 200
#define TAPPING_TOGGLE 2  // TT set to two taps

// Autocorrect settings
#define AUTOCORRECT_MIN_LENGTH 5

// RGB Matrix Settings
#ifdef RGB_MATRIX_ENABLE
    #define RGB_MATRIX_FRAMEBUFFER_EFFECTS
    #define RGB_MATRIX_KEYPRESSES

    // Enable RGB effects for RGB config layer
    #define ENABLE_RGB_MATRIX_SOLID_COLOR           // F1: Solid Color
    #define ENABLE_RGB_MATRIX_STARLIGHT_DUAL_HUE    // F2: Starlight Dual
    #define ENABLE_RGB_MATRIX_RAINDROPS             // F3: Raindrops
    #define ENABLE_RGB_MATRIX_DIGITAL_RAIN          // F4: Digital Rain
    #define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL        // F9: Rainbow Pinwheel
    #define ENABLE_RGB_MATRIX_MULTISPLASH           // F10: Rainbow splash ripples
    #define ENABLE_RGB_MATRIX_RIVERFLOW             // F11: Riverflow
    #define ENABLE_RGB_MATRIX_TYPING_HEATMAP        // F12: Typing Heatmap

    #define RGB_DISABLE_WHEN_USB_SUSPENDED
#endif
