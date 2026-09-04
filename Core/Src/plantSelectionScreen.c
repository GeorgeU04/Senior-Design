#include "plantSelectionScreen.h"
#include "growControl.h"
#include "guiTheme.h"
#include "homeScreen.h"
#include "lvgl.h"
#include "plantProfiles.h"
#include "src/misc/lv_area.h"
#include "src/misc/lv_event.h"
#include <stdint.h>

const struct plantProfile *currentPlantProfile = NULL;

static lv_obj_t *plantSelector = NULL;
static lv_obj_t *plantButtons[8];

static const struct plantProfile *const plantProfiles[] = {
    &ARUGULA_PROFILE, &LETTUCE_PROFILE,    &BASIL_PROFILE,
    &SPINACH_PROFILE, &KALE_PROFILE,       &CILANTRO_PROFILE,
    &PARSLEY_PROFILE, &GREEN_ONION_PROFILE};

static void refreshPlantButtonStyles(void) {
  const size_t count = sizeof(plantProfiles) / sizeof(plantProfiles[0]);
  for (size_t i = 0; i < count; ++i) {
    gui_style_plant_button(plantButtons[i], plantProfiles[i] == currentPlantProfile);
  }
}

static void event_handler(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  const struct plantProfile *p =
      (const struct plantProfile *)lv_event_get_user_data(e);
  if (code == LV_EVENT_CLICKED) {
    currentPlantProfile = p;
    updatePlantProfileLabels(currentPlantProfile);
    growControl_setPlant(currentPlantProfile);
    refreshPlantButtonStyles();
  }
}

void drawPlantSelectionScreen(lv_obj_t *plantSelectScreen) {
  lv_obj_t *title = lv_label_create(plantSelectScreen);
  lv_label_set_text(title, "Select Plant");
  gui_style_section_title(title);
  lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 0);

  /* Sized so all 8 plants fit — avoids scroll redraw lag on the LCD */
  plantSelector = lv_obj_create(plantSelectScreen);
  lv_obj_set_size(plantSelector, 300, 152);
  lv_obj_align(plantSelector, LV_ALIGN_TOP_MID, 0, 20);
  gui_style_card(plantSelector);
  lv_obj_set_style_pad_all(plantSelector, 4, 0);

  lv_obj_remove_flag(plantSelector, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_set_scrollbar_mode(plantSelector, LV_SCROLLBAR_MODE_OFF);

  lv_obj_set_flex_flow(plantSelector, LV_FLEX_FLOW_ROW_WRAP);
  lv_obj_set_flex_align(plantSelector, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START,
                        LV_FLEX_ALIGN_START);
  lv_obj_set_style_pad_row(plantSelector, 4, 0);
  lv_obj_set_style_pad_column(plantSelector, 4, 0);

  const int32_t buttonWidth = 140;
  const int32_t buttonHeight = 30;

  for (size_t i = 0; i < (sizeof(plantProfiles) / sizeof(plantProfiles[0]));
       ++i) {
    const struct plantProfile *p = plantProfiles[i];

    lv_obj_t *button = lv_button_create(plantSelector);
    plantButtons[i] = button;
    lv_obj_set_size(button, buttonWidth, buttonHeight);
    gui_style_plant_button(button, p == currentPlantProfile);
    lv_obj_add_event_cb(button, event_handler, LV_EVENT_CLICKED, (void *)p);

    lv_obj_t *lbl = lv_label_create(button);
    lv_label_set_text(lbl, p->name);
    gui_style_body_text(lbl);
    lv_obj_center(lbl);
  }
}
