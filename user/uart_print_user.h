/*
 * Template library for creating an Arduino-like UART print API.
 * @date    26-Apr-2020
 * @author  Domen Jurkovic
 * @source  http://damogranlabs.com/
 *          https://github.com/damogranlabs/Embedded-device-utilities-in-C
 *
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __UART_PRINT_USER_H
#define __UART_PRINT_USER_H

/* Includes ------------------------------------------------------------------*/
#include "stdint.h"

void send_data(uint8_t *data, uint16_t size);

#endif
