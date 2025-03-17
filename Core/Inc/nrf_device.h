#pragma once

#include <stdint.h>

int8_t nrf_init(void);
int8_t nrf_read_status(uint8_t *status);