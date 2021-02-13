/**
 ******************************************************************************
 * File Name          : lcd_user.c
 * Description        : This file provides code for the configuration
 *                      of HD44780 based LCD
 * @date    13-Feb-2021
 * @author  Domen Jurkovic, Damogran Labs
 * @source  http://damogranlabs.com/
 *          https://github.com/damogranlabs
 * @version v1.3
 */

/* Includes -------------------------------------*/
#include "lcd_user.h"

/**
 * @brief Microcontroller-specific implementation of microsecond delay
 * @param Microseconds to delay
 * @retval None
 * @note For core clock frequency above 1MHz. Doesn't generate precise us delay - only for simple purposes.
 */
void lcd_delay_us(uint32_t uSec) {
  uSec *= (SystemCoreClock / 1000000) / 6;

  while (uSec--) {

  }
}

/**
 * @brief Microcontroller-specific implementation of miliseconds delay
 * @param Miliseconds to delay
 * @retval None
 */
void lcd_delay_ms(uint32_t mSec) {
  HAL_Delay(mSec);
}

/**
 * @brief Microcontroller-specific implementation of GPIO initialization.
 * @retval None
 */
void lcd_init_pins(void) {
  // do initialization of pins if not already configured elsewhere
}

/**
 * @brief Microcontroller-specific implementation of GPIO output pin write-function.
 * @param GPIO port
 * @param GPIO pin
 * @param GPIO new output state
 * @retval None
 */
void lcd_write_pin(LCD_GPIO_PORT_TYPE *port, LCD_GPIO_PIN_TYPE pin, bool state) {
  if (state) {
    LL_GPIO_SetOutputPin(port, pin);
  }
  else {
    LL_GPIO_ResetOutputPin(port, pin);
  }
}

