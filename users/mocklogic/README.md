# MockLogic QMK Userspace

This userspace contains shared functionality across multiple keyboards:
- **Keychron Q3** (primary development keyboard)
- **Keychron Q1** (unified design)
- **GMMK Pro** (unified design)
- **ZSA Moonlander** (gaming-specific, NOT part of unified design)

## Design Philosophy

**Keep keyboard-specific files minimal.** Only include keyboard-specific code when absolutely necessary:

> **Note:** The unified design applies to the Q3, Q1, and GMMK Pro. The ZSA Moonlander uses a separate gaming-focused configuration.

### What goes in USERSPACE (`users/mocklogic/`):
- ✅ Custom keycodes and their implementations
- ✅ Layer definitions (must be consistent across all keyboards)
- ✅ Feature implementations (autocorrect, mouse jiggler, RGB presets, etc.)
- ✅ `process_record_user()` - all custom keycode handling
- ✅ Leader key sequences
- ✅ RGB indicator logic (using portable keycode-based approach)
- ✅ EEPROM configuration management
- ✅ Any functionality that should work the same across keyboards

### What goes in KEYBOARD-SPECIFIC files (`keyboards/.../keymaps/mocklogic/`):
- ❗ Only keymap layout definitions (the actual key positions)
- ❗ Only tap dance action arrays (must be in keymap.c per QMK requirement)
- ❗ Only encoder maps (if using different encoder behavior per keyboard)
- ❗ **DO NOT** add `process_record_user()` to keyboard files unless you need keyboard-specific overrides (and if you do, make sure to call the userspace version)

## Layer Structure

Layers 0-3 are reserved for Keychron physical OS switch compatibility:
- Layer 0: `_MAC_BASE` - Mac base layer
- Layer 1: `_MAC_FN` - Mac function layer (activated by FN_MAC)
- Layer 2: `_WIN_BASE` - Windows base layer
- Layer 3: `_WIN_FN` - Windows function layer (activated by FN_WIN)

Higher layers (4+):
- Layer 4: `_FEATURES` - Feature control layer
- Layer 5+: Other special layers (Gaming, Mouse, Kiddo, RGB Config, Leader)

## Custom Keycodes

### Dual-Layer Function Keys
- `FN_MAC` - Activates both `_MAC_FN` + `_FEATURES` layers simultaneously
- `FN_WIN` - Activates both `_WIN_FN` + `_FEATURES` layers simultaneously

This allows OS-specific keys (like `TASK_MGR` on Windows) to be placed in the OS-specific FN layer, while common features remain in the `_FEATURES` layer.

### OS-Aware Features
Some features automatically adapt to the current OS mode based on the physical switch position:

- **Select Word (`SELWORD`)** - Uses Mac hotkeys (Option+Shift+Arrow) when in Mac mode (layer 0), and Windows hotkeys (Ctrl+Shift+Arrow) when in Windows mode (layer 2). The implementation checks `default_layer_state` at runtime to determine which hotkeys to use.

### Implementation Pattern
All custom keycode handling is in `users/mocklogic/mocklogic.c` in the `process_record_user()` function. This ensures consistent behavior across all keyboards.

## File Organization

```
users/mocklogic/
├── mocklogic.h          # Layer definitions, keycode enums, function declarations
├── mocklogic.c          # Main userspace implementation
├── rules.mk             # Build configuration
├── README.md            # This file
└── features/            # Modular feature implementations
    ├── select_word.h/c
    ├── rgb_presets.h/c
    └── ...

keyboards/.../keymaps/mocklogic/
├── keymap.c             # ONLY layout definitions, tap dance arrays, encoder maps
└── rules.mk             # Keyboard-specific build flags (if needed)
```

## When Adding New Features

**Always ask yourself:** "Does this need to be keyboard-specific, or should it go in userspace?"

Default to userspace unless there's a compelling reason for it to be keyboard-specific (like physical layout differences and Tapdance having to be there).
