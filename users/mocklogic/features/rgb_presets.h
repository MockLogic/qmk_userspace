// Copyright 2025 MockLogic (@mocklogic)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include QMK_KEYBOARD_H

// RGB preset configuration
void rgb_preset_init(void);
void rgb_preset_apply(uint8_t preset);

// RGB config layer state management
void rgb_config_layer_enter(void);
void rgb_config_layer_exit(void);
void rgb_config_layer_reset(void);
void rgb_config_set_effect(uint8_t mode);
void rgb_config_adjust_hue(int8_t delta);
void rgb_config_adjust_sat(int8_t delta);
void rgb_config_adjust_val(int8_t delta);
void rgb_config_adjust_speed(int8_t delta);
