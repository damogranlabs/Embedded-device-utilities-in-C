/*
 * Template library for handling button events.
 * @date    30-May-2020
 * @author  Domen Jurkovic
 * @source  http://damogranlabs.com/
 *          https://github.com/damogranlabs
 */
#include "buttons.h"
#include "buttons_user.h"

button_t _buttons[NUM_OF_BUTTONS]; // private: store pointers to buttons description structures.
uint8_t _num_of_registered_buttons = 0; // private: number of currently registered buttons.

/**
 * @brief Handle buttons state. This function must be periodically called in a main while loop.
 *        This function calls event callbacks in buttons_user.c
 * @param None
 * @retval None
 */
void handle_buttons(void) {
  uint8_t btn_num;
  btn_phy_state_t phy_state;
  button_t *btn;
  uint32_t timestamp = HAL_GetTick();

  for (btn_num = 0; btn_num < _num_of_registered_buttons; btn_num++) {
    btn = &_buttons[btn_num];
    phy_state = get_button_pin_state(&btn->button_cfg);
    btn->button_phy_state = phy_state;

    if (btn->first_change_timestamp == 0) {
      // no active tracking for this button
      if (phy_state == BTN_PHY_ACTIVE) {
        if (timestamp > (btn->last_event_timestamp + BTN_AFTER_PRESS_TIME_MS)) {
          // first pulse after IDLE state
          btn->first_change_timestamp = timestamp;
        }
      }
    }
    else {
      // button timestamp exists, check state and time
      if (phy_state == BTN_PHY_ACTIVE) {
        switch (btn->button_state) {
          case BTN_STATE_IDLE:
            // first event on this button
            if (timestamp > (btn->first_change_timestamp + BTN_PRESS_TIME_MS)) {
              btn->button_state = BTN_STATE_PRESS;
              on_button_press(btn->button_cfg.gpio_port, btn->button_cfg.gpio_pin);
              btn->last_event_timestamp = timestamp;
            }
            break;

          case BTN_STATE_PRESS:
            // button already pressed, handle depending on a button mode
            if (btn->button_cfg.press_mode == BTN_MODE_LONGPRESS) {
              if (timestamp > (btn->first_change_timestamp + BTN_LONGPRESS_TIME_MS)) {
                btn->button_state = BTN_STATE_LONGPRESS;
                on_button_longpress(btn->button_cfg.gpio_port, btn->button_cfg.gpio_pin);
                btn->last_event_timestamp = timestamp;
              }
            }
            else if (btn->button_cfg.press_mode == BTN_MODE_REPETITIVE) {
              // button already pressed, repetitive mode: check if new 'on press' event should be triggered
              if (timestamp > (btn->last_event_timestamp + BTN_REPETITIVE_PRESS_TIME_MS)) {
                on_button_press(btn->button_cfg.gpio_port, btn->button_cfg.gpio_pin);
                btn->last_event_timestamp = timestamp;
              }
            }
            break;

          case BTN_STATE_LONGPRESS: //long press mode is not repetitive
          default:
            break;
        }
      }
      else {
        // button is not pressed: could be glitch to debounce it or button release
        //is not active, but start timestamp exists - debounce if state != IDLE
        if (btn->button_state == BTN_STATE_IDLE) {
          // pulses to debounce on button press or other button line spikes
          if (timestamp > (btn->first_change_timestamp + BTN_PRESS_TIME_MS)) {
            // non-relevant glitches, discard current tracking.
            btn->first_change_timestamp = 0;
            btn->last_event_timestamp = timestamp; // avoid immediate re-trigger phy on on->off glitches
          }
          // else: debounce
        }
        else {
          // state != IDLE, reset button tracking
          btn->button_state = BTN_STATE_IDLE;
          btn->first_change_timestamp = 0;
          btn->last_event_timestamp = timestamp; // avoid immediate re-trigger on phy on->off glitches
        }
      }
    }
  }
}

/**
 * @brief Add (register) button to a list of available buttons.
 * @param Registered button GPIO port.
 * @param Registered button GPIO pin.
 * @retval None
 */
void register_button(BTN_GPIO_PORT_TYPE *port, BTN_GPIO_PIN_TYPE pin, btn_press_mode_t press_mode) {
  _buttons[_num_of_registered_buttons].button_cfg.gpio_port = port;
  _buttons[_num_of_registered_buttons].button_cfg.gpio_pin = pin;
  _buttons[_num_of_registered_buttons].button_cfg.press_mode = press_mode;

  _buttons[_num_of_registered_buttons].button_state = BTN_STATE_IDLE;
  _buttons[_num_of_registered_buttons].first_change_timestamp = 0;
  _buttons[_num_of_registered_buttons].button_phy_state = get_button_pin_state(
      &_buttons[_num_of_registered_buttons].button_cfg);

  _num_of_registered_buttons++;
}

