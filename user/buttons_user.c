/*
 * Template library for handling button events.
 * @date    30-May-2020
 * @author  Domen Jurkovic
 * @source  http://damogranlabs.com/
 *          https://github.com/damogranlabs/Embedded-device-utilities-in-C/Embedded-device-utilities-in-C
 */
#include "stdint.h"

#include "buttons.h"
#include "buttons_user.h"

// add custom includes here to access required defines, cpu-specific LL functions, ...
#include "main.h"

/**
 * @brief Get current system milliseconds (systick) value (usually started at system reset).
 * @retval Milliseconds value.
 * TODO: user must implement this function to return milliseconds (systick) value.
 */
uint32_t btn_get_milliseconds(void)
{
  return HAL_GetTick();
}

/**
 * @brief Low level call to get actual pin state.
 * @param cfg: Registered button configuration structure.
 * @retval BTN_PHY_ACTIVE on button press, BTN_PHY_IDLE otherwise.
 * TODO: user must implement this function to return button state.
 */
btn_phy_state_t btn_get_pin_state(btn_cfg_t *cfg)
{
  uint32_t port_state = LL_GPIO_ReadInputPort(cfg->gpio_port);
  uint32_t pin_state = READ_BIT(port_state, cfg->gpio_pin);

  if (pin_state == 0)
  {
    return BTN_PHY_ACTIVE;
  }
  else
  {
    return BTN_PHY_IDLE;
  }
}

/**
 * @brief On press (short, repetitive) button callback.
 * @param btn: Button configuration structure that triggered the event.
 * TODO: user can add actions on button events here.
 */
void btn_on_press(button_t *btn)
{
  if ((btn->cfg.gpio_port == B1_GPIO_Port) && (btn->cfg.gpio_pin == B1_Pin))
  {
    // printString("B1 press");
  }
  if ((btn->cfg.gpio_port == B2_GPIO_Port) && (btn->cfg.gpio_pin == B2_Pin))
  {
    // printString("B2 press");
  }
}

/**
 * @brief On press (long) button callback
 * @param btn Button configuration structure that triggered the event.
 * TODO: user can add actions on button events here.
 */
void btn_on_longpress(button_t *btn)
{
  if ((btn->cfg.gpio_port == B1_GPIO_Port) && (btn->cfg.gpio_pin == B1_Pin))
  {
    // printString("B1 L");
  }
  if ((btn->cfg.gpio_port == B2_GPIO_Port) && (btn->cfg.gpio_pin == B2_Pin))
  {
    // printString("B2 L");
  }
}

/**
 * @brief On release (short, repetitive or longpress) button callback.
 * @param btn Button configuration structure that triggered the event.
 * TODO: user can add actions on button events here.
 */
void btn_on_release(button_t *btn)
{
  if ((btn->cfg.gpio_port == B1_GPIO_Port) && (btn->cfg.gpio_pin == B1_Pin))
  {
    if (state == BTN_STATE_PRESS)
    {
      // printString("B1 press release");
    }
    else if (state == BTN_STATE_LONGPRESS)
    {
      // printString("B2 press (short/long) release");
    }
  }
}