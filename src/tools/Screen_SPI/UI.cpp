#include "constants/colors.h"
#include "tools/Screen_SPI/UI.h"

Component::Component(uint x, uint y, lv_style_t* style)
    : x(x), y(y), style(style)
{ };

void Component::setStyle(lv_style_t* style) {
  this->style = style;
}

void Component::setXY(int x, int y)
{
  this->x = x;
  this->y = y;
}

Line::Line(uint x1, uint y1, uint x2, uint y2, lv_style_t* style)
    : Component(x1, y1, style), x2(x2), y2(y2) {};

void Line::draw(lv_obj_t* parent)
{
  lv_obj_t * obj = lv_line_create(parent);
  lv_obj_add_style(obj, style, 0);
  static lv_point_t p[] = {{x, y}, {x2, y2}};
  lv_line_set_points(obj, p, 2);
}

Text::Text(uint32_t x,
           uint32_t y,
           const char* value,
           lv_style_t* style)
    : Component(x, y, style), value(value) {};

void Text::draw(lv_obj_t* parent)
{
  lv_obj_t* label = lv_label_create(parent);
  lv_label_set_text(label, value);
  lv_obj_set_x(label, x);
  lv_obj_set_y(label, y);
  lv_obj_add_style(label, style, 0);
};

void Text::setText(const char* str)
{
  this->value = str;
}

// InformationNumber::InformationNumber(
//     uint x,
//     uint y,
//     std::string name,
//     uint *value,
//     uint8_t size,
//     color_t color)
//     : Text(x, y, name, size, color), val(value) {};

// void InformationNumber::draw(TFT_eSPI *tft)
// {
//   tft->setTextColor(
//       tft->color565(color.red, color.green, color.blue), TFT_BLACK, true);
//   tft->setTextDatum(ML_DATUM);
//   tft->setTextSize(fontsize);
//   int16_t width = tft->drawString(value.c_str(), x, y, 4);

//   char str[30];
//   ltoa(*val, str, 10);
//   while (strlen(str) < 5)
//   {
//     strcat(str, "    ");
//   }
//   tft->drawString(str, x + width, y, 4);
// };

// InformationFloat::InformationFloat(uint x,
//                                    uint y,
//                                    std::string name,
//                                    float *value,
//                                    uint8_t size,
//                                    color_t color)
//     : Text(x, y, name, size, color), val(value) {};

// void InformationFloat::draw(TFT_eSPI *tft)
// {
//   tft->setTextColor(
//       tft->color565(color.red, color.green, color.blue), TFT_BLACK, true);
//   tft->setTextDatum(ML_DATUM);
//   tft->setTextSize(fontsize);
//   int16_t width = tft->drawString(value.c_str(), x, y, 4);
//   tft->drawFloat(*val, 2, x + width, y, 4);
// };

// Image::Image(int x, int y, const u_char *image, uint size) : Component(x, y), image(image), size(size) {};

// PNG_config_t *Image::png_config;
// PNG Image::png;

// void Image::pngDraw(PNGDRAW *pDraw)
// {
//   uint16_t lineBuffer[MAX_IMAGE_WIDTH];
//   png.getLineAsRGB565(pDraw, lineBuffer, PNG_RGB565_BIG_ENDIAN, 0xffffffff);
//   png_config->tft->pushImage(png_config->xpos,
//                              png_config->ypos + pDraw->y,
//                              pDraw->iWidth,
//                              1,
//                              lineBuffer);
// }

// void Image::draw(TFT_eSPI *tft)
// {
//   png_config = new PNG_config_t;
//   png_config->tft = tft;
//   png_config->xpos = x;
//   png_config->ypos = y;

