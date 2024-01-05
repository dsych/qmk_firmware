/*
Copyright 2020 Richard Goulter

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU general Public License for more details.

You should have received a copy of the GNU General Public LicensezZZ
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "os_detection.h"
#include "print.h"

#ifdef RGBLIGHT_ENABLE
#include "rgblight.h"
#endif

enum layers {
    _QWERTY,
    _WORKMAN,
    _COLEMAK,
    _DVORAK,
    _LOWER,
    _RAISE,
    _ADJUST,
    _FN
};

enum keycodes {
    QWERTY = SAFE_RANGE,
    WORKMAN,
    COLEMAK,
    DVORAK,
    TOGGLE_RGB,
    USR_COPY,
    USR_PASTE,
    USR_CUT,
    USR_FIND
};

#define FN    MO(_FN)
#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define LFT_CTRL CTL_T(KC_ESC)

#define LWR_ESC OSL(_LOWER)
#define RSE_ENT OSL(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Qwerty
     * ,-----------------------------------------------------------------------------------.
     * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |  -   |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  =   |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '   |
     * |------+------+------+------+------+------|------+------+------+------+------+------|
     * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Ent/Sh|
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Ctrl | GUI  | Alt  | Tab  | Esc  | Bksp | Space| Enter|  [   |  ]   |  GUI | Ctrl |
     * `-----------------------------------------------------------------------------------'
     */
    [_QWERTY] = LAYOUT(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_EQL,
        LFT_CTRL,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, SC_SENT,
        XXXXXXX, KC_LCTL, KC_LALT, KC_LGUI, LWR_ESC, KC_BSPC,  KC_SPC, RSE_ENT, KC_LCTL,  KC_TAB, KC_LGUI, XXXXXXX
    ),

    /* Workman
     * ,-----------------------------------------------------------------------------------.
     * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Tab  |   Q  |   D  |   R  |   W  |   B  |   J  |   F  |   U  |   P  |   ;  | Del  |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * | Esc  |   A  |   S  |   H  |   T  |   G  |   Y  |   N  |   E  |   O  |   I  |  '   |
     * |------+------+------+------+------+------|------+------+------+------+------+------|
     * | Shift|   Z  |   X  |   M  |   C  |   V  |   K  |   L  |   ,  |   .  |   /  |Enter |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Num  | Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
     * `-----------------------------------------------------------------------------------'
     */
    [_WORKMAN] = LAYOUT(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
        KC_TAB,  KC_Q,    KC_D,    KC_R,    KC_W,    KC_B,    KC_J,    KC_F,    KC_U,    KC_P,    KC_SCLN, KC_DEL,
        KC_ESC,  KC_A,    KC_S,    KC_H,    KC_T,    KC_G,    KC_Y,    KC_N,    KC_E,    KC_O,    KC_I,    KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_M,    KC_C,    KC_V,    KC_K,    KC_L,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
        KC_LCTL, KC_LGUI, KC_LALT, KC_TAB,  LWR_ESC, KC_SPC,  KC_BSPC, RSE_ENT, KC_DEL,  KC_RALT, KC_RGUI, KC_RCTL
    ),

    /* Colemak
     * ,-----------------------------------------------------------------------------------.
     * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Del  |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * | Esc  |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  '   |
     * |------+------+------+------+------+------|------+------+------+------+------+------|
     * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |Enter |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |  FN  | Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
     * `-----------------------------------------------------------------------------------'
     */
    [_COLEMAK] = LAYOUT(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_DEL,
        KC_ESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
        KC_LCTL, KC_LGUI, KC_LALT, KC_TAB,  LWR_ESC, KC_SPC,  KC_BSPC, RSE_ENT, KC_DEL,  KC_RALT, KC_RGUI, KC_RCTL
    ),

    /* Dvorak
     * ,-----------------------------------------------------------------------------------.
     * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Tab  |   '  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  | Del  |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * | Esc  |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |  /   |
     * |------+------+------+------+------+------|------+------+------+------+------+------|
     * | Shift|   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |Enter |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |  FN  | Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
     * `-----------------------------------------------------------------------------------'
     */
    [_DVORAK] = LAYOUT(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
        KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_DEL,
        KC_ESC,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_SLSH,
        KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_ENT,
        KC_LCTL, KC_LGUI, KC_LALT, KC_TAB,  LWR_ESC, KC_SPC,  KC_BSPC, RSE_ENT, KC_DEL,  KC_RALT, KC_RGUI, KC_RCTL
    ),

    /* Lower
     * ,-----------------------------------------------------------------------------------.
     * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |      |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |  |   |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * | Alt  |      |      |      |      |      | Left | Down | Up   | Rght |  -   |  \   |
     * |------+------+------+------+------+------|------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      | Home | PgDn | PgUp | End  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      | Del  |      |      | Left | Down | Up   | Rght |
     * `-----------------------------------------------------------------------------------'
     */
    [_LOWER] = LAYOUT(
        KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, XXXXXXX,
        KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PIPE,
        KC_LALT, XXXXXXX, XXXXXXX, XXXXXXX, USR_FIND, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, KC_MINS,KC_BSLS,
        _______, XXXXXXX, USR_CUT, USR_COPY, USR_PASTE, XXXXXXX, XXXXXXX, XXXXXXX, KC_LBRC, KC_RBRC, KC_BSLS, _______,
        _______, _______, _______, _______, XXXXXXX, _______, KC_RCTL, XXXXXXX, _______, _______, _______, _______
    ),

    /* Raise
     * ,-----------------------------------------------------------------------------------.
     * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |  \   |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * | Del  |      |MOUS_L|MOUS_U|MOUS_D|MOUS_R|  F6  |   -  |   =  |   [  |   ]  |  /   |
     * |------+------+------+------+------+------|------+------+------+------+------+------|
     * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / |PageUp|PageDn|      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
     * `-----------------------------------------------------------------------------------'
     */
    [_RAISE] = LAYOUT(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    XXXXXXX,
        KC_GRV, KC_BTN1,  KC_MS_U, KC_BTN2, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_SLSH,
        _______, KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX, XXXXXXX, XXXXXXX, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_SLSH,
        KC_KB_MUTE, XXXXXXX, KC_WH_L, KC_WH_U, KC_WH_D, KC_WH_R, XXXXXXX, RGB_VAD, RGB_VAI, RGB_RMOD, RGB_MOD, RGB_TOG,
        KC_MPRV, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY, KC_DEL, _______, XXXXXXX, _______, _______, _______, RGB_TOG
    ),

    /* Adjust (Lower + Raise)
     * ,-----------------------------------------------------------------------------------.
     * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      | Reset|      |      |      |      |      |      |      |      |      |  Del |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * |CPSLCK|      |      |      |      |      |      |Qwerty|Workmn|Colemk|Dvorak|      |
     * |------+------+------+------+------+------|------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |             |      |      |      |      |      |
     * `-----------------------------------------------------------------------------------'
     */
    [_ADJUST] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, QK_BOOT, _______, _______, _______, _______, _______, KC_PSCR, KC_SCRL, KC_PAUS, _______, _______,
        KC_CAPS, _______, _______, _______, _______, _______, _______, QWERTY,  WORKMAN, COLEMAK, DVORAK,  _______,
        _______, _______, _______, _______, _______, _______, _______, RGB_SAI, RGB_TOG, RGB_HUD, RGB_HUI, RGB_MOD,
        _______, _______, _______, _______, XXXXXXX, _______, _______, XXXXXXX, RGB_SPD, RGB_VAD, RGB_VAI, RGB_SPI
    )
};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
};

