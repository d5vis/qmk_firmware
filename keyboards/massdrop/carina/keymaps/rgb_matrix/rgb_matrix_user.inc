#include "rgb_matrix_user.h"

RGB_MATRIX_EFFECT(purple_border_reactive)
RGB_MATRIX_EFFECT(dim_border_reactive)
RGB_MATRIX_EFFECT(dim_border_white_reactive)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static bool purple_border_reactive(effect_params_t* params) {
    // bottom LEDS
    for (uint8_t i = 61; i < 87; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        rgb_matrix_set_color(i, 40, 25, 74);
    }

    return effect_runner_reactive_top_only(params, &CUSTOM_REACTIVE);
}

static bool dim_border_reactive(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    effect_runner_reactive_top_only(params, &CUSTOM_SOLID_REACTIVE);

    // bottom LEDS
    HSV hsv = rgb_matrix_config.hsv;
    hsv.v = 130;
    RGB rgb = hsv_to_rgb(hsv);
    for (uint8_t i = 61; i < 87; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }

    return led_max < DRIVER_LED_TOTAL;
}

static bool dim_border_white_reactive(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    effect_runner_reactive_top_only(params, &WHITE_CUSTOM_REACTIVE);

    // bottom LEDS
    HSV hsv = rgb_matrix_config.hsv;
    hsv.v = 130;
    RGB rgb = hsv_to_rgb(hsv);
    for (uint8_t i = 61; i < 87; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
   
    return led_max < DRIVER_LED_TOTAL;
}

#endif