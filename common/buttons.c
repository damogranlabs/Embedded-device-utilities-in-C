/*
 * Template library for handling button events.
 * @date    30-May-2020
 * @author  Domen Jurkovic
 * @source  http://damogranlabs.com/
 *          https://github.com/damogranlabs/Embedded-device-utilities-in-C
 */
#include <stdlib.h>

#include "buttons.h"
#include "buttons_user.h"

static uint8_t _num_of_registered_buttons = 0; // private: number of currently registered buttons.

/**
 * @brief Handle buttons state. This function must be periodically called in a main while loop.
 *        This function calls event callbacks in buttons_user.c
 * @param buttons: an array of registered buttons.
 * @retval None
 */
void handle_buttons(button_t buttons[])
{
  uint8_t btn_num;
  btn_phy_state_t phy_state;
  button_t *btn;
  uint32_t timestamp = get_milliseconds();

  for (btn_num = 0; btn_num < _num_of_registered_buttons; btn_num++)
  {
    btn = &buttons[btn_num];
    phy_state = get_button_pin_state(&btn->cfg);
    btn->button_phy_state = phy_state;

    if (btn->first_change_timestamp == 0)
    {
      // no active tracking for this button
      if (phy_state == BTN_PHY_ACTIVE)
      {
        if (timestamp > (btn->last_event_timestamp + BTN_AFTER_PRESS_TIME_MS))
        {
          // first pulse after IDLE state
          btn->first_change_timestamp = timestamp;
        }
      }
    }
    else
    {
      // button timestamp exists, check state and time
      if (phy_state == BTN_PHY_ACTIVE)
      {
        switch (btn->button_state)
        {
        case BTN_STATE_IDLE:
          // first event on this button
          if (timestamp > (btn->first_change_timestamp + BTN_PRESS_TIME_MS))
          {
            btn->button_state = BTN_STATE_PRESS;
            on_button_press(btn);
            btn->last_event_timestamp = timestamp;
          }
          break;

        case BTN_STATE_PRESS:
          // button already pressed, handle depending on a button mode
          if (btn->cfg.press_mode == BTN_MODE_LONGPRESS)
          {
            if (timestamp > (btn->first_change_timestamp + BTN_LONGPRESS_TIME_MS))
            {
              btn->button_state = BTN_STATE_LONGPRESS;
              on_button_longpress(btn);
              btn->last_event_timestamp = timestamp;
            }
          }
          else if (btn->cfg.press_mode == BTN_MODE_REPETITIVE)
          {
            // button already pressed, repetitive mode: check if new 'on press' event should be triggered
            if (timestamp > (btn->last_event_timestamp + BTN_REPETITIVE_PRESS_TIME_MS))
            {
              on_button_press(btn);
              btn->last_event_timestamp = timestamp;
            }
          }
          break;

        case BTN_STATE_LONGPRESS: // long press mode is not repetitive
        default:
          break;
        }
      }
      else
      {
        // button is not pressed: could be glitch to debounce it or button release
        // is not active, but start timestamp exists - debounce if state != IDLE
        if (btn->button_state == BTN_STATE_IDLE)
        {
          // pulses to debounce on button press or other button line spikes
          if (timestamp > (btn->first_change_timestamp + BTN_PRESS_TIME_MS))
          {
            // non-relevant glitches, discard current tracking.
            btn->first_change_timestamp = 0;
            btn->last_event_timestamp = timestamp; // avoid immediate re-trigger phy on on->off glitches
          }
          // else: debounce
        }
        else
        {
          // state != IDLE, reset button tracking
          on_button_release(btn);
          btn->button_state = BTN_STATE_IDLE;
          btn->first_change_timestamp = 0;
          btn->last_event_timestamp = timestamp; // avoid immediate re-trigger on phy on->off glitches
        }
      }
    }
  }
}

/**
 * @brief Return true if button is still pressed (after press event was already registered and
 *        `on_button_press` callback executed.
 * @param btn: Pointer to a created button data structure.
 * @retval `true` if still pressed, `false` otherwise.
 */
bool is_button_still_pressed(button_t *btn)
{
  if (btn->button_state != BTN_STATE_IDLE)
  {
    if (btn->button_phy_state == BTN_PHY_ACTIVE)
    {
      return true;
    }
  }

  return false;
}

/**
 * @brief Add (register) button to a list of available buttons.
 * @param buttons: array of buttons where new button data will get initialized.
 * @param port: Registered button GPIO port.
 * @param pin:Registered button GPIO pin.
 * @param press_mode: Button press mode selector.
 * @retval True on success, false on invalid (too much) registered buttons.
 *    Check NUM_OF_BUTTONS define.
 */
bool register_button(button_t buttons[], BTN_GPIO_PORT_TYPE *port, BTN_GPIO_PIN_TYPE pin, btn_press_mode_t press_mode)
{
  if (_num_of_registered_buttons >= NUM_OF_BUTTONS)
  {
    return false;
  }
  button_t *btn = &buttons[_num_of_registered_buttons];
  btn->idx = _num_of_registered_buttons;

  btn->cfg.gpio_port = port;
  btn->cfg.gpio_pin = pin;
  btn->cfg.press_mode = press_mode;

  btn->button_state = BTN_STATE_IDLE;
  btn->first_change_timestamp = 0;
  btn->button_phy_state = get_button_pin_state(&btn->cfg);

  _num_of_registered_buttons++;

  return true;
}

/**
 * @brief Return number of total registered buttons. Within range 0 ... NUM_OF_BUTTONS.
 * @retval True integer value of number of buttons.
 */
uint8_t get_registered_buttons_num(void)
{
  return _num_of_registered_buttons;
}
