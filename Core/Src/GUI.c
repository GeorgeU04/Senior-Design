#include "GUI.h"
#include "lv_port_disp.h"
#include "main.h"
#include "src/core/lv_obj.h"
#include "src/core/lv_obj_pos.h"
#include "src/core/lv_obj_style.h"
#include "src/core/lv_obj_style_gen.h"
#include "src/display/lv_display.h"
#include "src/font/lv_font.h"
#include "src/font/lv_symbol_def.h"
#include "src/misc/lv_area.h"
#include "src/widgets/bar/lv_bar.h"
#include "src/widgets/button/lv_button.h"
#include "src/widgets/label/lv_label.h"
#include <stdint.h>
#include <string.h>

static lv_obj_t *homeScreen;
static lv_obj_t *settingsScreen;
static lv_obj_t *plantSelectScreen;

static lv_obj_t *tempValueLabel;
static lv_obj_t *waterLevelValueLabel;
static lv_obj_t *nutrientDensityValueLabel;
static lv_obj_t *plantInfoValueLabel;

void initScreen(void) {
  RSX_GPIO_Port->BSRR = RSX_Pin << 16;
  HAL_Delay(20);
  RSX_GPIO_Port->BSRR = RSX_Pin;
  HAL_Delay(150);
  lv_init();
  lv_tick_set_cb(HAL_GetTick);
  lv_display_t *screen = lv_ili9341_create(240, 320, LV_LCD_FLAG_NONE,
                                           my_lcd_send_cmd, my_lcd_send_color);
  lv_display_set_default(screen);
  lv_display_set_rotation(screen, LV_DISPLAY_ROTATION_90);
  uint8_t *buf1 = NULL;
  uint8_t *buf2 = NULL;
  uint32_t buf_size =
      lv_display_get_horizontal_resolution(screen) * BUFFER_LINES *
      lv_color_format_get_size(lv_display_get_color_format(screen));

  buf1 = lv_malloc(buf_size);
  if (buf1 == NULL) {
    LV_LOG_ERROR("display draw buffer malloc failed");
    Error_Handler();
  }

  lv_display_set_buffers(screen, buf1, buf2, buf_size,
                         LV_DISPLAY_RENDER_MODE_PARTIAL);
}

static void styleScreen(lv_obj_t *screen) {
  lv_obj_set_style_bg_color(screen, lv_color_hex(0xFF0000), 0);
  lv_obj_set_style_bg_opa(screen, LV_OPA_COVER, 0);
  lv_obj_set_style_pad_all(screen, 12, 0);
}

static void drawNavbar(lv_obj_t *screen) {
  int32_t buttonWidth = 40;
  int32_t buttonHeight = 40;
  int32_t buttonY = 80;
  /* Home Button */
  lv_obj_t *homeButon = lv_button_create(screen);
  lv_obj_align(homeButon, LV_ALIGN_CENTER, 0, buttonY);
  lv_obj_set_size(homeButon, buttonWidth, buttonHeight);
  lv_obj_t *homeLabel = lv_label_create(homeButon);
  lv_label_set_text(homeLabel, LV_SYMBOL_HOME);
  lv_obj_set_style_bg_opa(homeButon, LV_OPA_TRANSP, 0);
  lv_obj_set_style_shadow_width(homeButon, 0, 0);
  lv_obj_center(homeLabel);

  /* Plant Button */
  lv_obj_t *plantButton = lv_button_create(screen);
  lv_obj_align(plantButton, LV_ALIGN_CENTER, 50, buttonY);
  lv_obj_set_size(plantButton, buttonWidth, buttonHeight);
  lv_obj_t *plantLabel = lv_label_create(plantButton);
  lv_label_set_text(plantLabel, "❀");
  lv_obj_set_style_bg_opa(plantButton, LV_OPA_TRANSP, 0);
  lv_obj_set_style_shadow_width(plantButton, 0, 0);
  lv_obj_center(plantLabel);

  /* Settings Button */
  lv_obj_t *settingsButton = lv_button_create(screen);
  lv_obj_align(settingsButton, LV_ALIGN_CENTER, -50, buttonY);
  lv_obj_set_size(settingsButton, buttonWidth, buttonHeight);
  lv_obj_t *settingsLabel = lv_label_create(settingsButton);
  lv_label_set_text(settingsLabel, LV_SYMBOL_SETTINGS);
  lv_obj_set_style_bg_opa(settingsButton, LV_OPA_TRANSP, 0);
  lv_obj_set_style_shadow_width(settingsButton, 0, 0);
  lv_obj_center(settingsLabel);
}

void showHome(void) {
  homeScreen = lv_obj_create(NULL);
  styleScreen(homeScreen);
  lv_screen_load(homeScreen);

  lv_obj_t *label = lv_label_create(homeScreen);
  lv_label_set_text(label, "Home Screen");
  lv_obj_set_style_text_color(label, lv_color_hex(0xffffff), LV_PART_MAIN);
  lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
  drawNavbar(homeScreen);
}

void showSettings(void) {
  /*Change the active screen's background color*/
  lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex(0xFF00FF),
                            LV_PART_MAIN);

  /*Create a white label, set its text and align it to the center*/
  lv_obj_t *label = lv_label_create(lv_screen_active());
  lv_label_set_text(label, "Settings Screen");
  lv_obj_set_style_text_color(lv_screen_active(), lv_color_hex(0xffffff),
                              LV_PART_MAIN);
  lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
}
void showPlantSelect(void) {
  /*Change the active screen's background color*/
  lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex(0xFF00FF),
                            LV_PART_MAIN);

  /*Create a white label, set its text and align it to the center*/
  lv_obj_t *label = lv_label_create(lv_screen_active());
  lv_label_set_text(label, "Plant Screen");
  lv_obj_set_style_text_color(lv_screen_active(), lv_color_hex(0xffffff),
                              LV_PART_MAIN);
  lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
}

void setTemperature(float c);
void setWaterLevel(float percent);
void setNutrientDensity(float ec);
void setPlantInfo(const char *name, const char *stage);
