#include "GUI.h"
#include "guiTheme.h"
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
#include "src/widgets/image/lv_image.h"
#include "src/widgets/label/lv_label.h"
#include "touchscreen.h"
#include <stdint.h>

static lv_obj_t *homeScreen;
static lv_obj_t *settingsScreen;
static lv_obj_t *plantSelectScreen;

typedef struct {
  lv_obj_t *settings;
  lv_obj_t *home;
  lv_obj_t *plant;
} NavButtons;

static NavButtons homeNav;
static NavButtons settingsNav;
static NavButtons plantNav;

/* Simple 16x16 plant/sprout icon (A8 alpha) */
static const uint8_t PLANT_ICON_MAP[256] = {
    /* row 0  */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    /* row 1  */ 0, 0, 0, 0, 0, 0, 40, 90, 40, 0, 0, 0, 0, 0, 0, 0,
    /* row 2  */ 0, 0, 0, 0, 0, 50, 160, 220, 160, 50, 0, 0, 0, 0, 0, 0,
    /* row 3  */ 0, 0, 0, 0, 40, 170, 255, 255, 255, 170, 40, 0, 0, 0, 0, 0,
    /* row 4  */ 0, 0, 0, 30, 140, 240, 200, 120, 200, 240, 140, 30, 0, 0, 0, 0,
    /* row 5  */ 0, 0, 20, 120, 230, 180, 80, 40, 80, 180, 230, 120, 20, 0, 0, 0,
    /* row 6  */ 0, 0, 80, 200, 160, 60, 0, 40, 0, 60, 160, 200, 80, 0, 0, 0,
    /* row 7  */ 0, 40, 180, 150, 50, 0, 0, 50, 0, 0, 50, 150, 180, 40, 0, 0,
    /* row 8  */ 0, 20, 100, 60, 0, 0, 0, 60, 0, 0, 0, 60, 100, 20, 0, 0,
    /* row 9  */ 0, 0, 0, 0, 0, 0, 0, 70, 0, 0, 0, 0, 0, 0, 0, 0,
    /* row 10 */ 0, 0, 0, 0, 0, 0, 0, 90, 0, 0, 0, 0, 0, 0, 0, 0,
    /* row 11 */ 0, 0, 0, 0, 0, 0, 0, 110, 0, 0, 0, 0, 0, 0, 0, 0,
    /* row 12 */ 0, 0, 0, 0, 0, 0, 0, 130, 0, 0, 0, 0, 0, 0, 0, 0,
    /* row 13 */ 0, 0, 0, 0, 0, 30, 80, 160, 80, 30, 0, 0, 0, 0, 0, 0,
    /* row 14 */ 0, 0, 0, 0, 40, 140, 210, 255, 210, 140, 40, 0, 0, 0, 0, 0,
    /* row 15 */ 0, 0, 0, 0, 0, 50, 120, 180, 120, 50, 0, 0, 0, 0, 0, 0,
};

static const lv_image_dsc_t PLANT_ICON = {
    .header.magic = LV_IMAGE_HEADER_MAGIC,
    .header.cf = LV_COLOR_FORMAT_A8,
    .header.flags = 0,
    .header.w = 16,
    .header.h = 16,
    .header.stride = 16,
    .data_size = sizeof(PLANT_ICON_MAP),
    .data = PLANT_ICON_MAP,
};

static NavButtons *navForScreen(lv_obj_t *screen) {
  if (screen == homeScreen)
    return &homeNav;
  if (screen == settingsScreen)
    return &settingsNav;
  if (screen == plantSelectScreen)
    return &plantNav;
  return NULL;
}

static void updateNavHighlight(lv_obj_t *activeScreen) {
  NavButtons *nav = navForScreen(activeScreen);
  if (!nav)
    return;

  gui_style_nav_button(nav->home, activeScreen == homeScreen);
  gui_style_nav_button(nav->settings, activeScreen == settingsScreen);
  gui_style_nav_button(nav->plant, activeScreen == plantSelectScreen);
}

static void buttonEvent(lv_event_t *e) {
  lv_obj_t *dest = (lv_obj_t *)lv_event_get_user_data(e);
  if (dest) {
    updateNavHighlight(dest);
    lv_screen_load(dest);
  }
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

  lv_display_set_rotation(disp, LV_DISPLAY_ROTATION_270);

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

static void styleScreen(lv_obj_t *screen) { gui_style_screen(screen); }

static lv_obj_t *createNavButton(lv_obj_t *parent, const char *symbol,
                                 lv_obj_t *dest) {
  lv_obj_t *btn = lv_button_create(parent);
  lv_obj_set_size(btn, 44, 36);
  gui_style_nav_button(btn, false);
  lv_obj_add_event_cb(btn, buttonEvent, LV_EVENT_CLICKED, dest);
  lv_obj_set_ext_click_area(btn, 12);

  lv_obj_t *label = lv_label_create(btn);
  lv_label_set_text(label, symbol);
  lv_obj_center(label);

  return btn;
}

static lv_obj_t *createPlantNavButton(lv_obj_t *parent, lv_obj_t *dest) {
  lv_obj_t *btn = lv_button_create(parent);
  lv_obj_set_size(btn, 44, 36);
  gui_style_nav_button(btn, false);
  lv_obj_add_event_cb(btn, buttonEvent, LV_EVENT_CLICKED, dest);
  lv_obj_set_ext_click_area(btn, 12);

  lv_obj_t *icon = lv_image_create(btn);
  lv_image_set_src(icon, &PLANT_ICON);
  lv_obj_set_style_image_recolor_opa(icon, LV_OPA_COVER, 0);
  lv_obj_set_style_image_recolor(icon, gui_color(GUI_COLOR_TEXT_MUTED), 0);
  lv_obj_center(icon);

  return btn;
}

static void drawNavbar(lv_obj_t *screen, NavButtons *nav) {
  lv_obj_t *navbar = lv_obj_create(screen);
  lv_obj_set_size(navbar, LV_PCT(100), 44);
  /* Keep navbar inside the padded content area so the screen never overflows */
  lv_obj_align(navbar, LV_ALIGN_BOTTOM_MID, 0, 0);
  gui_style_navbar(navbar);

  lv_obj_set_flex_flow(navbar, LV_FLEX_FLOW_ROW);
  lv_obj_set_flex_align(navbar, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_CENTER,
                        LV_FLEX_ALIGN_CENTER);

  nav->settings = createNavButton(navbar, LV_SYMBOL_SETTINGS, settingsScreen);
  nav->home = createNavButton(navbar, LV_SYMBOL_HOME, homeScreen);
  nav->plant = createPlantNavButton(navbar, plantSelectScreen);

  gui_style_nav_button(nav->settings, screen == settingsScreen);
  gui_style_nav_button(nav->home, screen == homeScreen);
  gui_style_nav_button(nav->plant, screen == plantSelectScreen);
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
  drawNavbar(homeScreen, &homeNav);
  drawHomeScreen(homeScreen);

  drawNavbar(settingsScreen, &settingsNav);
  drawSettingsScreen(settingsScreen);

  drawNavbar(plantSelectScreen, &plantNav);
  drawPlantSelectionScreen(plantSelectScreen);
}

void uiInitScreens(void) {
  createScreens();
  drawScreens();
  updateNavHighlight(homeScreen);
  lv_screen_load(homeScreen);
}
