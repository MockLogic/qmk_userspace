// Copyright 2025 MockLogic (@mocklogic)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "rgb_presets.h"

#ifdef RGB_MATRIX_ENABLE

typedef struct {
    uint8_t mode;
    uint8_t hue;
    uint8_t sat;
    uint8_t val;
} rgb_preset_config_t;

// Define the 4 RGB presets
const rgb_preset_config_t rgb_presets[] = {
    // Preset 0 (F5): No backlighting
    {
        .mode = RGB_MATRIX_SOLID_COLOR,
        .hue = 0,
        .sat = 0,
        .val = 0  // Off
    },
    // Preset 1 (F6): Dim neutral white (default)
    {
        .mode = RGB_MATRIX_SOLID_COLOR,
        .hue = 0,    // Neutral white (no hue)
        .sat = 0,    // No saturation for true white
        .val = 60    // Dim brightness
    },
    // Preset 2 (F7): Bright neutral white
    {
        .mode = RGB_MATRIX_SOLID_COLOR,
        .hue = 0,    // Neutral white (no hue)
        .sat = 0,    // No saturation for true white
        .val = 200   // Bright
    },
    // Preset 3 (F8): Fun RGB reactive
    {
        .mode = RGB_MATRIX_TYPING_HEATMAP,  // Reactive heatmap effect
        .hue = 0,
        .sat = 255,
        .val = 255   // Full brightness, full color
    }
};

void rgb_preset_init(void) {
    // RGB matrix is already initialized by QMK
    // This function is here for future expansion if needed
}

void rgb_preset_apply(uint8_t preset) {
    if (preset > 3) {
        preset = 1;  // Default to dim white if invalid
    }

    const rgb_preset_config_t *config = &rgb_presets[preset];

    // Apply the preset configuration
    // Note: We always keep RGB enabled so that indicators can work
    // Setting val=0 will turn off the base effect while allowing indicators to show
    rgb_matrix_enable();
    rgb_matrix_mode(config->mode);
    rgb_matrix_sethsv(config->hue, config->sat, config->val);
}

#endif // RGB_MATRIX_ENABLE
