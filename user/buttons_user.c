/*
 * Template library for handling button events.
 * @date    30-May-2020
 * @author  Domen Jurkovic
 * @source  http://damogranlabs.com/
 *          https://github.com/damogranlabs
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
uint32_t get_milliseconds(void)
{
  return HAL_GetTick();
}

/**
 * @brief Low level call to get actual pin state.
 * @param Registered button configuration structure.
 * @retval BTN_PHY_ACTIVE on button press, BTN_PHY_IDLE otherwise.
 * TODO: user must implement this function to return button state.
 */
btn_phy_state_t get_button_pin_state(btn_cfg_t *btn_cfg)
{
  uint32_t port_state = LL_GPIO_ReadInputPort(btn_cfg->gpio_port);
  uint32_t pin_state = READ_BIT(port_state, btn_cfg->gpio_pin);

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
 * @brief On press (short, repetitive) button callback
 * @param *btn_cfg Button configuration structure that triggered the event.
 * @retval None.
 * TODO: user can add actions on button events here.
 */
void on_button_press(btn_cfg_t *btn_cfg)
{
  if ((btn_cfg->gpio_port == B1_GPIO_Port) && (btn_cfg->gpio_pin == B1_Pin))
  {
    //printString("B1");
  }
  if ((btn_cfg->gpio_port == B2_GPIO_Port) && (btn_cfg->gpio_pin == B2_Pin))
  {
    //printString("B2");
  }
}

/**
 * @brief On press (long) button callback
 * @param *btn_cfg Button configuration structure that triggered the event.
 * @retval None.
 * TODO: user can add actions on button events here.
 */
void on_button_longpress(btn_cfg_t *btn_cfg)
{
  if ((btn_cfg->gpio_port == B1_GPIO_Port) && (btn_cfg->gpio_pin == B1_Pin))
  {
    // printString("B1 L");
  }
  if ((btn_cfg->gpio_port == B2_GPIO_Port) && (btn_cfg->gpio_pin == B2_Pin))
  {
    // printString("B2 L");
  }
}
