// Copyright 2025 MockLogic (@mocklogic)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "rgb_presets.h"
#include "mocklogic.h"

#ifdef RGB_MATRIX_ENABLE

typedef struct {
    uint8_t mode;
    uint8_t hue;
    uint8_t sat;
    uint8_t val;
    uint8_t speed;
} rgb_preset_config_t;

// RGB config layer state - tracks changes during layer session
static struct {
    bool active;
    rgb_preset_config_t temp_preset;
} rgb_config_state;

// Define the first 3 RGB presets (hardcoded, not configurable)
static const rgb_preset_config_t rgb_presets_fixed[] = {
    // Preset 0 (F5): No backlighting
    {
        .mode = RGB_MATRIX_SOLID_COLOR,
        .hue = 0,
        .sat = 0,
        .val = 0,
        .speed = 0
    },
    // Preset 1 (F6): Dim neutral white (default)
    {
        .mode = RGB_MATRIX_SOLID_COLOR,
        .hue = 0,
        .sat = 0,
        .val = 60,
        .speed = 0
    },
    // Preset 2 (F7): Bright neutral white
    {
        .mode = RGB_MATRIX_SOLID_COLOR,
        .hue = 0,
        .sat = 0,
        .val = 200,
        .speed = 0
    }
};

// Default for Preset 3 (F8): Fun RGB reactive (loaded from EEPROM or this default)
static const rgb_preset_config_t rgb_preset_4_default = {
    .mode = RGB_MATRIX_TYPING_HEATMAP,
    .hue = 0,
    .sat = 255,
    .val = 255,
    .speed = RGB_MATRIX_SPD_STEP * 2  // Medium speed
};

void rgb_preset_init(void) {
    // Validate 4th preset from EEPROM (already loaded by userspace_config_load)
    // Check if mode is invalid (>= max) or if it's a mode we disabled
    if (userspace_config.rgb_preset_mode >= RGB_MATRIX_EFFECT_MAX) {
        // Use default if invalid
        userspace_config.rgb_preset_mode = rgb_preset_4_default.mode;
        userspace_config.rgb_preset_hue = rgb_preset_4_default.hue;
        userspace_config.rgb_preset_sat = rgb_preset_4_default.sat;
        userspace_config.rgb_preset_val = rgb_preset_4_default.val;
        userspace_config.rgb_preset_speed = rgb_preset_4_default.speed;
        userspace_config_save();
    }

    // Initialize config state as inactive
    rgb_config_state.active = false;
}

void rgb_preset_apply(uint8_t preset) {
    if (preset > 3) {
        preset = 1;  // Default to dim white if invalid
    }

    // Apply the preset configuration
    // Note: We always keep RGB enabled so that indicators can work
    // Setting val=0 will turn off the base effect while allowing indicators to show
    rgb_matrix_enable();

    if (preset < 3) {
        // Presets 0-2: Use fixed presets
        const rgb_preset_config_t *config = &rgb_presets_fixed[preset];
        rgb_matrix_mode(config->mode);
        rgb_matrix_sethsv(config->hue, config->sat, config->val);
        rgb_matrix_set_speed(config->speed);
    } else {
        // Preset 3 (F8): Use custom preset from EEPROM
        rgb_matrix_mode(userspace_config.rgb_preset_mode);
        rgb_matrix_sethsv(userspace_config.rgb_preset_hue,
                          userspace_config.rgb_preset_sat,
                          userspace_config.rgb_preset_val);
        rgb_matrix_set_speed(userspace_config.rgb_preset_speed);
    }
}

// Enter RGB config layer - activate preset 4 and start tracking changes
void rgb_config_layer_enter(void) {
    rgb_config_state.active = true;

    // Copy current preset 4 settings from EEPROM to temp state
    rgb_config_state.temp_preset.mode = userspace_config.rgb_preset_mode;
    rgb_config_state.temp_preset.hue = userspace_config.rgb_preset_hue;
    rgb_config_state.temp_preset.sat = userspace_config.rgb_preset_sat;
    rgb_config_state.temp_preset.val = userspace_config.rgb_preset_val;
    rgb_config_state.temp_preset.speed = userspace_config.rgb_preset_speed;

    // If saturation is 0, use full saturation for color effects (avoid white/grayscale)
    if (rgb_config_state.temp_preset.sat == 0) {
        rgb_config_state.temp_preset.sat = 255;
    }

    // Apply preset 4 (using temp settings)
    rgb_matrix_enable();
    rgb_matrix_mode(rgb_config_state.temp_preset.mode);
    rgb_matrix_sethsv(rgb_config_state.temp_preset.hue,
                      rgb_config_state.temp_preset.sat,
                      rgb_config_state.temp_preset.val);
    rgb_matrix_set_speed(rgb_config_state.temp_preset.speed);
}

