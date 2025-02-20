#include "types/color.h"

// TODO: Rewrite with color_s or smth equivalent
rgb_color_t hsvToRgb(uint16_t h, uint8_t s, uint8_t v)
{
    uint8_t f = (h % 60) * 255 / 60;
    uint8_t p = (255 - s) * (uint16_t)v / 255;
    uint8_t q = (255 - f * (uint16_t)s / 255) * (uint16_t)v / 255;
    uint8_t t = (255 - (255 - f) * (uint16_t)s / 255) * (uint16_t)v / 255;
    uint8_t r = 0, g = 0, b = 0;
    switch ((h / 60) % 6)
    {
    case 0:
        r = v;
        g = t;
        b = p;
        break;
    case 1:
        r = q;
        g = v;
        b = p;
        break;
    case 2:
        r = p;
        g = v;
        b = t;
        break;
    case 3:
        r = p;
        g = q;
        b = v;
        break;
    case 4:
        r = t;
        g = p;
        b = v;
        break;
    case 5:
        r = v;
        g = p;
        b = q;
        break;
    }

    rgb_color_t res = {r, g, b};
    return res;
}

color_t convertToRGBA(color_t c)
{
    color_t ret;
    switch (c.type)
    {
    case single:
    {
        ret = color_t{RGBA, {.rgba_col = {c.color.single_col, c.color.single_col, c.color.single_col, 255}}};
        break;
    };
    case RGB:
    {
        ret = color_t{RGBA, {.rgba_col = {c.color.rgb_col.red, c.color.rgb_col.green, c.color.rgb_col.blue, 255}}};
        break;
    };
    case RGBA:
    {
        ret = c;
        break;
    };
    }

    return ret;
}

color_t convertToRGB(color_t c)
{
    color_t ret;
    switch (c.type)
    {
    case single:
    {
        ret = color_t{RGB, {.rgba_col = {c.color.single_col, c.color.single_col, c.color.single_col}}};
        break;
    };
    case RGB:
    {
        ret = c;
        break;
    };
    case RGBA:
    {
        ret = color_t{RGB, {.rgba_col = {c.color.rgba_col.red, c.color.rgba_col.green, c.color.rgba_col.blue}}};
        break;
    };
    }

    return ret;
}

color_t convertToSingle(color_t c)
{
    color_t ret;
    switch (c.type)
    {
    case single:
    {
        ret = c;
        break;
    };
    case RGB:
    {
        uint8_t avg = static_cast<uint8_t>(static_cast<float>(c.color.rgb_col.red + c.color.rgb_col.green + c.color.rgb_col.blue) / 3.0f);
        ret = color_t{single, {.single_col = avg}};
        break;
    };
    case RGBA:
    {
        uint8_t avg = static_cast<uint8_t>(static_cast<float>(c.color.rgba_col.red + c.color.rgba_col.green + c.color.rgba_col.blue) / 3.0f);
        ret = color_t{single, {.single_col = avg}};
        break;
    };
    }

    return ret;
}