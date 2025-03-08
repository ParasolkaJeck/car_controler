#include "joystick.h"

#include "stm32g4xx_ll_gpio.h"
#include "main.h"
#include <stdint.h>

enum
{
    JS_NONE,
    JS_PRESSED,
    JS_RELESED,
};

// static uint32_t ports_masks[5];
typedef struct
{
    uint32_t mask;
    key_press_worker worker;
    bool key_event;
}key_ctx_t;

key_ctx_t key_ctx[5];

static void js_process_key_interrupt(joystick_buttons_t butt);

/**
 * @brief 
 * 
 */
void js_init(void)
{
    key_ctx[JOYSTICK_BUTTON_OK].mask     = JB_KEY_2_Pin;
    key_ctx[JOYSTICK_BUTTON_LEFT].mask   = JB_KEY_3_Pin;
    key_ctx[JOYSTICK_BUTTON_RIGHT].mask  = JB_KEY_0_Pin;
    key_ctx[JOYSTICK_BUTTON_UP].mask     = JB_KEY_1_Pin;
    key_ctx[JOYSTICK_BUTTON_DOWN].mask   = JB_KEY_4_Pin;
}

/**
 * @brief 
 * 
 * @param butt 
 * @return true 
 * @return false 
 */
bool js_is_button_pressed(joystick_buttons_t butt)
{
    uint32_t port_value = LL_GPIO_ReadInputPort(JB_KEY_0_GPIO_Port);
    if (port_value & key_ctx[butt].mask)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void js_main(void)
{
    for (uint8_t i = 0; i < 5; i++)
    {
        if (key_ctx[i].key_event != JS_NONE)
        {
            if (key_ctx[i].worker != NULL)
            {
                key_ctx[i].worker();
            }
            key_ctx[i].key_event = JS_NONE;
        }
    }
}

void js_add_worker(joystick_buttons_t butt, key_press_worker worker)
{
    key_ctx[butt].worker = worker;
}

static void js_process_key_interrupt(joystick_buttons_t butt)
{
    bool is_pressed = js_is_button_pressed(butt);
    if (is_pressed)
    {
        key_ctx[butt].key_event = JS_PRESSED;
    }
    else
    {
        key_ctx[butt].key_event = JS_RELESED;
    }
}

/**
  * @brief This function handles EXTI line0 interrupt.
  */
void EXTI0_IRQHandler(void)
{
  if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_0) != RESET)
  {
    LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_0);
    js_process_key_interrupt(JOYSTICK_BUTTON_RIGHT);
  }
}

/**
  * @brief This function handles EXTI line1 interrupt.
  */
void EXTI1_IRQHandler(void)
{
  if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_1) != RESET)
  {
    LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_1);
    js_process_key_interrupt(JOYSTICK_BUTTON_UP);
  }
}

/**
  * @brief This function handles EXTI line2 interrupt.
  */
void EXTI2_IRQHandler(void)
{
  if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_2) != RESET)
  {
    LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_2);
    js_process_key_interrupt(JOYSTICK_BUTTON_OK);
  }
}

/**
  * @brief This function handles EXTI line3 interrupt.
  */
void EXTI3_IRQHandler(void)
{
  if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_3) != RESET)
  {
    LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_3);
    js_process_key_interrupt(JOYSTICK_BUTTON_LEFT);
  }
}

/**
  * @brief This function handles EXTI line4 interrupt.
  */
void EXTI4_IRQHandler(void)
{
  if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_4) != RESET)
  {
    LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_4);
    js_process_key_interrupt(JOYSTICK_BUTTON_DOWN);
  }
}
