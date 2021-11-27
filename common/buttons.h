/*
 * Template library for handling button events.
 * @date    30-May-2020
 * @author  Domen Jurkovic
 * @source  http://damogranlabs.com/
 *          https://github.com/damogranlabs
 */
#ifndef __BUTTONS_H
#define __BUTTONS_H

#include "stdint.h"
#include "stdbool.h"

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
  BTN_MODE_SINGLEPRESS, // only one on_button_press() call is generated per press
  BTN_MODE_REPETITIVE,  // multiple on_button_press() calls are generated while button is pressed.
  BTN_MODE_LONGPRESS    // after on_button_press() call is generated, on_button_longpress() call can be generated.
} btn_press_mode_t;

typedef struct
{
  BTN_GPIO_PORT_TYPE *gpio_port;
  BTN_GPIO_PIN_TYPE gpio_pin;
  btn_press_mode_t press_mode;
} btn_cfg_t;

typedef struct
{
  btn_cfg_t button_cfg;
  btn_state_t button_state;
  btn_phy_state_t button_phy_state;

  uint32_t first_change_timestamp;
  uint32_t last_event_timestamp;
} button_t;

void handle_buttons(void);

button_t *register_button(BTN_GPIO_PORT_TYPE *port, BTN_GPIO_PIN_TYPE pin, btn_press_mode_t press_mode);
btn_phy_state_t get_button_pin_state(btn_cfg_t *btn_cfg);
void on_button_press(btn_cfg_t *btn_cfg);
void on_button_longpress(btn_cfg_t *btn_cfg);

#endif
