#include <Arduino.h>

#include <lvgl.h>
#include <ESP_Panel_Library.h>
#include <ESP_IOExpander_Library.h>

ESP_Panel *panel = NULL;

void my_disp_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map) {
    panel->getLcd()->drawBitmap(area->x1, area->y1, area->x2 + 1, area->y2 + 1, (lv_color_t *)px_map);
    lv_display_flush_ready(disp);
}

void setup()
{
    panel = new ESP_Panel();

    lv_init();

    lv_display_t *display = lv_display_create(ESP_PANEL_LCD_H_RES, ESP_PANEL_LCD_V_RES);

    /*Declare a buffer for 1/10 screen size*/
    #define BYTE_PER_PIXEL (LV_COLOR_FORMAT_GET_SIZE(LV_COLOR_FORMAT_RGB565)) /*will be 2 for RGB565 */
    static uint8_t buf1[ESP_PANEL_LCD_H_RES * ESP_PANEL_LCD_V_RES / 10 * BYTE_PER_PIXEL];

    lv_display_set_buffers(display, buf1, NULL, sizeof(buf1), LV_DISPLAY_RENDER_MODE_PARTIAL);  /*Initialize the display buffer.*/
    lv_display_set_flush_cb(display, my_disp_flush); /*Initialize the flush callback*/

    panel->init();

    panel->begin();

    lv_obj_t * slider1 = lv_slider_create(lv_screen_active());
    lv_slider_set_value(slider1, 70, LV_ANIM_ON);
}

void loop()
{

}