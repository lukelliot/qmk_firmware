#include "66.h"

// Fill-ins for readability
#define _______ KC_TRNS
#define xxxxxxx KC_NO




enum kropotkin_kc
{
  KR_LCTL = SAFE_RANGE,
  KR_LALT,
};


static uint16_t kr_ctl_timer[1] = {0};
static uint16_t kr_alt_timer[1] = {0};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
    case KR_LCTL:
      if (record->event.pressed) {
        kr_ctl_timer[0] = timer_read ();
        register_mods(MOD_BIT(KC_LCTL));
      }
      else {
        if (timer_elapsed(kr_ctl_timer[0]) < TAPPING_TERM) {
          clear_mods();
          register_code(KC_LSFT);
          register_code(KC_MINS);
          unregister_code(KC_MINS);
          unregister_code(KC_LSFT);
          clear_mods();
        }
        unregister_mods(MOD_BIT(KC_LCTL));
      }
      return false;
    case KR_LALT:
      if (record->event.pressed) {
        kr_alt_timer[0] = timer_read ();
        register_mods(MOD_BIT(KC_LALT));
      }
      else {
        if (timer_elapsed(kr_alt_timer[0]) < TAPPING_TERM) {
          clear_mods();
          register_code(KC_LSFT);
          register_code(KC_LBRC);
          unregister_code(KC_LBRC);
          unregister_code(KC_LSFT);
          clear_mods();
        }
        unregister_mods(MOD_BIT(KC_LALT));
      }
      return false;
  }
  return true;
}

// Foundation
#define _BL 0
// Dvorak
#define _DV 1
// Lower Macro
#define _LM 2
// Upper Macro
#define _UM 3
// Normalize for normies
#define _NR 4
// Function Layer
#define _FL 5
// Color Config
#define _CL 6

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BL: Base Layer (Default Layer)
   */
[_BL] = KEYMAP(
  KC_GESC,KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL, KC_GRV, KC_BSLS,        TG(_CL), \
  KC_TAB ,KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,KC_RBRC,KC_BSPC,                KC_DEL , \
  KR_LCTL,KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,KC_NO  ,KC_ENT ,                         \
  KR_LALT,KC_LSPO,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_NO  ,KC_RSPC,        KC_UP,           \
  KC_RCTL,KC_LALT,KC_LGUI,KC_MHEN,        KC_SPC, KC_SPC,                         KC_HENK,KC_RGUI,KC_RALT,MO(_FL),KC_LEFT,KC_DOWN,KC_RGHT),

  /*Keymap _DV: Dvorak
  */
[_DV] = KEYMAP(
  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,KC_LBRC,KC_RBRC,_______,_______,        _______, \
  _______,KC_QUOT,KC_COMM,KC_DOT ,KC_P   ,KC_Y   ,KC_F   ,KC_G   ,KC_C   ,KC_R   ,KC_L   ,KC_SLSH,KC_EQL ,_______,                _______, \
  _______,KC_A   ,KC_O   ,KC_E   ,KC_U   ,KC_I   ,KC_D   ,KC_H   ,KC_T   ,KC_N   ,KC_S   ,KC_MINS,_______,_______,                         \
  _______,_______,KC_SCLN,KC_Q   ,KC_J   ,KC_K   ,KC_X   ,KC_B   ,KC_M   ,KC_W   ,KC_V   ,KC_Z   ,_______,_______,        _______,         \
  _______,_______,_______,_______,        _______,   _______,                     _______,_______,_______,_______,_______,_______,_______),


  /* Keymap _NR: Normalize
   */
[_NR] = KEYMAP(
  KC_GRV ,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,KC_BSPC,KC_BSPC,        _______, \
  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,KC_BSLS,                _______, \
  KC_CAPS,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,                         \
  KC_LSFT,KC_LSFT,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,KC_RSFT,        _______,         \
  KC_LCTL,KC_LALT,_______,_______,        _______,   _______,                     _______,_______,KC_RALT,_______,_______,_______,_______),

   /* Keymap _FL: Function Layer
   */
[_FL] = KEYMAP(
  KC_POWER, KC_F1,  KC_F2,  KC_F3,  KC_F4,xxxxxxx,xxxxxxx,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9, KC_F10, KC_F11, KC_F12,       KC_POWER, \
  xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,KC_MPLY,KC_MRWD,KC_MFFD,KC_MUTE,                KC_SLEP, \
  xxxxxxx,xxxxxxx,xxxxxxx,TG(_DV),xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,                         \
  xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,TG(_NR),xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,        KC_PGUP,         \
  RESET  ,xxxxxxx,xxxxxxx,xxxxxxx,        xxxxxxx,xxxxxxx,                        xxxxxxx,xxxxxxx,xxxxxxx,MO(_FL),KC_HOME,KC_PGDN,KC_END),


  /* Keymap _CL: Color layer
   */
[_CL] = KEYMAP(
  xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,        TG(_CL), \
  xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,                RGB_TOG, \
  xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,                         \
  xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,        RGB_SAI,         \
  xxxxxxx,xxxxxxx,xxxxxxx,xxxxxxx,        RGB_MOD,RGB_MOD,                        xxxxxxx,RGB_VAD,RGB_VAI,BL_TOGG,RGB_HUD,RGB_SAD,RGB_HUI),

};
