#include "LCD_Controller.h"

#include "main.h"
#include "stm32g4xx_ll_gpio.h"


void lcd_set_backlight(bool state)
{
    if (state)
    {
        LL_GPIO_ResetOutputPin(LCD_BK_GPIO_Port, LCD_BK_Pin);
    }
    else
    {
        LL_GPIO_SetOutputPin(LCD_BK_GPIO_Port, LCD_BK_Pin);
    }
}