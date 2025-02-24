#include "tools/Screen_SPI/screenControl.h"

ScreenController::ScreenController()
{
    // tft.init();
    // tft.setRotation(3);
    // tft.setCursor(0, 0);

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
    currentScreen->draw(&tft);
}

void ScreenController::setScreen(Screen *screen)
{
    Serial.write("Changing screens\n");
    tft.fillScreen(TFT_BLACK);

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