#include "../Inc/lv_port_disp.h"
#include "../Inc/ILI9341.h"
#include <stddef.h>

/* Send short command to the LCD. This function shall wait until the transaction
 * finishes. */
void my_lcd_send_cmd(lv_display_t *disp, const uint8_t *cmd, size_t cmd_size,
                     const uint8_t *param, size_t param_size) {
  (void)disp;

  for (size_t i = 0; i < cmd_size; ++i)
    writeCommand(cmd[i]);

  for (size_t i = 0; i < param_size; ++i)
    writeData(param[i]);
}

/* Send large array of pixel data to the LCD. If necessary, this function has to
 * do the byte-swapping. This function can do the transfer in the background. */
void my_lcd_send_color(lv_display_t *disp, const uint8_t *cmd, size_t cmd_size,
                       uint8_t *param, size_t param_size) {

  for (size_t i = 0; i < cmd_size; ++i)
    writeCommand(cmd[i]);

  for (size_t i = 0; i < param_size; i += 2) {
    writeData(param[i + 1]);
    writeData(param[i]);
  }

  lv_display_flush_ready(disp);
}
