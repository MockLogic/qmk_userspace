
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
#define RGB_MATRIX_STARTUP_HUE 15
#define RGB_MATRIX_STARTUP_SAT 40
#define RGB_MATRIX_STARTUP_VAL 60
#define RGB_DISABLE_WHEN_USB_SUSPENDED
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_KEYPRESSES
#define ENABLE_RGB_MATRIX_DIGITAL_RAIN
#define ENABLE_RGB_MATRIX_TYPING_HEATMAP
#define ENABLE_RGB_MATRIX_SPLASH
#endif

// Dynamic Macro Settings
#define DYNAMIC_MACRO_NO_NESTING

// CapsWord Settings
#define CAPS_WORD_IDLE_TIMEOUT 5000  // Turn off Caps Word after 5 seconds.

// AutoShift settings
#define AUTO_SHIFT_TIMEOUT 150 // How long a key needs to be pressed to be shifted. 
#define AUTO_SHIFT_DISABLED_AT_STARTUP // Use it, but not enabled by default.

// My Spacecadet Shift default
// #define SPACECADET_ENABLE_AT_STARTUP