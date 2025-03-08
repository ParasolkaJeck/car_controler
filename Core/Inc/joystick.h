#pragma once

#include "stdint.h"
#include "stdbool.h"
#include <stdint.h>

typedef void (*key_press_worker)(void);

typedef enum
{
    JOYSTICK_BUTTON_OK,
    JOYSTICK_BUTTON_LEFT,
    JOYSTICK_BUTTON_RIGHT,
    JOYSTICK_BUTTON_UP,
    JOYSTICK_BUTTON_DOWN,
}joystick_buttons_t;

void js_init(void);
bool js_is_button_pressed(joystick_buttons_t butt);
void js_main(void);
void js_add_worker(joystick_buttons_t butt, key_press_worker worker);