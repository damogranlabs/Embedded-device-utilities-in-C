/**
 ******************************************************************************
 * File Name          : lcd.h
 * Description        : This file provides code for the configuration
 *                      of HD44780 based LCD
 * @date    13-Feb-2021
 * @author  Domen Jurkovic, Damogran Labs
 * @source  http://damogranlabs.com/
 *          https://github.com/damogranlabs
 * @version v1.3
*/
 
#ifndef __LCD_H
#define __LCD_H

#include <stdint.h>
#include <stdbool.h>

void LCD_Init(uint8_t rows, uint8_t cols);
void LCD_PrintString(uint8_t y, uint8_t x, char* str);
void LCD_PrintStringWindow(uint8_t y, uint8_t x, uint8_t window_size, uint16_t speed_ms, char* str);
void LCD_PrintNumber(uint8_t y, uint8_t x, int32_t number);
void LCD_PrintFloat(uint8_t y, uint8_t x, float number_f, uint8_t precision);

void LCD_DisplayOn(void);
void LCD_DisplayOff(void);
void LCD_Clear(void);
void LCD_ClearArea(uint8_t y, uint8_t x_start, uint8_t x_end);
void LCD_BlinkOn(void);
void LCD_BlinkOff(void);
void LCD_CursorOn(void);
void LCD_CursorOff(void);
void LCD_ScrollLeft(void);
void LCD_ScrollRight(void);

void LCD_CreateChar(uint8_t location, uint8_t* data);
void LCD_PutCustom(uint8_t y, uint8_t x, uint8_t location);


/**********************************************************/
/*	PRIVATE FUNCTIONS */
/**********************************************************/
void _lcd_init_pins(void);
void _lcd_send_command(uint8_t cmd);
void _lcd_send_command_4_bit(uint8_t cmd);
void _lcd_send_data(uint8_t data);
void _lcd_cursor_set(uint8_t row, uint8_t col);
void _lcd_enable_pulse(void);


#endif /* __LCD_H */
