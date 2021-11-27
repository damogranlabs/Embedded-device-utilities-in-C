/**
 ******************************************************************************
 * File Name          : lcd_user.h
 * Description        : This file provides code for the configuration
 *                      of HD44780 based LCD
 * @date    13-Feb-2021
 * @author  Domen Jurkovic, Damogran Labs
 * @source  http://damogranlabs.com/
 *          https://github.com/damogranlabs
 * @version v1.4
*/

#ifndef __LCD_USER_H
#define __LCD_USER_H

#include <stdint.h>
#include <stdbool.h>

#include "stm32f0xx_ll_gpio.h"

// define GPIO port/pin object type
#define LCD_GPIO_PORT_TYPE GPIO_TypeDef
#define LCD_GPIO_PIN_TYPE uint32_t

#define LCD_D4_GPIO_Port GPIOB
#define LCD_D4_Pin GPIO_PIN_4
#define LCD_D5_GPIO_Port GPIOB
#define LCD_D5_Pin GPIO_PIN_5
#define LCD_D6_GPIO_Port GPIOB
#define LCD_D6_Pin GPIO_PIN_6
#define LCD_D7_GPIO_Port GPIOB
#define LCD_D7_Pin GPIO_PIN_7

#define LCD_RS_GPIO_Port GPIOA
#define LCD_RS_Pin GPIO_PIN_8
#define LCD_E_GPIO_Port GPIOA
#define LCD_E_Pin GPIO_PIN_10

//#define LCD_GO_TO_NEW_LINE_IF_STRING_TOO_LONG	// uncomment if strings larger than screen size should break and continue on new line.
#define LCD_WINDOW_PRINT_DELAY_MS 800 // delay between static view and window scrolling (used in LCD_PrintStringWindow();)

void lcd_delay_us(uint32_t uSec);
void lcd_delay_ms(uint32_t mSec);

void lcd_init_pins(void);
void lcd_write_pin(LCD_GPIO_PORT_TYPE *port, LCD_GPIO_PIN_TYPE pin, bool state);

#endif /* __LCD_H */
