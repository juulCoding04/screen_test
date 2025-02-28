#include "tools/Screen_SPI/screenControl.h"

ScreenController::ScreenController()
{
    obj = lv_obj_create(NULL);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN);

    screens.push_back(new Screen("Boot", SCR_WIDTH, SCR_HEIGHT));
    screens.push_back(new Screen("Main", SCR_WIDTH, SCR_HEIGHT));
    screens.push_back(new Screen("Settings", SCR_WIDTH, SCR_HEIGHT));
    screens.push_back(new Screen("Testing", SCR_WIDTH, SCR_HEIGHT));
    screens.push_back(new Screen("Power", SCR_WIDTH, SCR_HEIGHT));
    screens.push_back(new Screen("Banks", SCR_WIDTH, SCR_HEIGHT));
    screens.push_back(new Screen("CAN", SCR_WIDTH, SCR_HEIGHT));
    screens.push_back(new Screen("BSPD", SCR_WIDTH, SCR_HEIGHT));
    screens.push_back(new Screen("DRIVER", SCR_WIDTH, SCR_HEIGHT));
    screens.push_back(new Screen("AMI", SCR_WIDTH, SCR_HEIGHT));
    screens.push_back(new Screen("AMI CONTROL", SCR_WIDTH, SCR_HEIGHT));
}

void ScreenController::draw()
{
    currentScreen->draw(obj);
    lv_disp_load_scr(obj);
}

void ScreenController::setScreen(Screen *screen)
{
    Serial.write("Changing screens\n");
    // lv_obj_set_style_bg_color(obj, lv_color_hex(0x000000), LV_PART_MAIN);

    currentScreen = screen;
}

Screen* ScreenController::getScreen(int index) {
    return screens[index];
}

void ScreenController::nextScreen()
{
    // use modulo to wrap arround
    counter = (counter + 1) % NR_OF_SCREENS;
    currentScreen = screens[counter];
}

void ScreenController::previousScreen()
{
    // use modulo to wrap arround
    counter = (counter - 1) % NR_OF_SCREENS;
    currentScreen = screens[counter];
}