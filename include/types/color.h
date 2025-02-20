#pragma once

#include <Arduino.h>

enum colorType {
  single,
  RGB,
  RGBA,
};

typedef struct {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
} rgb_color_t;

typedef struct {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
  // brightness
  uint8_t alpha;
} rgba_color_t;

typedef struct {
  colorType type;
  union colors {
    uint8_t single_col;
    rgb_color_t rgb_col;
    rgba_color_t rgba_col;
  } color;
} color_t;

rgb_color_t hsvToRgb(uint16_t h, uint8_t s, uint8_t v);

color_t convertToRGBA(color_t);
color_t convertToRGB(color_t);
color_t convertToSingle(color_t);
