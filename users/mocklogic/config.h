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
    #define ENABLE_RGB_MATRIX_TYPING_HEATMAP
    #define ENABLE_RGB_MATRIX_SPLASH
    #define RGB_DISABLE_WHEN_USB_SUSPENDED
#endif
