// Copyright 2025 MockLogic (@mocklogic)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include QMK_KEYBOARD_H

// Initialize the whack-a-mole game
void whack_a_mole_init(void);

// Update game state (called from RGB matrix effect)
void whack_a_mole_task(void);

// Handle keypress events (returns true if key was consumed by game)
bool whack_a_mole_process_key(uint16_t keycode, keyrecord_t *record);

// Get current active key (for RGB display)
uint16_t whack_a_mole_get_active_key(void);

// Get current active color (for RGB display)
void whack_a_mole_get_active_color(uint8_t *r, uint8_t *g, uint8_t *b);

// Check if game is active
bool whack_a_mole_is_active(void);

// Check if celebration effect is active (correct mole was hit)
bool whack_a_mole_celebration_active(void);

// Get key that triggered celebration
uint16_t whack_a_mole_get_celebration_key(void);

// Get current celebration color for a specific key position (rainbow ripple)
void whack_a_mole_get_celebration_color(uint8_t row, uint8_t col, uint8_t *r, uint8_t *g, uint8_t *b);
