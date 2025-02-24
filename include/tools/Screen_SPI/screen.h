#pragma once

#include "UI.h"

#include <PNGdec.h>
#include <lvgl.h>
#include <vector>

#define ID char

#define MAX_IMAGE_WIDTH 240

class Screen {
public:
  Screen(std::string, int16_t, int16_t);

  const std::string name;
  const int16_t width;
  const int16_t height;

  Screen *next;
  Screen *previous;

  virtual void draw(lv_obj_t* obj);

  void addComponent(Component *comp);
  void addSelectable(Selectable *sel);

  void activeSelected();
  void nextSelected();
  void previousSelected();

protected:
  uint timeSinceClear = 0;

  std::vector<Component *> components;
  std::vector<Selectable *> selectables;
  uint currentSelected;
};