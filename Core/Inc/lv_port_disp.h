#ifndef LV_PORT_DISP_H
#define LV_PORT_DISP_H
#include "lvgl.h"
#include <stdint.h>
#include <stdlib.h>

/* Send short command to the LCD. This function shall wait until the transaction
 * finishes. */
void my_lcd_send_cmd(lv_display_t *disp, const uint8_t *cmd, size_t cmd_size,
                     const uint8_t *param, size_t param_size);

/* Send large array of pixel data to the LCD. If necessary, this function has to
 * do the byte-swapping. This function can do the transfer in the background. */
void my_lcd_send_color(lv_display_t *disp, const uint8_t *cmd, size_t cmd_size,
                       uint8_t *param, size_t param_size);

#endif // !LV_PORT_DISP_H