//   int16_t rc = png.openFLASH((uint8_t *)image, size, pngDraw);
//   if (rc == PNG_SUCCESS)
//   {
//     // Serial.println("Successfully opened png file");
//     // Serial.printf("image specs: (%d x %d), %d bpp, pixel type: %d\n",
//     //               png.getWidth(),
//     //               png.getHeight(),
//     //               png.getBpp(),
//     //               png.getPixelType());
//     tft->startWrite();
//     uint32_t dt = millis();
//     rc = png.decode(NULL, 0);
//     // Serial.print(millis() - dt);
//     // Serial.println("ms");
//     tft->endWrite();
//     // png.close(); // not needed for memory->memory decode
//     // Serial.printf("Image loading succesfull: %s\n",
//     //               rc == PNG_SUCCESS ? "true" : "false");
//   }
// }

// Rectangle::Rectangle(int x, int y, uint width, uint height, color_t color) : Component(x, y, color), width(width), height(height) {};

// void Rectangle::draw(TFT_eSPI *tft)
// {
//   // TODO: Add actual chosen color
//   tft->fillRect(x, y, width, height, tft->color565(color.red, color.green, color.blue));
// }

Selectable::Selectable(int x, int y, bool select, lv_style_t* style) : Component(x, y, style), selectable(select) {};

// virtual functions
void Selectable::draw(lv_obj_t* parent) {};
void Selectable::activate() {};

ButtonUI::ButtonUI(int x, int y, uint width, uint height, lv_event_cb_t func, const char* str, bool select, lv_style_t* style, lv_style_t* selStyle) : Selectable(x, y, select, style), width(width), height(height), str(str), fnt(func), selStyle(selStyle)
{};

void ButtonUI::draw(lv_obj_t* parent)
{
  lv_obj_t * btn = lv_btn_create(parent);     /*Add a button the current screen*/
  lv_obj_set_pos(btn, x, y);                            /*Set its position*/
  lv_obj_set_size(btn, width, height);                          /*Set its size*/
  if (active)
  {
    lv_obj_add_style(btn, selStyle, 0);
  }
  else
  {
    lv_obj_add_style(btn, style, 0);
  }

  lv_obj_add_event_cb(btn, fnt, LV_EVENT_ALL, NULL);           /*Assign a callback to the button*/

  lv_obj_t * label = lv_label_create(btn);          /*Add a label to the button*/
  lv_label_set_text(label, str);                    /*Set the labels text*/
  lv_obj_add_style(label, style, 0);
  lv_obj_center(label);
}

// void ButtonUI::activate()
// {
//   fnt();
// }

// // ChangeableValue::ChangeableValue(int x, int y, int min, int max, int val, bool select, color_t color, color_t selColor) :
// //   Selectable(x, y, select, color)
// //   , min(min)
// //   , max(max)
// //   , val(val) {
// //   switch (selColor.type) {
// //   case single:
// //     this->selectedColor = rgba_color_t{ .red = selColor.color.single_col,
// //                                 .green = selColor.color.single_col,
// //                                 .blue = selColor.color.single_col,
// //                                 .alpha = 255 };
// //   case RGB:
// //     this->selectedColor = rgba_color_t{ selColor.color.rgb_col.red,
// //                                 selColor.color.rgb_col.green,
// //                                 selColor.color.rgb_col.blue,
// //                                 255 };
// //   case RGBA:
// //     this->selectedColor = selColor.color.rgba_col;
// //   }
// // };

// // void ChangeableValue::draw(TFT_eSPI* tft) {
// //   if (active) {
// //     tft->setTextColor(tft->color565(selectedColor.red, selectedColor.green, selectedColor.blue), TFT_BLACK, true);
// //   }
// //   else {
// //     tft->setTextColor(tft->color565(color.red, color.green, color.blue), TFT_BLACK, true);
// //   }
// //   tft->setTextDatum(ML_DATUM);
// //   tft->setTextSize(4);

// //   char str[30];
// //   ltoa(val, str, 10);
// //   while (strlen(str) < 5) {
// //     strcat(str, "    ");
// //   }
// //   tft->drawString(str, x, y, 4);
// // }