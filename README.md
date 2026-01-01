# MockLogic's QMK Userspace

This repository contains my custom QMK firmware configurations for multiple keyboards, using QMK's external userspace system. This approach allows me to maintain shared functionality across keyboards while keeping keyboard-specific code minimal.

**Repository:** https://github.com/MockLogic/qmk_userspace

## Configured Keyboards

- ✅ **Keychron Q3** (TKL, primary development keyboard, physical OS switch)
- ✅ **Keychron Q1v2** (75% compact, physical OS switch)
- ✅ **GMMK Pro** (75% compact, automatic OS detection)
- 🎮 **ZSA Moonlander** (split ergonomic, separate gaming config)

## Key Features

This userspace implements a comprehensive set of features designed for productivity and accessibility:

- **Autocorrect** - Keyboard-level spell checking with custom dictionary (primary feature for dyslexia assistance)
- **OS Detection** - Automatic OS detection for GMMK Pro (Keychrons use physical switch)
- **RGB Presets** - 4 RGB presets including warm white correction for Keychron blue LED tint
- **RGB Config Layer** - Live RGB customization with EEPROM persistence
- **Leader Key Sequences** - Text-based commands for layer access and missing keys (END, INS, PRINT)
- **Gaming Layer** - Disables Windows key, highlights WASD, gaming RGB effects
- **Mouse Control** - Full mouse control via keyboard (emergency fallback)
- **Mouse Jiggler** - Prevents screen timeout for remote work
- **Whack-a-Mole Game** - Interactive RGB game for toddler entertainment (COVID legacy)
- **Word Selection** - OS-aware smart word selection (SELWORD)
- **Dual-Layer FN Keys** - FN_MAC/FN_WIN activate both OS-specific and common feature layers
- **EEPROM Persistence** - Settings saved across power cycles

## Quick Start

### Initial Setup

1. Clone the QMK firmware repository (if not already done):
   ```bash
   qmk setup
   ```

2. Clone this userspace repository:
   ```bash
   git clone https://github.com/MockLogic/qmk_userspace.git
   cd qmk_userspace
   ```

3. Configure QMK to use this userspace:
   ```bash
   qmk config user.overlay_dir="$(realpath .)"
   ```

### Building Firmware

Build for specific keyboard:
```bash
# Keychron Q3
qmk compile -kb keychron/q3/ansi_encoder -km mocklogic

# Keychron Q1v2
qmk compile -kb keychron/q1v2/ansi_encoder -km mocklogic

# GMMK Pro
qmk compile -kb gmmk/pro/rev1/ansi -km mocklogic
```

Flash firmware:
```bash
qmk flash -kb keychron/q3/ansi_encoder -km mocklogic
```

Or use QMK Toolbox to flash the compiled `.bin` file.

## Architecture

### Userspace Structure

```
users/mocklogic/
├── mocklogic.h              # Layer definitions, keycode enums, declarations
├── mocklogic.c              # Main userspace implementation
├── rules.mk                 # Shared build configuration
├── autocorrect_data.txt     # Custom autocorrect dictionary
├── README.md                # Architecture documentation
└── features/                # Modular feature implementations
    ├── select_word.h/c      # Smart word selection
    ├── rgb_presets.h/c      # RGB preset system
    └── whack_a_mole.h/c     # Kid mode game

keyboards/.../keymaps/mocklogic/
├── keymap.c                 # Physical layout ONLY (per-keyboard)
└── rules.mk                 # Keyboard-specific flags (if needed)
```

### Design Philosophy

**Keep keyboard-specific files minimal.** The goal is to have all logic in `users/mocklogic/` so that:

1. **Features are portable** - RGB indicators, layer logic, custom keycodes work across all keyboards
2. **Maintenance is simple** - Fix a bug once, it's fixed everywhere
3. **New keyboards are easy** - Just define the physical layout, everything else works automatically

**What goes in userspace:**
- ✅ All custom keycodes and implementations
- ✅ All layer logic and definitions
- ✅ RGB indicators (using portable `set_led_color_for_keycode()`)
- ✅ Leader key sequences
- ✅ Feature implementations (autocorrect, mouse jiggler, RGB presets, etc.)
- ✅ EEPROM configuration management

**What goes in keyboard-specific files:**
- ❗ Physical key layouts only
- ❗ Tap dance arrays (QMK requirement)
- ❗ Encoder maps (if different per keyboard)

## Layer System

All keyboards use a consistent 10-layer structure:

