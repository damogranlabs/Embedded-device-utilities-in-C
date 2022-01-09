/**
 ******************************************************************************
 * File Name          : rot_enc_user.h
 * Description        : This file provides code for handling rotary encoder
 * @date    13-Feb-2021
 * @author  Domen Jurkovic, Damogran Labs
 * @source  http://damogranlabs.com/
 *          https://github.com/damogranlabs/Embedded-device-utilities-in-C
 * @version v1.1
 */
#ifndef __ROT_ENC_USER_H
#define __ROT_ENC_USER_H

#include <stdint.h>
#include <stdbool.h>

#include "stm32f0xx_ll_gpio.h"

#define ROT_ENC_GPIO_PORT_TYPE GPIO_TypeDef
#define ROT_ENC_GPIO_PIN_TYPE uint16_t
#define ROT_ENC_GPIO_PIN_STATE_TYPE GPIO_PinState

bool rot_enc_read_pin(ROT_ENC_GPIO_PORT_TYPE *port, ROT_ENC_GPIO_PIN_TYPE pin);

#endif
