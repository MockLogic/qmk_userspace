# Copyright 2025 MockLogic (@mocklogic)
# SPDX-License-Identifier: GPL-2.0-or-later

# Core Features
LEADER_ENABLE = yes
TAP_DANCE_ENABLE = yes
MOUSEKEY_ENABLE = yes
EXTRAKEY_ENABLE = yes

# Mouse Jiggler Support
POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = custom

# Autocorrect with custom dictionary
AUTOCORRECT_ENABLE = yes
AUTOCORRECT_DATA = $(USER_PATH)/autocorrect_data.txt

# Custom feature files
SRC += $(USER_PATH)/features/select_word.c
SRC += $(USER_PATH)/features/rgb_presets.c
SRC += $(USER_PATH)/features/whack_a_mole.c
SRC += $(USER_PATH)/mocklogic.c

# RGB Matrix Features
# RGB_MATRIX_KEYPRESSES = yes  # Disabled - using custom whack-a-mole feedback instead
