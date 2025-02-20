#pragma once

#include "constants/colors.h"
#include "types/color.h"

#include <lvgl.h>
#include <PNGdec.h>

#include <functional>
#include <string>

#define default_size 1
#define default_color c_white
#define MAX_IMAGE_WIDTH 240

typedef struct {
  int16_t xpos;
  int16_t ypos;
  lv_obj_t* obj;
} PNG_config_t;

class Component {
protected:
  Component(uint32_t x, uint32_t y, color_t color = default_color);

  uint x;
  uint y;

  rgba_color_t color;

public:
  Component() = delete;

  virtual void draw(lv_obj_t* obj){};
  void setColor(color_t color);
  void setXY(int x, int y);
};

class Line : public Component {
protected:
  uint x2;
  uint y2;

public:
  Line(uint x1, uint y1, uint x2, uint y2, color_t color = default_color);

  void draw(lv_obj_t* obj);
};

class Text : public Component {
protected:
  uint fontsize;

  std::string value;

public:
  Text(uint x, uint y, std::string value, uint8_t size = default_size,
       color_t color = default_color);

  void draw(lv_obj_t* obj);
  void setText(std::string str);
};

class InformationNumber : public Text {
protected:
  uint *val;

public:
  InformationNumber(uint x, uint y, std::string name, uint *value,
                    uint8_t size = default_size, color_t color = default_color);

  void draw(lv_obj_t* obj);
};

class InformationFloat : public Text {
protected:
  float *val;

public:
  InformationFloat(uint x, uint y, std::string name, float *value,
                   uint8_t size = default_size, color_t color = default_color);

  void draw(lv_obj_t* obj);
};

class Image : public Component {
protected:
  const u_char *image;
  long size;

  static PNG_config_t *png_config;
  static PNG png;

public:
  static void pngDraw(PNGDRAW *);

  Image(int x, int y, const u_char *image, uint size);

  void draw(lv_obj_t* obj);
};

class Rectangle : public Component {
protected:
  uint width;
  uint height;

public:
  Rectangle(int x, int y, uint width, uint height,
            color_t color = default_color);
  void draw(lv_obj_t* obj);
};

// TODO: Implement these classes

class Selectable : public Component {
protected:
  bool selectable;

  rgba_color_t selectedColor;

public:
  Selectable(int x, int y, bool select = true, color_t color = default_color);
  virtual void draw(lv_obj_t* obj);
  virtual void activate();

  bool active = false;
};

class ButtonUI : public Selectable {
protected:
  const std::string str;
  std::function<void()> fnt;

  uint width;
  uint height;

public:
  ButtonUI(int x, int y, uint width, uint height, std::function<void()> func,
           const std::string str = "", bool select = true,
           color_t color = default_color, color_t selectCol = c_blue);
  void draw(lv_obj_t* obj);

  void activate();
};

// class ChangeableValue: public Selectable {
//   protected:
//     int max;
//     int min;

//     int val;

//   public:
//     ChangeableValue(int x, int y, int min, int max, int val, bool select =
//     true, color_t color = default_color, color_t selectCol = c_blue); void
//     draw(TFT_eSPI* tft);

//     void activate();
// }

// class ProgressBar : public Rectangle {}
