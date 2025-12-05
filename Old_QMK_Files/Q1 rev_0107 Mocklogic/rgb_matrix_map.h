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

#ifdef RGB_MATRIX_ENABLE
// Custom GMMK Pro-specific RGB color customizations (defaults found in quantum/color.h)
#define RGB_GODSPEED 0x00, 0xE4, 0xFF     // color for matching keycaps
#define RGB_NAUTILUS 0x00, 0xA4, 0xA9     // Nautilus Font colors
#define RGB_OFFBLUE 0x00, 0x80, 0xFF      // new color: blue with a hint of green
#define RGB_DKRED 0x28, 0x00, 0x00        // new color: dark red
#define RGB_ORANGE2 0xFF, 0x28, 0x00      // fix: reduced green from 80 to 28
#define RGB_PURPLE2 0x80, 0x00, 0xFF      // fix: increased red from 7A to 80
#define RGB_SPRINGGREEN2 0x00, 0xFF, 0x10 // fix: blue was 80, now 10
#define RGB_YELLOW2 0xFF, 0xB0, 0x00      // fix: green was FF, now B0
#define RGB_OFF RGB_BLACK

enum led_location_map {
	LED_ESC,
	LED_F1,
	LED_F2,
	LED_F3,
	LED_F4,
	LED_F5,
	LED_F6,
	LED_F7,
	LED_F8,
	LED_F9,
	LED_F10,
	LED_F11,
	LED_F12,
	LED_DEL,
	LED_KNOB_OFF,
	LED_GRV,
	LED_1,
	LED_2,
	LED_3,
	LED_4,
	LED_5,
	LED_6,
	LED_7,
	LED_8,
	LED_9,
	LED_0,
	LED_MINS,
	LED_EQL,
	LED_BSPC,
	LED_HOME,
	LED_TAB,
	LED_Q,
	LED_W,
	LED_E,
	LED_R,
	LED_T,
	LED_Y,
	LED_U,
	LED_I,
	LED_O,
	LED_P,
	LED_LBRC,
	LED_RBRC,
	LED_BSLS,
	LED_PGUP,
	LED_CAPS,
	LED_A,
	LED_S,
	LED_D,
	LED_F,
	LED_G,
	LED_H,
	LED_J,
	LED_K,
	LED_L,
	LED_SCLN,
	LED_QUOT,
	LED_ENT,
	LED_PGDN,
	LED_LSFT,
	LED_Z,
	LED_X,
	LED_C,
	LED_V,
	LED_B,
	LED_N,
	LED_M,
	LED_COMM,
	LED_DOT,
	LED_SLSH,
	LED_RSFT,
	LED_UP,
	LED_LCTL,
	LED_LWIN,
	LED_LALT,
	LED_SPC,
	LED_RALT,
	LED_FN,
	LED_LEAD,
	LED_LEFT,
	LED_DOWN,
	LED_RIGHT,
};

const uint8_t LED_LIST_WASD[] = {
    LED_W,
    LED_A,
    LED_S,
    LED_D
};

const uint8_t LED_LIST_ARROWS[] = {
    LED_LEFT,
    LED_RIGHT,
    LED_UP,
    LED_DOWN
};

const uint8_t LED_LIST_FUNCROW[] = {
    LED_ESC,
    LED_F1,
    LED_F2,
    LED_F3,
    LED_F4,
    LED_F5,
    LED_F6,
    LED_F7,
    LED_F8,
    LED_F9,
    LED_F10,
    LED_F11,
    LED_F12,
    LED_DEL
};

const uint8_t LED_LIST_NUMROW[] = {
    LED_GRV,
    LED_1,
    LED_2,
    LED_3,
    LED_4,
    LED_5,
    LED_6,
    LED_7,
    LED_8,
    LED_9,
    LED_0,
    LED_MINS,
    LED_EQL,
    LED_BSPC
};

const uint8_t LED_LIST_LETTERS[] = {
    LED_1,
    LED_2,
    LED_3,
    LED_4,
    LED_5,
    LED_6,
    LED_7,
    LED_8,
    LED_9,
    LED_0,
    LED_Q,
    LED_W,
    LED_E,
    LED_R,
    LED_T,
    LED_Y,
    LED_U,
    LED_I,
    LED_O,
    LED_P,
    LED_A,
    LED_S,
    LED_D,
    LED_F,
    LED_G,
    LED_H,
    LED_J,
    LED_K,
    LED_L,
    LED_Z,
    LED_X,
    LED_C,
    LED_V,
    LED_B,
    LED_N,
    LED_M
};

const uint8_t LED_LIST_NUMPAD[] = {
    LED_1,
    LED_2,
    LED_3,
    LED_4,
    LED_5,
    LED_6,
    LED_7,
    LED_8,
    LED_9,
    LED_0,
    LED_MINS,
    LED_EQL,
    LED_U,
    LED_I,
    LED_O,
    LED_P,
    LED_J,
    LED_K,
    LED_L,
    LED_SCLN,
    LED_ENT,
    LED_M,
    LED_COMM,
    LED_DOT,
    LED_SLSH,
    LED_RIGHT
};

#endif