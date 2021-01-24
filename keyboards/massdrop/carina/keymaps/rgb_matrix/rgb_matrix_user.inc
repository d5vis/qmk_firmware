#include "rgb_matrix_user.h"

RGB_MATRIX_EFFECT(border_reactive)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static bool border_reactive(effect_params_t* params) {
    // RGB_MATRIX_USE_LIMITS(led_min, led_max);

    // RGB rgb = hsv_to_rgb(rgb_matrix_config.hsv);
    // for (uint8_t i = led_min; i < led_max; i++) {
    //     RGB_MATRIX_TEST_LED_FLAGS();
    //     rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    // }
    // return led_max < DRIVER_LED_TOTAL;

  // return effect_runner_reactive(params, &SOLID_REACTIVE_math);
  // return effect_runner_reactive_splash(qsub8(g_last_hit_tracker.count, 1), params, &SOLID_REACTIVE_NEXUS_math);


    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    uint16_t max_tick = 65535 / rgb_matrix_config.speed;
    for (uint8_t i = 0; i < 61; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        uint16_t tick = max_tick;
        // Reverse search to find most recent key hit
        for (int8_t j = g_last_hit_tracker.count - 1; j >= 0; j--) {
            if (g_last_hit_tracker.index[j] == i && g_last_hit_tracker.tick[j] < tick) {
                tick = g_last_hit_tracker.tick[j];
                break;
            }
        }

        uint16_t offset = scale16by8(tick, rgb_matrix_config.speed);
        RGB      rgb    = hsv_to_rgb(CUSTOM_REACTIVE(rgb_matrix_config.hsv, offset));
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }

    // bottom LEDS
    for (uint8_t i = 61; i < 87; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        rgb_matrix_set_color(i, 40, 25, 74);
    }

    return led_max < DRIVER_LED_TOTAL;
  // return effect_runner_reactive_custom(params, &SOLID_REACTIVE_SIMPLE_math);
}

#endif