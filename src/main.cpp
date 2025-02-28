#include <Arduino.h>

#include <lvgl.h>
#include <ESP_Panel_Library.h>
#include <ESP_IOExpander_Library.h>
// #include <ui.h>
#include "tools/Screen_SPI/UI.h"
#include "tools/Screen_SPI/screenControl.h"

/* LVGL porting configurations */
#define LVGL_TICK_PERIOD_MS     (2)
#define LVGL_TASK_MAX_DELAY_MS  (500)
#define LVGL_TASK_MIN_DELAY_MS  (1)
#define LVGL_TASK_STACK_SIZE    (4 * 1024)
#define LVGL_TASK_PRIORITY      (2)
#define LVGL_BUF_SIZE           (ESP_PANEL_LCD_H_RES * 20)

ESP_Panel *panel = NULL;
SemaphoreHandle_t lvgl_mux = NULL;                  // LVGL mutex

ScreenController* SC;

/* ------------------------------ Main Screen ------------------------------ */
Text* txt_Orion_state;
Text* txt_ELVIS_state;
Text* txt_HB_ECU;
Text* txt_HB_ASSI;
Text* txt_HB_ELVIS;
Text* txt_HB_PDU;
Text* txt_AS_debug;

static void btn_event_cb(lv_event_t * e)
{
    // lv_event_code_t code = lv_event_get_code(e);
    // lv_obj_t * btn = lv_event_get_target(e);
    // if(code == LV_EVENT_CLICKED) {
    //     static uint8_t cnt = 0;
    //     cnt++;

    //     /*Get the first child of the button which is the label and change its text*/
    //     lv_obj_t * label = lv_obj_get_child(btn, 0);
    //     lv_label_set_text_fmt(label, "Button: %d", cnt);
    // }
}

/* Display flushing */
void lvgl_port_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    panel->getLcd()->drawBitmap(area->x1, area->y1, area->x2 + 1, area->y2 + 1, color_p);
    lv_disp_flush_ready(disp);
}

void lvgl_port_lock(int timeout_ms)
{
    const TickType_t timeout_ticks = (timeout_ms < 0) ? portMAX_DELAY : pdMS_TO_TICKS(timeout_ms);
    xSemaphoreTakeRecursive(lvgl_mux, timeout_ticks);
}

void lvgl_port_unlock(void)
{
    xSemaphoreGiveRecursive(lvgl_mux);
}

void lvgl_port_task(void *arg)
{
    Serial.println("Starting LVGL task");

    uint32_t task_delay_ms = LVGL_TASK_MAX_DELAY_MS;
    while (1) {
        // Lock the mutex due to the LVGL APIs are not thread-safe
        lvgl_port_lock(-1);
        task_delay_ms = lv_timer_handler();
        // Release the mutex
        lvgl_port_unlock();
        if (task_delay_ms > LVGL_TASK_MAX_DELAY_MS) {
            task_delay_ms = LVGL_TASK_MAX_DELAY_MS;
        } else if (task_delay_ms < LVGL_TASK_MIN_DELAY_MS) {
            task_delay_ms = LVGL_TASK_MIN_DELAY_MS;
        }
        vTaskDelay(pdMS_TO_TICKS(task_delay_ms));
    }
}

void setup()
{
    Serial.begin(115200); /* prepare for possible serial debug */

    String LVGL_Arduino = "Hello LVGL! ";
    LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();

    Serial.println(LVGL_Arduino);
    Serial.println("I am ESP32_Display_Panel");

    panel = new ESP_Panel();

    /* Initialize LVGL core */
    lv_init();

    /* Initialize LVGL buffers */
    static lv_disp_draw_buf_t draw_buf;
    /* Using double buffers is more faster than single buffer */
    /* Using internal SRAM is more fast than PSRAM (Note: Memory allocated using `malloc` may be located in PSRAM.) */
    uint8_t *buf = (uint8_t *)heap_caps_calloc(1, LVGL_BUF_SIZE * sizeof(lv_color_t), MALLOC_CAP_INTERNAL);
    assert(buf);
    lv_disp_draw_buf_init(&draw_buf, buf, NULL, LVGL_BUF_SIZE);

    /* Initialize the display device */
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    /* Change the following line to your display resolution */
    disp_drv.hor_res = ESP_PANEL_LCD_H_RES;
    disp_drv.ver_res = ESP_PANEL_LCD_V_RES;
    disp_drv.flush_cb = lvgl_port_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    panel->init();

    /* Start panel */
    panel->begin();

    /* Create a task to run the LVGL task periodically */
    lvgl_mux = xSemaphoreCreateRecursiveMutex();
    xTaskCreate(lvgl_port_task, "lvgl", LVGL_TASK_STACK_SIZE, NULL, LVGL_TASK_PRIORITY, NULL);

    /* Lock the mutex due to the LVGL APIs are not thread-safe */
    lvgl_port_lock(-1);

    SC = new ScreenController();

    Screen* scr_main = SC->getScreen(1);

    // lv_obj_t *obj;

    // obj = lv_obj_create(NULL);
    // lv_obj_clear_flag( obj, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

    // lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN);

    /*Creating a new style*/
    static lv_style_t style;
    lv_style_init(&style);

    lv_style_set_line_color(&style, lv_palette_main(LV_PALETTE_GREY));
    lv_style_set_line_width(&style, 6);
    lv_style_set_line_rounded(&style, true);
    lv_style_set_text_font(&style, &lv_font_montserrat_30);

    /*Draw a line from upper left to bottom right*/
    // Line* l = new Line(0, 0, ESP_PANEL_LCD_H_RES, ESP_PANEL_LCD_V_RES, &style);
    // l->draw(ui_FirstScreen);

    // /*Drawing text on screen*/
    // Text* t = new Text(350, 150, "Hello there", &style);
    // t->draw(obj);

    // /*Drawing ButtonUI*/
    // ButtonUI* btn = new ButtonUI(10, 10, 300, 300, btn_event_cb, "Button", true, &style, &style);
    // btn->draw(obj);

    txt_Orion_state = new Text(150, 50, "UNKNOWN", &style);
    txt_ELVIS_state = new Text(150, 80, "UNKNOWN", &style);

    scr_main->addComponent(new Text(50, 50, "Orion: ", &style));
    scr_main->addComponent(txt_Orion_state);
    scr_main->addComponent(new Text(50, 80, "ELVIS: ", &style));
    scr_main->addComponent(txt_ELVIS_state);

    SC->setScreen(scr_main);

    SC->draw();

    // lv_disp_load_scr(obj);

    /* Release the mutex */
    lvgl_port_unlock();

    Serial.println("Setup done");
}

void loop()
{

}