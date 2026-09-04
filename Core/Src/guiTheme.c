#include "guiTheme.h"
#include "src/core/lv_obj.h"
#include "src/core/lv_obj_scroll.h"
#include "src/core/lv_obj_style.h"
#include "src/font/lv_font.h"
#include "src/widgets/label/lv_label.h"

lv_color_t gui_color(uint32_t hex) { return lv_color_hex(hex); }

void gui_style_screen(lv_obj_t *screen) {
  lv_obj_set_style_bg_color(screen, gui_color(GUI_COLOR_BG), 0);
  lv_obj_set_style_bg_opa(screen, LV_OPA_COVER, 0);
  lv_obj_set_style_pad_all(screen, 8, 0);
  lv_obj_set_style_border_width(screen, 0, 0);
  lv_obj_set_style_text_color(screen, gui_color(GUI_COLOR_TEXT), 0);
  lv_obj_set_style_text_font(screen, &lv_font_montserrat_14, 0);
  /* Screens must not scroll — scrolling invalidates large areas on a slow LCD */
  lv_obj_remove_flag(screen, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_set_scrollbar_mode(screen, LV_SCROLLBAR_MODE_OFF);
}

lv_obj_t *gui_create_card(lv_obj_t *parent, int32_t w, int32_t h) {
  lv_obj_t *card = lv_obj_create(parent);
  lv_obj_set_size(card, w, h);
  gui_style_card(card);
  return card;
}

void gui_style_card(lv_obj_t *card) {
  lv_obj_set_style_bg_color(card, gui_color(GUI_COLOR_SURFACE), 0);
  lv_obj_set_style_bg_opa(card, LV_OPA_COVER, 0);
  lv_obj_set_style_border_color(card, gui_color(GUI_COLOR_BORDER), 0);
  lv_obj_set_style_border_width(card, 1, 0);
  lv_obj_set_style_border_opa(card, LV_OPA_COVER, 0);
  lv_obj_set_style_radius(card, 6, 0);
  lv_obj_set_style_pad_all(card, 8, 0);
  /* Soft shadows are very expensive on the SW renderer + parallel LCD */
  lv_obj_set_style_shadow_width(card, 0, 0);
  lv_obj_remove_flag(card, LV_OBJ_FLAG_SCROLLABLE);
}

void gui_style_section_title(lv_obj_t *label) {
  lv_obj_set_style_text_font(label, &lv_font_montserrat_16, 0);
  lv_obj_set_style_text_color(label, gui_color(GUI_COLOR_ACCENT), 0);
  lv_obj_set_style_pad_bottom(label, 4, 0);
}

void gui_style_body_text(lv_obj_t *label) {
  lv_obj_set_style_text_color(label, gui_color(GUI_COLOR_TEXT), 0);
  lv_obj_set_style_text_font(label, &lv_font_montserrat_14, 0);
}

void gui_style_muted_text(lv_obj_t *label) {
  lv_obj_set_style_text_color(label, gui_color(GUI_COLOR_TEXT_MUTED), 0);
  lv_obj_set_style_text_font(label, &lv_font_montserrat_14, 0);
}

void gui_style_nav_button(lv_obj_t *btn, bool active) {
  lv_obj_set_style_radius(btn, 8, 0);
  lv_obj_set_style_border_width(btn, active ? 2 : 1, 0);
  lv_obj_set_style_border_color(
      btn, gui_color(active ? GUI_COLOR_ACCENT : GUI_COLOR_BORDER), 0);
  lv_obj_set_style_shadow_width(btn, 0, 0);

  lv_color_t fg =
      gui_color(active ? GUI_COLOR_ACCENT : GUI_COLOR_TEXT_MUTED);

  if (active) {
    lv_obj_set_style_bg_color(btn, gui_color(GUI_COLOR_SURFACE_ALT), 0);
    lv_obj_set_style_bg_opa(btn, LV_OPA_COVER, 0);
  } else {
    lv_obj_set_style_bg_color(btn, gui_color(GUI_COLOR_SURFACE), 0);
    lv_obj_set_style_bg_opa(btn, LV_OPA_80, 0);
  }

  lv_obj_set_style_text_color(btn, fg, 0);

  /* Recolor symbol labels / plant icon image inside the button */
  uint32_t childCount = lv_obj_get_child_count(btn);
  for (uint32_t i = 0; i < childCount; ++i) {
    lv_obj_t *child = lv_obj_get_child(btn, i);
    lv_obj_set_style_text_color(child, fg, 0);
    lv_obj_set_style_image_recolor(child, fg, 0);
    lv_obj_set_style_image_recolor_opa(child, LV_OPA_COVER, 0);
  }
}

void gui_style_primary_button(lv_obj_t *btn) {
  lv_obj_set_style_radius(btn, 6, 0);
  lv_obj_set_style_bg_color(btn, gui_color(GUI_COLOR_ACCENT_DIM), 0);
  lv_obj_set_style_bg_opa(btn, LV_OPA_COVER, 0);
  lv_obj_set_style_border_width(btn, 0, 0);
  lv_obj_set_style_shadow_width(btn, 0, 0);
  lv_obj_set_style_pad_hor(btn, 16, 0);
  lv_obj_set_style_pad_ver(btn, 10, 0);
}

void gui_style_plant_button(lv_obj_t *btn, bool selected) {
  lv_obj_set_style_radius(btn, 4, 0);
  lv_obj_set_style_border_width(btn, selected ? 2 : 1, 0);
  lv_obj_set_style_border_color(
      btn, gui_color(selected ? GUI_COLOR_ACCENT : GUI_COLOR_BORDER), 0);
  lv_obj_set_style_bg_color(
      btn, gui_color(selected ? GUI_COLOR_SURFACE_ALT : GUI_COLOR_SURFACE), 0);
  lv_obj_set_style_bg_opa(btn, LV_OPA_COVER, 0);
  lv_obj_set_style_shadow_width(btn, 0, 0);
}

void gui_style_navbar(lv_obj_t *navbar) {
  lv_obj_set_style_bg_color(navbar, gui_color(GUI_COLOR_NAVBAR), 0);
  lv_obj_set_style_bg_opa(navbar, LV_OPA_COVER, 0);
  lv_obj_set_style_border_color(navbar, gui_color(GUI_COLOR_BORDER), 0);
  lv_obj_set_style_border_width(navbar, 1, 0);
  lv_obj_set_style_border_side(navbar, LV_BORDER_SIDE_TOP, 0);
  lv_obj_set_style_radius(navbar, 0, 0);
  lv_obj_set_style_pad_all(navbar, 6, 0);
  lv_obj_remove_flag(navbar, LV_OBJ_FLAG_SCROLLABLE);
}
