/*
 * Template library for creating an Arduino-like UART print API. * @date    26-Apr-2020
 * @author  Domen Jurkovic
 * @source  http://damogranlabs.com/
 *          https://github.com/damogranlabs
 */

#include "uart_print_user.h"

// add hardware-specific inlcudes and defines

/**
 * @brief Send data over UART peripheral
 * @param pointer to a data
 * @param size of data (number of bytes to send
 * @retval None
 */
void send_data(uint8_t *data, uint16_t size) {
	//TODO: implement hardware specific UART handling.
}
