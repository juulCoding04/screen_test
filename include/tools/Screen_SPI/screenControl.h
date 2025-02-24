#pragma once

#include "screen.h"
#include <lvgl.h>

#define SCR_WIDTH       480
#define SCR_HEIGHT      320
#define NR_OF_SCREENS   11

#define BOOT_SCREEN     0
#define MAIN_SCREEN     1

class ScreenController {
public:
  ScreenController();

  Screen *currentScreen;

  void draw();
  void nextScreen();
  void previousScreen();

  // void createScreen();
  void setScreen(Screen *);
  Screen* getScreen(int index);
  // void deleteScreen();

private:
//   TFT_eSPI tft;
  int counter = 0;
  std::vector<Screen*> screens;
};