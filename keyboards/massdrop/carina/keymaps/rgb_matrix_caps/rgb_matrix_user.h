#ifdef RGB_MATRIX_KEYREACTIVE_ENABLED
  #ifndef DISABLE_RGB_MATRIX_SOLID_REACTIVE
    #ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static HSV CUSTOM_REACTIVE(HSV hsv, uint16_t offset) {
    hsv.s = 0;
    uint8_t valoff = 60;
    uint8_t val = scale8(255 - offset, hsv.v) + valoff;
    hsv.v = val> 255 ? 255 : val;
    return hsv;
}


static HSV CUSTOM_SOLID_REACTIVE(HSV hsv, uint16_t offset) {
    hsv.v = scale8(255 - offset, hsv.v);
    return hsv;
}

static HSV CUSTOM_SOLID_WHITE_REACTIVE(HSV hsv, uint16_t offset) {
    hsv.s = 0;
    hsv.v = scale8(255 - offset, hsv.v);
    return hsv;
}

static HSV CUSTOM_ENERGY_REACTIVE(HSV hsv, uint16_t offset) {
    uint8_t satOffset = offset + 130 > 255 ? 255 : offset + 130;
    hsv.s = scale8(satOffset, hsv.s);
    hsv.v = scale8(255 - offset, hsv.v);
    return hsv;
}

static HSV CUSTOM_TRIADIC_REACTIVE(HSV hsv, uint16_t offset) {
    hsv.v = scale8(255 - offset, hsv.v);
    HSV newHsv;
    newHsv.s = hsv.s;
    newHsv.v = hsv.v;
    newHsv.h = hsv.h + 170 > 255 ? hsv.h + 170 - 255 : hsv.h + 170;
    return newHsv;
}

static HSV CUSTOM_TRIADIC_REV_REACTIVE(HSV hsv, uint16_t offset) {
    hsv.v = scale8(255 - offset, hsv.v);
    HSV newHsv;
    newHsv.s = hsv.s;
    newHsv.v = hsv.v;
    newHsv.h = hsv.h + 85 > 255 ? hsv.h + 85 - 255 : hsv.h + 85;
    return newHsv;
}

static HSV CUSTOM_TRIADIC_FADE_REACTIVE(HSV hsv, uint16_t offset) {
    uint8_t satOffset = offset;
    hsv.s = scale8(satOffset, hsv.s);
    HSV newHsv;
    newHsv.s = hsv.s;
    newHsv.v = hsv.v;
    newHsv.h = hsv.h + 170 > 255 ? hsv.h + 170 - 255 : hsv.h + 170;
    return newHsv;
}

static HSV CUSTOM_TRIADIC_FADE_REV_REACTIVE(HSV hsv, uint16_t offset) {
    uint8_t satOffset = offset;
    hsv.s = scale8(satOffset, hsv.s);
    HSV newHsv;
    newHsv.s = hsv.s;
    newHsv.v = hsv.v;
    newHsv.h = hsv.h + 85 > 255 ? hsv.h + 85 - 255 : hsv.h + 85;
    return newHsv;
}

static bool effect_runner_reactive_top_only (effect_params_t* params, reactive_f effect_func) {
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
        RGB      rgb    = hsv_to_rgb(effect_func(rgb_matrix_config.hsv, offset));
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }

    return led_max < DRIVER_LED_TOTAL;
}

    #endif
  #endif
#endif