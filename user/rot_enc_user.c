/**
 ******************************************************************************
 * File Name          : rot_en_user.c
 * Description        : This file provides code for handling rotary encoder
 * @date    13-Feb-2021
 * @author  Domen Jurkovic, Damogran Labs
 * @source  http://damogranlabs.com/
 *          https://github.com/damogranlabs
 * @version v1.1
 */
#include "rot_enc_user.h"

/**
 * @brief Microcontroller-specific implementation of GPIO pin read function
 * @param GPIO port
 * @param GPIO pin
 * @retval bool (0 if pin state is logical low, 1 if pin state is logical high)
 */
bool rot_enc_read_pin(ROT_ENC_GPIO_PORT_TYPE *port, ROT_ENC_GPIO_PIN_TYPE pin) {
  return (bool) HAL_GPIO_ReadPin(port, pin);
}
