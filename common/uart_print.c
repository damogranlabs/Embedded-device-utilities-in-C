/*
 * Template library for creating an Arduino-like UART print API.
 * @date    26-Apr-2020
 * @author  Domen Jurkovic
 * @source  http://damogranlabs.com/
 *          https://github.com/damogranlabs
 */
#include "uart_print.h"
#include "uart_print_user.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

void _printUnsignedNumber(uint32_t n, uint8_t base);

/**
 * @brief Send/print readable character/string.
 * @param pointer to a string data
 * @example printString("test data");
 * @retval None
 */
void printString(char *data)
{
  send_data((uint8_t *)data, (uint16_t)strlen(data));
}

/**
 * @brief Send/print number as a readable string.
 * @param number to convert to a readable string
 * @param decode base: DEC, HEX, OCT, BIN
 * @example printNumber(number, DEC); printNumber(2246, DEC);
 * @retval None
 */
void printNumber(int32_t number, uint8_t base)
{
  if (number < 0)
  {
    printString("-");
    number = -number;
    _printUnsignedNumber(number, base);
  }
  else
  {
    _printUnsignedNumber(number, base);
  }
}

/**
 * @brief Same as printString() but append newline.
 */
void printStringLn(char *data)
{
  send_data((uint8_t *)data, (uint16_t)strlen(data));
  printLn();
}

/**
 * @brief Same as printNumber() but append newline.
 */
void printNumberLn(int32_t number, uint8_t base)
{
  if (number < 0)
  {
    printString("-");
    number = -number;
    _printUnsignedNumber(number, base);
  }
  else
  {
    _printUnsignedNumber(number, base);
  }
  printLn();
}

/**
 * @brief Send/print newline sequence.
 * @example printLn();
 * @retval None
 */
void printLn()
{
  printString("\n\r");
}

/**
 * @brief Send/print float number as a readable string.
 * @param number to convert to a readable string
 * @example printFloat(number, DEC);
 * @note pay attention on "double" type range - approximately 6 digits after decimal point?
 * @retval None
 */
void printFloat(double number)
{
  char float_as_string[20];
  sprintf(float_as_string, "%f", number);
  printString(float_as_string);
}

/**
 * @brief Same as printFloat() but append newline.
 */
void printFloatLn(double number)
{
  printFloat(number);
  printLn();
}

/**
 * @brief Private function: send/print unsigned number as a readable string.
 * @param number to convert to a readable string
 * @param decode base: DEC, HEX, OCT, BIN
 * @example _printUnsignedNumber(number, DEC);
 * @retval None
 */
void _printUnsignedNumber(uint32_t n, uint8_t base)
{
  char buf[8 * sizeof(long) + 1]; // Assumes 8-bit chars plus zero byte.
  char *str = &buf[sizeof(buf) - 1];
  unsigned long m;
  char c;
  *str = '\0';

  //prevent crash if called with base == 1
  if (base < 2)
    base = 10;

  do
  {
    m = n;
    n /= base;
    c = m - base * n;
    *--str = c < 10 ? c + '0' : c + 'A' - 10;
  } while (n);

  printString(str);
}
