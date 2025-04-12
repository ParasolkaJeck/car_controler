#pragma once

#include <stdint.h>

int8_t nrf_init(void);
int8_t nrf_read_status(uint8_t *status);
int8_t nrf_read_configuration(uint8_t *configuration);
int8_t nrf_write_configuration(uint8_t configuration);