// Exit RGB config layer - save settings to EEPROM and preset 4
void rgb_config_layer_exit(void) {
    if (!rgb_config_state.active) return;

    // Save temp settings to preset 4 in EEPROM
    userspace_config.rgb_preset_mode = rgb_config_state.temp_preset.mode;
    userspace_config.rgb_preset_hue = rgb_config_state.temp_preset.hue;
    userspace_config.rgb_preset_sat = rgb_config_state.temp_preset.sat;
    userspace_config.rgb_preset_val = rgb_config_state.temp_preset.val;
    userspace_config.rgb_preset_speed = rgb_config_state.temp_preset.speed;
    userspace_config_save();

    rgb_config_state.active = false;

    // Keep the preset active (already applied via temp settings)
}

// Reset to saved preset 4 settings (F8 key press)
void rgb_config_layer_reset(void) {
    if (!rgb_config_state.active) return;

    // Reload from saved EEPROM preset
    rgb_config_state.temp_preset.mode = userspace_config.rgb_preset_mode;
    rgb_config_state.temp_preset.hue = userspace_config.rgb_preset_hue;
    rgb_config_state.temp_preset.sat = userspace_config.rgb_preset_sat;
    rgb_config_state.temp_preset.val = userspace_config.rgb_preset_val;
    rgb_config_state.temp_preset.speed = userspace_config.rgb_preset_speed;

    // Reapply
    rgb_matrix_mode(rgb_config_state.temp_preset.mode);
    rgb_matrix_sethsv(rgb_config_state.temp_preset.hue,
                      rgb_config_state.temp_preset.sat,
                      rgb_config_state.temp_preset.val);
    rgb_matrix_set_speed(rgb_config_state.temp_preset.speed);
}

// Set RGB effect mode
void rgb_config_set_effect(uint8_t mode) {
    if (!rgb_config_state.active) return;

    rgb_config_state.temp_preset.mode = mode;
    rgb_matrix_mode(mode);
}

// Adjust hue (encoder rotation)
void rgb_config_adjust_hue(int8_t delta) {
    if (!rgb_config_state.active) return;

    // Delta is already in HSV units from encoder
    int16_t new_hue = rgb_config_state.temp_preset.hue + delta;
    if (new_hue < 0) new_hue += 256;
    if (new_hue > 255) new_hue -= 256;

    rgb_config_state.temp_preset.hue = (uint8_t)new_hue;
    rgb_matrix_sethsv(rgb_config_state.temp_preset.hue,
                      rgb_config_state.temp_preset.sat,
                      rgb_config_state.temp_preset.val);
}

// Adjust saturation (if needed)
void rgb_config_adjust_sat(int8_t delta) {
    if (!rgb_config_state.active) return;

    int16_t new_sat = rgb_config_state.temp_preset.sat + delta;
    if (new_sat < 0) new_sat = 0;
    if (new_sat > 255) new_sat = 255;

    rgb_config_state.temp_preset.sat = (uint8_t)new_sat;
    rgb_matrix_sethsv(rgb_config_state.temp_preset.hue,
                      rgb_config_state.temp_preset.sat,
                      rgb_config_state.temp_preset.val);
}

// Adjust brightness (up/down arrows)
void rgb_config_adjust_val(int8_t delta) {
    if (!rgb_config_state.active) return;

    int16_t new_val = rgb_config_state.temp_preset.val + delta;
    if (new_val < 0) new_val = 0;
    if (new_val > 255) new_val = 255;

    rgb_config_state.temp_preset.val = (uint8_t)new_val;
    rgb_matrix_sethsv(rgb_config_state.temp_preset.hue,
                      rgb_config_state.temp_preset.sat,
                      rgb_config_state.temp_preset.val);
}

// Adjust speed (left/right arrows)
void rgb_config_adjust_speed(int8_t delta) {
    if (!rgb_config_state.active) return;

    int16_t new_speed = rgb_config_state.temp_preset.speed + delta;
    if (new_speed < 0) new_speed = 0;
    if (new_speed > 255) new_speed = 255;

    rgb_config_state.temp_preset.speed = (uint8_t)new_speed;
    rgb_matrix_set_speed(rgb_config_state.temp_preset.speed);
}

#endif // RGB_MATRIX_ENABLE
