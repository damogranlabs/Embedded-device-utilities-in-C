/**
 ******************************************************************************
 * File Name          : lcd.h
 * Description        : This file provides code for the configuration
 *                      of HD44780 based LCD
 * @date    13-Feb-2021
 * @author  Domen Jurkovic, Damogran Labs
 * @source  http://damogranlabs.com/
 *          https://github.com/damogranlabs
 * @version v1.4
*/
 
#ifndef __LCD_H
#define __LCD_H

#include <stdint.h>
#include <stdbool.h>

void lcd_init(uint8_t rows, uint8_t cols);
void lcd_print_str(uint8_t y, uint8_t x, char* str);
void lcd_print_str_window(uint8_t y, uint8_t x, uint8_t window_size, uint16_t speed_ms, char* str);
void lcd_print_int(uint8_t y, uint8_t x, int32_t number);
void lcd_print_float(uint8_t y, uint8_t x, float number_f, uint8_t precision);

void lcd_display_on(void);
void lcd_display_off(void);
void lcd_clear(void);
void lcd_clear_area(uint8_t y, uint8_t x_start, uint8_t x_end);
void lcd_blink_on(void);
void lcd_blink_off(void);
void lcd_cursor_on(void);
void lcd_cursor_off(void);
void lcd_scroll_left(void);
void lcd_scroll_right(void);

void lcd_create_char(uint8_t location, uint8_t* data);
void lcd_put_char(uint8_t y, uint8_t x, uint8_t location);

#endif /* __LCD_H */
