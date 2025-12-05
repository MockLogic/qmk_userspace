// Copyright 2025 MockLogic (@mocklogic)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "whack_a_mole.h"
#include "mocklogic.h"

// Game state
static struct {
    uint16_t active_key;       // Currently lit key
    uint32_t next_change_time; // When to pick next key (ms)
    uint8_t  color_r;          // Current color RGB
    uint8_t  color_g;
    uint8_t  color_b;
    bool     is_active;        // Is game running
    uint16_t hit_key;          // Key that was just hit (for celebration effect)
    uint8_t  hit_row;          // Row of hit key (for ripple calculation)
    uint8_t  hit_col;          // Column of hit key (for ripple calculation)
    uint32_t hit_start_time;   // When celebration started (ms)
    uint32_t hit_end_time;     // When celebration effect ends (ms)
} game_state;

// Valid keys for the game (alphanumeric + symbols, no ESC, no F-keys)
static const uint16_t valid_keys[] = {
    // Number row
    KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC,
    // Top row
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
    // Home row
    KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
    // Bottom row
    KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,
    // Spacebar
    KC_SPC
};

#define NUM_VALID_KEYS (sizeof(valid_keys) / sizeof(valid_keys[0]))

// Rainbow colors (bright and vibrant for toddlers!)
static const struct {
    uint8_t r, g, b;
} rainbow_colors[] = {
    {255, 0, 0},     // Red
    {255, 127, 0},   // Orange
    {255, 255, 0},   // Yellow
    {0, 255, 0},     // Green
    {0, 255, 255},   // Cyan
    {0, 0, 255},     // Blue
    {255, 0, 255},   // Magenta
    {255, 0, 127},   // Pink
};

#define NUM_COLORS (sizeof(rainbow_colors) / sizeof(rainbow_colors[0]))

// Select a random valid key
static uint16_t select_random_key(void) {
    // Use timer as random seed
    uint32_t seed = timer_read32();
    uint8_t index = (seed * 13 + timer_read()) % NUM_VALID_KEYS;
    return valid_keys[index];
}

// Select a random color
static void select_random_color(void) {
    uint32_t seed = timer_read32();
    uint8_t index = (seed * 17 + timer_read()) % NUM_COLORS;
    game_state.color_r = rainbow_colors[index].r;
    game_state.color_g = rainbow_colors[index].g;
    game_state.color_b = rainbow_colors[index].b;
}

// Pick a new target and set timer (1-2 seconds randomly)
static void pick_new_target(void) {
    game_state.active_key = select_random_key();
    select_random_color();

    // Random duration between 1000ms and 2000ms
    uint32_t seed = timer_read32();
    uint16_t duration = 1000 + ((seed * 7 + timer_read()) % 1001);
    game_state.next_change_time = timer_read32() + duration;
}

void whack_a_mole_init(void) {
    game_state.is_active = true;
    game_state.hit_key = KC_NO;
    game_state.hit_end_time = 0;
    pick_new_target();
}

void whack_a_mole_task(void) {
    if (!game_state.is_active) {
        return;
    }

    // Check if time expired
    if (timer_expired32(timer_read32(), game_state.next_change_time)) {
        pick_new_target();
    }
}

bool whack_a_mole_process_key(uint16_t keycode, keyrecord_t *record) {
    if (!game_state.is_active || !record->event.pressed) {
        return false;
    }

    // Check if this is a valid game key
    bool is_valid_key = false;
    for (uint8_t i = 0; i < NUM_VALID_KEYS; i++) {
        if (keycode == valid_keys[i]) {
            is_valid_key = true;
            break;
        }
    }

    if (!is_valid_key) {
        return false; // Not a game key, don't consume it
    }

    // Check if they hit the active mole
    if (keycode == game_state.active_key) {
        // Hit! Trigger celebration ripple effect (500ms)
        game_state.hit_key = keycode;
        game_state.hit_row = record->event.key.row;
        game_state.hit_col = record->event.key.col;
        game_state.hit_start_time = timer_read32();
        game_state.hit_end_time = timer_read32() + 500;
        pick_new_target();
    }
    // else: wrong key, no penalty, just ignore it

    return true; // Consume all game key presses to prevent typing
}

uint16_t whack_a_mole_get_active_key(void) {
    return game_state.active_key;
}

void whack_a_mole_get_active_color(uint8_t *r, uint8_t *g, uint8_t *b) {
    *r = game_state.color_r;
    *g = game_state.color_g;
    *b = game_state.color_b;
}

bool whack_a_mole_is_active(void) {
    return game_state.is_active;
}

bool whack_a_mole_celebration_active(void) {
    if (game_state.hit_key == KC_NO) {
        return false;
    }
    if (timer_expired32(timer_read32(), game_state.hit_end_time)) {
        game_state.hit_key = KC_NO;
        return false;
    }
    return true;
}

uint16_t whack_a_mole_get_celebration_key(void) {
    return game_state.hit_key;
}

void whack_a_mole_get_celebration_color(uint8_t row, uint8_t col, uint8_t *r, uint8_t *g, uint8_t *b) {
    // Calculate elapsed time (0-500ms)
    uint32_t elapsed = timer_read32() - game_state.hit_start_time;

    // Calculate distance from hit position (Manhattan distance)
    int8_t row_diff = (int8_t)row - (int8_t)game_state.hit_row;
    int8_t col_diff = (int8_t)col - (int8_t)game_state.hit_col;
    uint8_t distance = (row_diff < 0 ? -row_diff : row_diff) + (col_diff < 0 ? -col_diff : col_diff);

    // Ripple expands at 8 keys per 500ms (roughly 4 keys at 250ms)
    // Current ripple radius based on time (0-8 over 500ms)
    uint16_t ripple_radius = (elapsed * 8) / 500;

    // Check if this key is within the current ripple (with some thickness)
    if (distance > ripple_radius + 2) {
        // Beyond the ripple - no color
        *r = *g = *b = 0;
        return;
    }

    if (distance < ripple_radius - 1) {
        // Behind the ripple - faded out
        *r = *g = *b = 0;
        return;
    }

    // This key is in the ripple! Calculate rainbow color based on distance
    // Hue cycles through rainbow based on distance (0-255)
    uint8_t hue = (distance * 32) % 255;

    // Brightness fades as ripple expands
    uint8_t brightness = 255 - ((elapsed * 255) / 500);

    // Use QMK's built-in HSV to RGB conversion
    HSV hsv = {hue, 255, brightness};
    RGB rgb = hsv_to_rgb(hsv);
    *r = rgb.r;
    *g = rgb.g;
    *b = rgb.b;
}
