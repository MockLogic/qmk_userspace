# MockLogic's GMMK Pro Layout

Mostly a QMK Learning project, this keymap includes a lot of featuers. It is intended to be run with RGB compatible keycaps as key highlighting is used in various places.

* Lots of RGB inidcators including a function layer where toggles are blue when the feature is activated and orange when the feature is deactivated
* Dynamic Macro recording (2 slots)
* N-Key Rollover disable/enable toggle for compatibility
* CapsWord feature based on [Pascal Getreuer's work](https://getreuer.info/posts/keyboards/caps-word/index.html).
* Autocorrection with over 400 common errors. also based on [Pascal Getreuer's work](https://getreuer.info/posts/keyboards/autocorrection/index.html).
* An RGB configuration mode with lots of controls.
* A Gaming Mode that disables potentially game disrupting keys like Windows, Capslock, and several other optional features. Has WASD highlighting through RGB.
* [Space Cadet Shift](https://docs.qmk.fm/#/feature_space_cadet).
* A mosue mode where it's possible to use the arrow keys along with Right Control and End, to emulate a mouse. The rest of the keyboard remains active as normal.
* Mouse Jiggler feature to keep a computer away based on [DIYCharles's Project](https://github.com/DIYCharles/MouseJiggler).
* The Encoder Knob is enabled. Most of the time it controls the volume.
* Auto Shift is availble, although disabled by default. There is also a testing layer where the speed can be adjusted.
* A number pad layer.

## Keyboard Layout
The base layout of the keyboard is *nearly* default. I have chosen to put my Delete key between F12 and the Knob, and a Home key directly under the Knob, with the usual Page Up, Page Down, and End keys under that. My function key lives right of the right Alt and the Right Control key has been replaced with a select word/line macro key.

### Select Word / Line
On Windows, pressing the select word key will select the current word regardless where in the word your cursor is. Key tapping the key to select additional words.

Holding shift and hitting the macro will select the current line. Key pressing the key while holding shift to select additional lines.


## Function Controls
Function + F1 or F2 records dynamic macros. Function + Escape ends a recording. Function + 1 or 2 plays them back.

F4 brings up Task Manager in Windows.

F10 Media Previous Song

F11 Media Play/Pause

F12 Medai Next Song

F9 brings up My Computer in Windows.

Delete becomes Insert

Home opens My computer

Page Up cycles thorugh oppen apps

Page Down opens Clipboard History

End hides/displays the desktop (minmizes all/returns them)

The 9 and 0 keys activate Space Cadet Shift, but only for the Shift Keys.

Back Space clears the keyboard memory.

Back slash resets the keyboard, as usual.

W toggles CapsWord feature.

S toggles the Auto Shift feature.

J activates the mouse jiggler feature.

C toggles the auto correction feature.

N Toggles the N-Key Rollover function. This setting is retained in memory.

L Activates a Key Lock. The next key pressed will be virtually held down by the keyboard until it is tapped again.

Right Control turns on the Leader key.

The encoder knob zooms pages in and out, and pressing the knob resets zoom.

## Leader Key options

Activate the Leader key and it should glow blue. Type a command to activate that feature. All commands are lower case.

* rgb - Brings up the RGB control page.
* game - Puts the keyboard in a gaming mode.
* white - sets the backlight to a pale warm white.
* color - set the backlight to a scrolling rainbow.
* num - takes you to a number pad layer.

## RGB Control Mode

Most keys are disabled in this mode.

The F1-F12, and Delete, keys each set the keyboard to a particular color.

Q and W alter the hue (color), as does the encoder knob.

A and S alter the saturation (white vs color).

Z and X alter the vibrancey (how bright).

Up and Down arrows move through different effects.

Left and Right arrows control effect speed.

Pushing the knob down toggles the RGB matrix on/off.

## Auto Shift Configuration Mode

This page is configured to aid in finding the right Auto Shift timing settings, in accordance with the Auto Shift documentation.

Pressing Home will toggle Auto Shift on and off. Page Up and Page Down increase or decreaasae the amount of time a button has to be pressed to register as shifted. End will cauase the keyboard to output the current setting as typed text.