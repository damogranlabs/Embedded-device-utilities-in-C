/*
 * Template library for creating an Arduino-like UART print API.
 * @date    26-Apr-2020
 * @author  Domen Jurkovic
 * @source  http://damogranlabs.com/
 *          https://github.com/damogranlabs/Embedded-device-utilities-in-C
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __UART_PRINT_H
#define __UART_PRINT_H

/* Includes ------------------------------------------------------------------*/
#include "stdint.h"

#include "uart_print_user.h"

//uint8_t base:
#define DEC 10
#define BIN 2
#define HEX 16
#define OCT 8

void printString(char *data);                     //send/print string overserial.
void printStringLn(char *data);                   //send/print string.
void printNumber(int32_t number, uint8_t base);   //send/print SINGED/UNSIGNED int32_t number
void printNumberLn(int32_t number, uint8_t base); //send/print SINGED/UNSIGNED number.
void printFloat(double number);
void printFloatLn(double number);

void printLn(void); //print new line and carriage return

#endif
