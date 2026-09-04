#ifndef GUI_THEME_H
#define GUI_THEME_H

#include "src/core/lv_obj.h"
#include "src/misc/lv_color.h"

/* Hydroponics dashboard palette */
#define GUI_COLOR_BG 0x0B1B2B
#define GUI_COLOR_SURFACE 0x142636
#define GUI_COLOR_SURFACE_ALT 0x1A3044
#define GUI_COLOR_BORDER 0x2A4558
#define GUI_COLOR_ACCENT 0x3DDC84
#define GUI_COLOR_ACCENT_DIM 0x2A9D5C
#define GUI_COLOR_TEXT 0xE8F1F8
#define GUI_COLOR_TEXT_MUTED 0x8FA8BE
#define GUI_COLOR_NAVBAR 0x0F2233
#define GUI_COLOR_DANGER 0xE85D5D

lv_color_t gui_color(uint32_t hex);
void gui_style_screen(lv_obj_t *screen);
lv_obj_t *gui_create_card(lv_obj_t *parent, int32_t w, int32_t h);
void gui_style_card(lv_obj_t *card);
void gui_style_section_title(lv_obj_t *label);
void gui_style_body_text(lv_obj_t *label);
void gui_style_muted_text(lv_obj_t *label);
void gui_style_nav_button(lv_obj_t *btn, bool active);
void gui_style_primary_button(lv_obj_t *btn);
void gui_style_plant_button(lv_obj_t *btn, bool selected);
void gui_style_navbar(lv_obj_t *navbar);

#endif /* GUI_THEME_H */
