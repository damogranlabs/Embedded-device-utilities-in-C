/**
 ******************************************************************************
 * File Name          : rot_enc.h
 * Description        : This file provides code for handling rotary encoder
 * @date    13-Feb-2021
 * @author  Domen Jurkovic, Damogran Labs
 * @source  http://damogranlabs.com/
 *          https://github.com/damogranlabs/Embedded-device-utilities-in-C
 * @version v1.1
 */
#ifndef __ROT_ENC_H
#define __ROT_ENC_H

#include "rot_enc_user.h"

typedef enum
{
  ROT_ENC_INC_CW, // CW pulse = +1
  ROT_ENC_INC_CCW // CW pulse = -1
} rot_enc_inc_dir_t;

typedef struct
{
  ROT_ENC_GPIO_PORT_TYPE *port_A;
  ROT_ENC_GPIO_PIN_TYPE pin_A;
  ROT_ENC_GPIO_PORT_TYPE *port_B;
  ROT_ENC_GPIO_PIN_TYPE pin_B;

  rot_enc_inc_dir_t inc_dir; //  Increment direction (CW or CCW)
  int32_t volatile abs_rot;  //  Absolute rotation from beginning
  int32_t volatile diff_rot; //  Difference in rotation from last check

  //private
  bool _last_pin_A_state; //  Last state of pin A
} rot_enc_data_t;

void rot_enc_init(rot_enc_data_t *re_data,
                  ROT_ENC_GPIO_PORT_TYPE *port_A,
                  ROT_ENC_GPIO_PIN_TYPE pin_A,
                  ROT_ENC_GPIO_PORT_TYPE *port_B,
                  ROT_ENC_GPIO_PIN_TYPE pin_B);
void rot_enc_set_direction(rot_enc_data_t *re_data, rot_enc_inc_dir_t re_dir);

volatile int32_t rot_enc_get_count(rot_enc_data_t *re_data);
volatile int32_t rot_enc_get_abs_count(rot_enc_data_t *re_data);
void rot_enc_reset_count(rot_enc_data_t *re_data);
void rot_enc_reset_abs_count(rot_enc_data_t *re_data);

void rot_enc_update(rot_enc_data_t *re_data);

#endif
