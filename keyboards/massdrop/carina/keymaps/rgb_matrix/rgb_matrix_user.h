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

    #endif
  #endif
#endif