1. **MAC_BASE** (Layer 0) - Mac base layer (physical OS switch)
2. **MAC_FN** (Layer 1) - Mac function layer
3. **WIN_BASE** (Layer 2) - Windows base layer (physical OS switch)
4. **WIN_FN** (Layer 3) - Windows function layer
5. **FEATURES** (Layer 4) - Feature control layer
6. **GAMING** (Layer 5) - Gaming mode
7. **MOUSE** (Layer 6) - Mouse control
8. **KIDDO** (Layer 7) - Kid mode with whack-a-mole
9. **RGB_CFG** (Layer 8) - RGB configuration
10. **LEADER** (Layer 9) - Leader key active indicator

> **Note:** Layers 0-3 must remain in this order for Keychron physical OS switch compatibility.

### OS Detection (GMMK Pro)

The GMMK Pro lacks a physical OS toggle switch, so it uses QMK's OS detection feature to automatically detect the connected operating system:

- **macOS/iOS detected** → Switches to MAC_BASE layer (layer 0)
- **Windows/Linux/Unknown** → Defaults to WIN_BASE layer (layer 2)

OS detection occurs during keyboard initialization (when plugged in or restarted). If you switch between operating systems, simply replug the keyboard or restart it to re-detect the OS.

The Keychron keyboards continue to use their physical OS toggle switch and do not use OS detection.

## Leader Key Sequences

Access special layers and missing keys via Leader sequences:

| Sequence | Function |
|----------|----------|
| Leader + `GAME` | Enter gaming layer (exit: double-tap ESC) |
| Leader + `MOUSE` | Enter mouse layer (exit: double-tap ESC) |
| Leader + `KIDDO` | Enter kid mode (exit: double-tap ESC) |
| Leader + `RGB` | Enter RGB config layer (exit/save: double-tap ESC) |
| Leader + `END` | Send End key (for 75% keyboards) |
| Leader + `INS` | Send Insert key (for 75% keyboards) |
| Leader + `PRINT` | Send Print Screen key (for 75% keyboards) |

## RGB Presets

- **F5:** No backlighting (LEDs off)
- **F6:** Dim warm white (hue=15, sat=40, val=60)
- **F7:** Bright warm white (hue=15, sat=40, val=200)
- **F8:** Customizable preset (default: Typing Heatmap, configure via RGB Config Layer)

> **Note:** Warm white settings (hue=15, sat=40) compensate for blue tint in Keychron RGB LEDs.

## Customizing for Your Own Use

If you want to fork this repository for your own keyboards:

1. Fork this repository on GitHub
2. Clone your fork locally
3. Update `users/mocklogic/` with your custom features
4. Create keyboard-specific directories for your keyboards in `keyboards/`
5. Update build targets in `qmk.json` (or use `qmk userspace-add`)
6. Commit and push your changes

### Autocorrect Dictionary

Edit `users/mocklogic/autocorrect_data.txt` to add your own common typos. Format:
```
typo -> correction
teh -> the
```

Then rebuild and flash.

## Building with GitHub Actions

1. Enable workflows in the GitHub Actions tab
2. Push changes to your fork
3. Wait for the build to complete
4. Download compiled firmware from the Releases tab

To use a different QMK branch or fork, edit `.github/workflows/build_binaries.yml`:
```yaml
with:
  qmk_repo: qmk/qmk_firmware
  qmk_ref: master
```

## Documentation

- [users/mocklogic/README.md](users/mocklogic/README.md) - Userspace architecture documentation
- [QMK External Userspace Docs](https://docs.qmk.fm/#/newbs_external_userspace) - Official QMK documentation

## Resources

- [QMK Firmware Repository](https://github.com/qmk/qmk_firmware)
- [QMK Documentation](https://docs.qmk.fm/)
- [My QMK Tricks Reddit Post](https://www.reddit.com/r/olkb/comments/t4imri/qmk_tricks/) - Collection of advanced QMK features and tricks

## License

GPL-2.0-or-later (following QMK Firmware licensing)

## Technical Highlights

What makes this setup special:

1. **Portable RGB System** - `set_led_color_for_keycode()` works across different LED matrices
2. **OS-Aware Features** - Automatic Mac/Windows adaptation (e.g., SELWORD)
3. **Dual-Layer FN Keys** - FN_MAC/FN_WIN activate OS-specific + common layers simultaneously
4. **Minimal Per-Keyboard Code** - <100 lines per keyboard, all logic in userspace
5. **Live RGB Customization** - RGB Config layer with EEPROM persistence
6. **Comprehensive EEPROM** - Settings persist across power cycles
7. **Leader-Based UX** - Text sequences easier to remember than key combos
