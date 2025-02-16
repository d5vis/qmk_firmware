#include QMK_KEYBOARD_H

enum carina_keycodes {
    OW,
    U_T_AUTO = SAFE_RANGE,
    U_T_AGCR,           //USB Toggle Automatic GCR control
    DBG_TOG,            //DEBUG Toggle On / Off
    DBG_MTRX,           //DEBUG Toggle Matrix Prints
    DBG_KBD,            //DEBUG Toggle Keyboard Prints
    DBG_MOU,            //DEBUG Toggle Mouse Prints
    DBG_FAC,            //DEBUG Factory light testing (All on white)
    MD_BOOT             //Restart into bootloader after hold timeout
};

#define TG_NKRO MAGIC_TOGGLE_NKRO //Toggle 6KRO / NKRO mode

keymap_config_t keymap_config;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, \
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, \
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  \
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                   KC_RSFT, \
        KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                                      KC_GRV, KC_MENU, KC_RCTRL, MO(1) \
    ),
    [1] = LAYOUT(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  \
        _______, RGB_SPD, RGB_VAI, RGB_SPI, RGB_HUI, RGB_SAI, _______, KC_PSCR, KC_SLCK, KC_PAUS, _______,   _______, _______, U_T_AGCR,\
        _______, RGB_RMOD,RGB_VAD, RGB_MOD, RGB_HUD, RGB_SAD, _______, KC_INS,  KC_HOME, KC_PGUP, _______,   _______,         KC_AUDIO_VOL_UP, \
        _______, RGB_TOG,  _______, _______, _______, MD_BOOT, TG_NKRO, KC_DEL,  KC_END,  KC_PGDN,   KC_UP,                   KC_AUDIO_VOL_DOWN, \
        OW, _______, _______,                   DBG_FAC,                                    KC_LEFT, KC_DOWN, KC_RIGHT,  _______ \
    ),
    /*
    [X] = LAYOUT(
        _______  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______, \
        _______, _______, _______,                   _______,                            _______, _______, _______,          _______  \
    ),
    */
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
    rgb_matrix_mode(RGB_MATRIX_CUSTOM_gradient_vert_reactive);
};

#define MODS_SHIFT (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT))
#define MODS_CTRL (get_mods() & MOD_BIT(KC_LCTL) || get_mods() & MOD_BIT(KC_RCTRL))
#define MODS_ALT (get_mods() & MOD_BIT(KC_LALT) || get_mods() & MOD_BIT(KC_RALT))

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint32_t key_timer;

    switch (keycode) {
        case U_T_AGCR:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_gcr_auto, "USB GCR auto mode");
            }
            return false;
        case DBG_FAC:
            // if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
            //     led_lighting_mode = LED_MODE_NORMAL;
            //     led_edge_brightness = 1;
            //     led_edge_mode = LED_EDGE_MODE_ALL;
            //     led_animation_breathing = 0;
            //     led_animation_id = 7; //led_programs.c led_setups leds_white index
            //     gcr_desired = LED_GCR_MAX;
            //     I2C3733_Control_Set(1);
            // }
            return false;
        case DBG_TOG:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_enable, "Debug mode");
            }
            return false;
        case DBG_MTRX:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_matrix, "Debug matrix");
            }
            return false;
        case DBG_KBD:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_keyboard, "Debug keyboard");
            }
            return false;
        case DBG_MOU:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_mouse, "Debug mouse");
            }
            return false;
        case MD_BOOT:
            if (record->event.pressed) {
                key_timer = timer_read32();
            } else {
                if (timer_elapsed32(key_timer) >= BOOTKEY_HOLD_MS) {
                    reset_keyboard();
                }
            }
            return false;
        case RGB_TOG:
            if (record->event.pressed) {
              switch (rgb_matrix_get_flags()) {
                case LED_FLAG_ALL: {
                    rgb_matrix_set_flags(LED_FLAG_KEYLIGHT);
                    rgb_matrix_set_color_all(0, 0, 0);
                  }
                  break;
                case LED_FLAG_KEYLIGHT: {
                    rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
                    rgb_matrix_set_color_all(0, 0, 0);
                  }
                  break;
                case LED_FLAG_UNDERGLOW: {
                    rgb_matrix_set_flags(LED_FLAG_NONE);
                    rgb_matrix_disable_noeeprom();
                  }
                  break;
                default: {
                    rgb_matrix_set_flags(LED_FLAG_ALL);
                    rgb_matrix_enable_noeeprom();
                  }
                  break;
              }
            }
            return false;

        case OW:
            if(record->event.pressed) {
                rgb_matrix_mode(RGB_MATRIX_CUSTOM_gradient_vert_reactive);
            }
        default:
            return true; //Process all other keycodes normally
    }
}