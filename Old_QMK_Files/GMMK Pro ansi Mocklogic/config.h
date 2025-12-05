/* Copyright 2021 Jonavin Eng @Jonavin
   Copyright 2022 gourdo1 <jcblake@outlook.com>
   Messed with by MockLogic 2022
   
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#define TAPPING_TOGGLE 2
// TT set to two taps

/* Handle GRAVESC combo keys */
#define GRAVE_ESC_ALT_OVERRIDE
// Always send Escape if Alt is pressed
#define GRAVE_ESC_CTRL_OVERRIDE
// Always send Escape if Control is pressed

// #define TAPPING_TERM
#define TAPPING_TERM 200

// Leader key settings
#define LEADER_TIMEOUT 500
#define LEADER_PER_KEY_TIMING // Timing is between key presses not overall
#define LEADER_NO_TIMEOUT // No time out after leader key to start sequence. Timing kicks in after first key is pressed.

// RGB Matrix Settings
#ifdef RGB_MATRIX_ENABLE
#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_SOLID_COLOR
#define RGB_MATRIX_STARTUP_HUE 35
#define RGB_MATRIX_STARTUP_SAT 40
#define RGB_MATRIX_STARTUP_VAL 102
#define RGB_DISABLE_WHEN_USB_SUSPENDED
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_KEYPRESSES
#define ENABLE_RGB_MATRIX_DIGITAL_RAIN
#define ENABLE_RGB_MATRIX_TYPING_HEATMAP
#define ENABLE_RGB_MATRIX_SPLASH
#endif

// RGB step values
#define RGBLIGHT_HUE_STEP 10 // The number of steps to cycle through the hue by (default 10, was at 32)
#define RGBLIGHT_SAT_STEP 17 // The number of steps to increment the saturation by (default 17)
#define RGBLIGHT_VAL_STEP 17 // The number of steps to increment the brightness by (default 17)

// Dynamic Macro Settings
#define DYNAMIC_MACRO_NO_NESTING

// CapsWord Settings
#define CAPS_WORD_IDLE_TIMEOUT 5000  // Turn off Caps Word after 5 seconds.

// AutoShift settings
#define AUTO_SHIFT_TIMEOUT 150 // How long a key needs to be pressed to be shifted. 
#define AUTO_SHIFT_DISABLED_AT_STARTUP // Use it, but not enabled by default.

// My Spacecadet Shift default
// #define SPACECADET_ENABLE_AT_STARTUP