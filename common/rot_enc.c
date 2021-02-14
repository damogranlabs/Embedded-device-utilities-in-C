/**
 ******************************************************************************
 * File Name          : rot_enc.c
 * Description        : This file provides code for handling rotary encoder
 * @date    13-Feb-2021
 * @author  Domen Jurkovic, Damogran Labs
 * @source  http://damogranlabs.com/
 *          https://github.com/damogranlabs
 * @version v1.1
 *
 * HOW TO USE THIS DRIVER:
 * 1. Set up library:
 *  1.1. Set up GPIO defines in rot_enc_user.h
 *  1.2. Initialize two pins as input pins. Pin A must trigger interrupt on rising/falling edge.
 *    NOTE: Set pull-up and pull-down resistors according to your hardware. If you are using pull-ups,
 *    common pin of the encoder should be connected to GND. (And vice versa).
 *  1.2. Create microcontroller-specific implementation of function in rot_enc_user.c
 *
 * 2. Init library:
 *  2.1. Create global encoder data storage variable:
 *    rot_enc_data_t *encoder;
 *  2.2. Init encoder object & GPIO pins
 *    rot_enc_init(&encoder, ENC_A_GPIO_Port, ENC_A_Pin, ENC_B_GPIO_Port, ENC_B_Pin);
 *
 * 3. Call rot_enc_update() function in pin A interrupt handler.
 *
 * 4. Use library (example):
 *    rot_enc_set_direction(&encoder, rot_enc_inc_cw);
 *
 *    if(rot_enc_get_count(&encoder)){
 *     //do something
 *     }
 *
 *     rot_enc_reset_count(&encoder);
 *
 *     ...
 */

#include "rot_enc.h"

/**
 * @brief Init function.
 * @param Rotary encoder data
 * @retval None
 */
void rot_enc_init(rot_enc_data_t *re_data,
                  ROT_ENC_GPIO_PORT_TYPE *port_A,
                  ROT_ENC_GPIO_PIN_TYPE pin_A,
                  ROT_ENC_GPIO_PORT_TYPE *port_B,
                  ROT_ENC_GPIO_PIN_TYPE pin_B) {
  re_data->port_A = port_A;
  re_data->pin_A = pin_A;
  re_data->port_B = port_B;
  re_data->pin_B = pin_B;

  re_data->inc_dir = ROT_ENC_INC_CW;	// default mode is CW-increment
  re_data->_last_pin_A_state = false;

  re_data->abs_rot = 0;
  re_data->diff_rot = 0;
}
/**
 * @brief Set increment direction to CW or CCW
 * @param Rotary encoder data
 * @param Direction selector
 * @retval None
 */
void rot_enc_set_direction(rot_enc_data_t *re_data, rot_enc_inc_dir_t re_dir) {
  re_data->inc_dir = re_dir;
}

/**
 * @brief Get difference from the last time this funciton was called.
 * @param Rotary encoder data
 * @retval Difference from the last time this function was called.
 */
int32_t rot_enc_get_count(rot_enc_data_t *re_data) {
  int32_t difference = re_data->diff_rot;

  re_data->diff_rot = 0;
  return difference;
}

/**
 * @brief Get absoulute count.
 * @param Rotary encoder data
 * @retval Absolute count value.
 */
int32_t rot_enc_get_abs_count(rot_enc_data_t *re_data) {
  return re_data->abs_rot;
}

/**
 * @brief Reset internal count value to zero
 * @param Rotary encoder data
 * @retval None.
 */
void rot_enc_reset_count(rot_enc_data_t *re_data) {
  re_data->diff_rot = -re_data->abs_rot;
  re_data->abs_rot = 0;
}

/**
 * @brief This function should be called in pin A interrupt routine.
 *  Function detects rotation and direction of rotary encoder based on pin A and B states.
 *  Difference is incremented/decremented according to increment mode.
 * @param Rotary encoder data
 * @retval None.
 */
void rot_enc_update(rot_enc_data_t *re_data) {
  bool pin_A_state, pin_B_state;

  pin_A_state = rot_enc_read_pin(re_data->port_A, re_data->pin_A);
  pin_B_state = rot_enc_read_pin(re_data->port_B, re_data->pin_B);

  // Check for difference between current state and last state
  if (pin_A_state != re_data->_last_pin_A_state) {
    re_data->_last_pin_A_state = pin_A_state;

    if (re_data->_last_pin_A_state == 0) {
      if (pin_B_state == 1) {
        if (re_data->inc_dir == ROT_ENC_INC_CW) {	// Increment mode
          re_data->diff_rot--;
          re_data->abs_rot--;
        }
        else {
          re_data->diff_rot++;
          re_data->abs_rot++;
        }
      }
      else {
        if (re_data->inc_dir == ROT_ENC_INC_CW) {	// Increment mode
          re_data->diff_rot++;
          re_data->abs_rot++;
        }
        else {
          re_data->diff_rot--;
          re_data->abs_rot--;
        }
      }
    }
  }
}