#define NUM_OS_SUPPORTED 4
#define NUM_KEYCODES_SUPPORTED 4

const uint16_t keycode_to_os_keycode [NUM_OS_SUPPORTED][NUM_KEYCODES_SUPPORTED][2] = {
    [OS_MACOS] = {
        { USR_COPY, LGUI(KC_C) },
        { USR_PASTE, LGUI(KC_V) },
        { USR_CUT, LGUI(KC_X) },
        { USR_FIND, LGUI(KC_F) }
    },
    [OS_LINUX] = {
        { USR_COPY, S(LCTL(KC_C)) },
        { USR_PASTE, S(LCTL(KC_V)) },
        { USR_CUT, S(LCTL(KC_X)) },
        { USR_FIND, S(LCTL(KC_F)) }
    },
    [OS_WINDOWS] = {
        { USR_COPY, LCTL(KC_C) },
        { USR_PASTE, LCTL(KC_V) },
        { USR_CUT, LCTL(KC_X) },
        { USR_FIND, LCTL(KC_F) }
    }
};

void print_os(uint16_t os) {
#ifdef CONSOLE_ENABLED
    switch (os) {
        case OS_WINDOWS:
            print("windows\n");
            break;
        case OS_MACOS:
            print("mac\n");
            break;
        case OS_LINUX:
            print("linux\n");
            break;
    }
#endif
}

void print_keycode(uint16_t keycode) {
#ifdef CONSOLE_ENABLED
    switch (keycode) {
        case USR_COPY:
            print("copy\n");
            break;
        case USR_CUT:
            print("cut\n");
            break;
        case USR_PASTE:
            print("paste\n");
            break;
        case USR_FIND:
            print("find\n");
            break;
    }
#endif
}

void issue_os_specific_keycode(uint16_t keycode) {
    uint16_t detected_os = detected_host_os();
    for (int os = 0; os < NUM_OS_SUPPORTED; os++) {
        if (os == detected_os) {
            print_os(os);
            const uint16_t (*os_specific_keycodes)[2] = keycode_to_os_keycode[os];
            for (int kc = 0; kc < NUM_KEYCODES_SUPPORTED; kc++) {
                if (keycode == os_specific_keycodes[kc][0]) {
                    print_keycode(keycode);
                    tap_code16(os_specific_keycodes[kc][1]);
                }
            }
        }
    }
    return;
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
        case WORKMAN:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_WORKMAN);
            }
            return false;
        case COLEMAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_COLEMAK);
            }
            return false;
        case DVORAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_DVORAK);
            }
            return false;
        case USR_COPY:
        case USR_PASTE:
        case USR_CUT:
        case USR_FIND:
            if (record->event.pressed) {
                issue_os_specific_keycode(keycode);
            }
            return false;
    }
    return true;
};
