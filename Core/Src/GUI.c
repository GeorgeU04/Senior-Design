#include "GUI.h"
#include "homeScreen.h"
#include "lv_port_disp.h"
#include "main.h"
#include "plantSelectionScreen.h"
#include "settingsScreen.h"
#include "src/core/lv_obj.h"
#include "src/core/lv_obj_event.h"
#include "src/core/lv_obj_pos.h"
#include "src/core/lv_obj_style.h"
#include "src/display/lv_display.h"
#include "src/misc/lv_event.h"
#include "src/widgets/button/lv_button.h"
#include "src/widgets/label/lv_label.h"
#include "touchscreen.h"
#include <stdint.h>

static lv_obj_t *homeScreen;
static lv_obj_t *settingsScreen;
static lv_obj_t *plantSelectScreen;

static void buttonEvent(lv_event_t *e) {
  lv_obj_t *dest = (lv_obj_t *)lv_event_get_user_data(e);
  if (dest)
    lv_screen_load(dest);
}

void initScreen(void) {
  RSX_GPIO_Port->BSRR = RSX_Pin << 16;
  HAL_Delay(20);
  RSX_GPIO_Port->BSRR = RSX_Pin;
  HAL_Delay(150);

  lv_init();
  lv_tick_set_cb(HAL_GetTick);

  lv_display_t *disp = lv_ili9341_create(240, 320, LV_LCD_FLAG_NONE,
                                         my_lcd_send_cmd, my_lcd_send_color);
  lv_display_set_default(disp);

  lv_display_set_rotation(disp, LV_DISPLAY_ROTATION_90);

  uint32_t buf_size =
      lv_display_get_horizontal_resolution(disp) * BUFFER_LINES *
      lv_color_format_get_size(lv_display_get_color_format(disp));

  uint8_t *buf1 = lv_malloc(buf_size);
  if (!buf1) {
    LV_LOG_ERROR("display draw buffer malloc failed");
    Error_Handler();
  }

  lv_display_set_buffers(disp, buf1, NULL, buf_size,
                         LV_DISPLAY_RENDER_MODE_PARTIAL);
  initTouchScreen();
}

static void styleScreen(lv_obj_t *screen) {
  lv_obj_set_style_bg_color(screen, lv_color_hex(0x0B1B2B), 0);
  lv_obj_set_style_bg_opa(screen, LV_OPA_COVER, 0);
  lv_obj_set_style_pad_all(screen, 12, 0);
}

static void drawNavbar(lv_obj_t *screen) {
  int32_t buttonWidth = 40;
  int32_t buttonHeight = 40;
  int32_t buttonY = 80;

  /* Settings button (left) */
  lv_obj_t *settingsButton = lv_button_create(screen);
  lv_obj_align(settingsButton, LV_ALIGN_CENTER, -100, buttonY);
  lv_obj_set_size(settingsButton, buttonWidth, buttonHeight);
  lv_obj_add_event_cb(settingsButton, buttonEvent, LV_EVENT_CLICKED,
                      settingsScreen);
  // lv_obj_set_style_bg_opa(settingsButton, LV_OPA_TRANSP, 0);
  // lv_obj_set_style_shadow_width(settingsButton, 0, 0);
  lv_obj_t *settingsLabel = lv_label_create(settingsButton);
  lv_label_set_text(settingsLabel, LV_SYMBOL_SETTINGS);
  lv_obj_center(settingsLabel);
  lv_obj_set_ext_click_area(settingsButton, 20);

  /* Home button (center) */
  lv_obj_t *homeButton = lv_button_create(screen);
  lv_obj_align(homeButton, LV_ALIGN_CENTER, 0, buttonY);
  lv_obj_set_size(homeButton, buttonWidth, buttonHeight);
  lv_obj_add_event_cb(homeButton, buttonEvent, LV_EVENT_CLICKED, homeScreen);
  // lv_obj_set_style_bg_opa(homeButton, LV_OPA_TRANSP, 0);
  // lv_obj_set_style_shadow_width(homeButton, 0, 0);
  lv_obj_set_ext_click_area(homeButton, 20);
  lv_obj_t *homeLabel = lv_label_create(homeButton);
  lv_label_set_text(homeLabel, LV_SYMBOL_HOME);
  lv_obj_center(homeLabel);
  lv_obj_set_ext_click_area(homeButton, 20);

  /* Plant button (right) */
  lv_obj_t *plantButton = lv_button_create(screen);
  lv_obj_align(plantButton, LV_ALIGN_CENTER, 100, buttonY);
  lv_obj_set_size(plantButton, buttonWidth, buttonHeight);
  lv_obj_add_event_cb(plantButton, buttonEvent, LV_EVENT_CLICKED,
                      plantSelectScreen);
  lv_obj_set_ext_click_area(plantButton, 20);
  // lv_obj_set_style_bg_opa(plantButton, LV_OPA_TRANSP, 0);
  // lv_obj_set_style_shadow_width(plantButton, 0, 0);
  lv_obj_t *plantLabel = lv_label_create(plantButton);
  lv_label_set_text(plantLabel, "P");
  lv_obj_center(plantLabel);
}

static void createScreens(void) {
  homeScreen = lv_obj_create(NULL);
  styleScreen(homeScreen);
  settingsScreen = lv_obj_create(NULL);
  styleScreen(settingsScreen);
  plantSelectScreen = lv_obj_create(NULL);
  styleScreen(plantSelectScreen);
}

static void drawScreens(void) {
  drawNavbar(homeScreen);
  drawHomeScreen(homeScreen);

  drawNavbar(settingsScreen);
  drawSettingsScreen(settingsScreen);

  drawNavbar(plantSelectScreen);
  drawPlantSelectionScreen(plantSelectScreen);
}

void uiInitScreens(void) {
  createScreens();
  drawScreens();
  lv_screen_load(homeScreen);
}
