#include "plantSelectionScreen.h"
#include "homeScreen.h"
#include "lvgl.h"
#include "plantProfiles.h"
#include "src/misc/lv_area.h"
#include "src/misc/lv_event.h"
#include <stdint.h>

static lv_obj_t *plantList = NULL;
const struct plantProfile *currentPlantProfile = NULL;

static const struct plantProfile *const plantProfiles[] = {
    &ARUGULA_PROFILE, &LETTUCE_PROFILE,    &BASIL_PROFILE,
    &SPINACH_PROFILE, &KALE_PROFILE,       &CILANTRO_PROFILE,
    &PARSLEY_PROFILE, &GREEN_ONION_PROFILE};

static void event_handler(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  const struct plantProfile *p =
      (const struct plantProfile *)lv_event_get_user_data(e);
  if (code == LV_EVENT_CLICKED) {
    currentPlantProfile = p;
    updatePlantProfileLabels(currentPlantProfile);
  }
}

void drawPlantSelectionScreen(lv_obj_t *plantSelectScreen) {
  lv_obj_t *plantSelector = lv_obj_create(plantSelectScreen);
  lv_obj_set_size(plantSelector, 295, 160);
  lv_obj_align(plantSelector, LV_ALIGN_TOP_LEFT, 0, 0);

  lv_obj_set_style_bg_opa(plantSelector, LV_OPA_TRANSP, 0);
  lv_obj_set_style_border_width(plantSelector, 2, 0);

  // Enable scrolling if there are many plants
  lv_obj_set_scroll_dir(plantSelector, LV_DIR_VER);
  lv_obj_set_scrollbar_mode(plantSelector, LV_SCROLLBAR_MODE_AUTO);

  lv_obj_set_flex_flow(plantSelector, LV_FLEX_FLOW_ROW_WRAP);
  lv_obj_set_flex_align(plantSelector,
                        LV_FLEX_ALIGN_START,  // main axis
                        LV_FLEX_ALIGN_START,  // cross axis
                        LV_FLEX_ALIGN_START); // track align

  lv_obj_set_style_pad_all(plantSelector, 8, 0);
  lv_obj_set_style_pad_row(plantSelector, 8, 0);
  lv_obj_set_style_pad_column(plantSelector, 8, 0);

  const int32_t buttonWidth = 130;
  const int32_t buttonHeight = 35;

  for (size_t i = 0; i < (sizeof(plantProfiles) / sizeof(plantProfiles[0]));
       ++i) {
    const struct plantProfile *p = plantProfiles[i];

    lv_obj_t *button = lv_button_create(plantSelector);
    lv_obj_set_size(button, buttonWidth, buttonHeight);
    lv_obj_add_event_cb(button, event_handler, LV_EVENT_CLICKED, (void *)p);

    lv_obj_t *lbl = lv_label_create(button);
    lv_label_set_text(lbl, p->name);
    lv_obj_center(lbl);
  }
}
