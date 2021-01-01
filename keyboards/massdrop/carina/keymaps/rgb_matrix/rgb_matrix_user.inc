#include "rgb_matrix_user.h"

RGB_MATRIX_EFFECT(dim_border_reactive)
RGB_MATRIX_EFFECT(dim_border_white_reactive)
RGB_MATRIX_EFFECT(triad_reactive)
RGB_MATRIX_EFFECT(triad_reverse_reactive)
RGB_MATRIX_EFFECT(triad_fade_reactive)
RGB_MATRIX_EFFECT(triad_fade_rev_reactive)
RGB_MATRIX_EFFECT(gradient_vert_reactive)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static bool dim_border_reactive(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    effect_runner_reactive_top_only(params, &CUSTOM_SOLID_REACTIVE);

    // bottom LEDS
    HSV hsv = rgb_matrix_config.hsv;
    RGB rgb = hsv_to_rgb(hsv);
    for (uint8_t i = 61; i < 87; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }

    return led_max < DRIVER_LED_TOTAL;
}

static bool dim_border_white_reactive(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    effect_runner_reactive_top_only(params, &CUSTOM_ENERGY_REACTIVE);

    // bottom LEDS
    HSV hsv = rgb_matrix_config.hsv;
    RGB rgb = hsv_to_rgb(hsv);
    for (uint8_t i = 61; i < 87; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
   
    return led_max < DRIVER_LED_TOTAL;
}

static bool triad_reactive(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    effect_runner_reactive_top_only(params, &CUSTOM_TRIADIC_REACTIVE);

    // bottom LEDS
    HSV hsv = rgb_matrix_config.hsv;
    RGB rgb = hsv_to_rgb(hsv);
    for (uint8_t i = 61; i < 87; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
   
    return led_max < DRIVER_LED_TOTAL;
}

static bool triad_reverse_reactive(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    effect_runner_reactive_top_only(params, &CUSTOM_TRIADIC_REV_REACTIVE);

    // bottom LEDS
    HSV hsv = rgb_matrix_config.hsv;
    RGB rgb = hsv_to_rgb(hsv);
    for (uint8_t i = 61; i < 87; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
   
    return led_max < DRIVER_LED_TOTAL;
}

static bool triad_fade_reactive(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    effect_runner_reactive_top_only(params, &CUSTOM_TRIADIC_FADE_REACTIVE);

    // bottom LEDS
    HSV hsv = rgb_matrix_config.hsv;
    RGB rgb = hsv_to_rgb(hsv);
    for (uint8_t i = 61; i < 87; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
   
    return led_max < DRIVER_LED_TOTAL;
}

static bool triad_fade_rev_reactive(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    effect_runner_reactive_top_only(params, &CUSTOM_TRIADIC_FADE_REV_REACTIVE);

    // bottom LEDS
    HSV hsv = rgb_matrix_config.hsv;
    RGB rgb = hsv_to_rgb(hsv);
    for (uint8_t i = 61; i < 87; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
   
    return led_max < DRIVER_LED_TOTAL;
}

static bool gradient_vert_reactive (effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    HSV     hsv   = rgb_matrix_config.hsv;
    uint8_t scale = scale8(64, rgb_matrix_config.speed);
    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        // The y range will be 0..64, map this to 0..4
        // Relies on hue being 8-bit and wrapping
        hsv.h   = rgb_matrix_config.hsv.h + scale * (g_led_config.point[i].y >> 4);
        RGB rgb = hsv_to_rgb(hsv);
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }

    effect_runner_reactive_top_only(params, &CUSTOM_SOLID_WHITE_REACTIVE);

    return led_max < DRIVER_LED_TOTAL;
}


#endif
