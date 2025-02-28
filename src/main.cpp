#include <Arduino.h>

#include <lvgl.h>
#include <ESP_Panel_Library.h>

#include "tools/Screen_SPI/UI.h"
#include "tools/Screen_SPI/screenControl.h"

#include "helperfunctions.h"

ScreenController* SC;

/* ------------------------------ Main Screen ------------------------------ */
Text* txt_Orion_state;
Text* txt_ELVIS_state;
Text* txt_HB_ECU;
Text* txt_HB_ASSI;
Text* txt_HB_ELVIS;
Text* txt_HB_PDU;
Text* txt_AS_debug;

void ui_init();


void setup()
{
    Serial.begin(115200); /* prepare for possible serial debug */

    String LVGL_Arduino = "Hello LVGL! ";
    LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();

    Serial.println(LVGL_Arduino);
    Serial.println("I am ESP32_Display_Panel");

    lvgl_setup(&ui_init);

    Serial.println("Setup done");
}

void loop()
{
    sleep(1);
    SC->draw();
}

void ui_init() {
    SC = new ScreenController();
    /*Creating a new style*/
    static lv_style_t style;
    lv_style_init(&style);

    lv_style_set_line_color(&style, lv_palette_main(LV_PALETTE_GREY));
    lv_style_set_line_width(&style, 6);
    lv_style_set_line_rounded(&style, true);
    lv_style_set_text_font(&style, &lv_font_montserrat_14);

    Screen* scr_main = SC->getScreen(1);

    txt_Orion_state = new Text(150, 50, "UNKNOWN", &style);
    txt_ELVIS_state = new Text(150, 80, "UNKNOWN", &style);

    txt_HB_ECU = new Text(200, 300, "NOK", &style);
    txt_HB_ASSI = new Text(280, 300, "NOK", &style);
    txt_HB_ELVIS = new Text(360, 300, "NOK", &style);
    txt_HB_PDU = new Text(440, 300, "NOK", &style);

    scr_main->addComponent(new Text(50, 50, "Orion: ", &style));
    scr_main->addComponent(txt_Orion_state);
    scr_main->addComponent(new Text(50, 80, "ELVIS: ", &style));
    scr_main->addComponent(txt_ELVIS_state);

    scr_main->addComponent(new Text(80, 300, "Heartbeats: ", &style));
    scr_main->addComponent(new Text(200, 270, "ECU", &style));
    scr_main->addComponent(txt_HB_ECU);
    scr_main->addComponent(new Text(280, 270, "ASSI", &style));
    scr_main->addComponent(txt_HB_ASSI);
    scr_main->addComponent(new Text(360, 270, "ELVIS", &style));
    scr_main->addComponent(txt_HB_ELVIS);
    scr_main->addComponent(new Text(440, 270, "PDU", &style));
    scr_main->addComponent(txt_HB_PDU);

    // lv_disp_load_scr(obj);
    SC->setScreen(scr_main);
}