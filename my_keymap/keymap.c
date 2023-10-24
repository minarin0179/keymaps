/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

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

#include QMK_KEYBOARD_H

#include "quantum.h"
#include "a2j/translate_ansi_to_jis.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default
  [0] = LAYOUT_universal(
    KC_TAB    , KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                                        KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     , KC_MINS  ,
    KC_LSFT   , KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                                        KC_H     , KC_J     , KC_K     , KC_L     , KC_SCLN  , KC_COLN  ,
    KC_LCTL   , KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     ,                                        KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  , KC_INT1  ,
              KC_LALT,KC_LGUI,LSFT_T(KC_LNG2)     ,LT(2,KC_SPC),LALT_T(KC_LNG1),                  KC_BSPC ,LT(3,KC_ENT), _______  , _______  , KC_PSCR
  ),


  [1] = LAYOUT_universal(
    _______  , _______  , _______  , _______  , _______  , _______  ,                                        _______  , _______  , _______  , _______ , _______  , _______   ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                                        _______  , KC_BTN1  , SCRL_MO  , KC_BTN2  , KC_BTN4  , KC_BTN5  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                                        _______  , _______  , KC_BTN3  , _______  , _______  , _______  ,
                  _______    , _______  , _______  ,        _______  , _______  ,                   _______  , _______  , _______       , _______  , _______
  ),

  [2] = LAYOUT_universal(
    KC_ESC  ,  KC_EXLM	, KC_DQT   , KC_HASH , KC_DLR   , KC_PERC  ,                                         KC_AMPR  , KC_QUOT  , KC_CIRC  , KC_TILD  ,KC_PIPE  , KC_GRV   ,
    _______  ,  KC_1    , KC_2     , KC_3    , KC_4     , KC_5     ,                                         KC_6     , KC_7     , KC_8     , KC_9     , KC_0    , _______  ,
    KC_F1    ,  KC_F2   , KC_F3    , KC_F4   , KC_F5    , KC_F6    ,                                         KC_F7    , KC_F8    , KC_F9    , KC_F10   , KC_F11  , KC_F12   ,
                  _______  , _______ , _______  ,         _______  , _______  ,                   _______  , _______  , _______       , _______  , _______
  ),

  [3] = LAYOUT_universal(
    RGB_TOG  ,  _______ , KC_7     , KC_8    , KC_9     , KC_LBRC  ,                                         KC_RBRC  , KC_BSPC  , KC_UP      , KC_DEL   , KC_AT    , KC_EQL   ,
    CPI_I100 ,  _______ , KC_4     , KC_5    , KC_6     , KC_LPRN  ,                                         KC_RPRN  , KC_LEFT  , KC_DOWN    , KC_RIGHT , KC_PLUS  , KC_ASTR  ,
    CPI_D100 ,  _______ , KC_1     , KC_2    , KC_3     , KC_LCBR  ,                                         KC_RCBR  , _______  , KC_LABK    , KC_RABK  , KC_QUES  , KC_UNDS  ,
                  KC_0     , KC_DOT  , _______  ,         _______  , _______  ,                   _______  , _______  , _______       , _______  , _______
  ),

};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 2
    keyball_set_scroll_mode(get_highest_layer(state) == 2);
    return state;
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif


void pointing_device_init_user(void) {
    set_auto_mouse_enable(true);         // always required before the auto mouse feature will work
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return process_record_user_a2j(keycode, record);
}