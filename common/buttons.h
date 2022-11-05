/*
 * Template library for handling button events.
 * @date    30-May-2020
 * @author  Domen Jurkovic
 * @source  http://damogranlabs.com/
 *          https://github.com/damogranlabs/Embedded-device-utilities-in-C
 */
#ifndef __BUTTONS_H
#define __BUTTONS_H

#include <stdint.h>
#include <stdbool.h>

#include "buttons_user.h"

typedef enum
{
  BTN_PHY_IDLE,  // button is not pressed
  BTN_PHY_ACTIVE // button is pressed
} btn_phy_state_t;

typedef enum
{
  BTN_STATE_IDLE,
  BTN_STATE_PRESS,
  BTN_STATE_LONGPRESS
} btn_state_t;

typedef enum
{
  BTN_MODE_SINGLEPRESS, // only one btn_on_press() call is generated per press
  BTN_MODE_REPETITIVE,  // multiple btn_on_press() calls are generated while button is pressed.
  BTN_MODE_LONGPRESS    // after btn_on_press() call is generated, btn_on_longpress() call can be generated.
} btn_press_mode_t;

typedef struct
{
  BTN_GPIO_PORT_TYPE *gpio_port;
  BTN_GPIO_PIN_TYPE gpio_pin;
  btn_press_mode_t press_mode;
} btn_cfg_t;

typedef struct
{
  uint8_t idx;
  btn_cfg_t cfg;
  btn_state_t state;
  btn_phy_state_t phy_state;

  uint32_t first_change_timestamp;
  uint32_t last_event_timestamp;
} button_t;

void btn_handle(button_t buttons[]);

bool btn_register(button_t buttons[], BTN_GPIO_PORT_TYPE *port, BTN_GPIO_PIN_TYPE pin, btn_press_mode_t press_mode);
uint8_t get_registered_buttons_num(void);

uint32_t btn_get_milliseconds(void);
btn_phy_state_t btn_get_pin_state(btn_cfg_t *cfg);

bool btn_is_still_pressed(button_t *btn);

void btn_on_press(button_t *btn);
void btn_on_longpress(button_t *btn);
void btn_on_release(button_t *btn);

void btn_reset_timestamps(button_t buttons[]);

#endif
