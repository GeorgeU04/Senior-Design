#include "../Inc/ILI9341.h"
#include "main.h"
#include <stdint.h>

inline void writeCommand(uint8_t cmd) {
  CDX_GPIO_Port->BSRR = (CDX_Pin << 16); // set CDX low
  CSX_GPIO_Port->BSRR = (CSX_Pin << 16); // set CSX low
  D0_GPIO_Port->BSRR = (0xFFu << 16) |   // clear PD0-PD7
                       ((uint32_t)cmd);  // set new data
  WRX_GPIO_Port->BSRR = (WRX_Pin << 16); // set WRX low
  WRX_GPIO_Port->BSRR = (WRX_Pin);       // set WRX high
  CSX_GPIO_Port->BSRR = (CSX_Pin);       // set CSX high
}

inline void writeData(uint8_t data) {
  CDX_GPIO_Port->BSRR = (CDX_Pin);       // set CDX high
  CSX_GPIO_Port->BSRR = (CSX_Pin << 16); // set CSX low
  D0_GPIO_Port->BSRR = (0xFFu << 16) |   // clear PD0-PD7
                       ((uint32_t)data); // set new data
  WRX_GPIO_Port->BSRR = (WRX_Pin << 16); // set WRX low
  WRX_GPIO_Port->BSRR = (WRX_Pin);       // set WRX high
  CSX_GPIO_Port->BSRR = (CSX_Pin);       // set CSX high
}
