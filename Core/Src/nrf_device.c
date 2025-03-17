#include "nrf_device.h"
#include <stdbool.h>
#include "main.h"
#include "stm32g4xx_ll_gpio.h"
#include "stdint.h"
#include "syslog.h"

static bool _nrf_transmit_receive_data(uint8_t *tx, uint8_t *rx, uint32_t size);

#define NRF_CS_ENABLE   LL_GPIO_ResetOutputPin(NRF_CSN_GPIO_Port, NRF_CSN_Pin)
#define NRF_CS_DISABLE  LL_GPIO_SetOutputPin(NRF_CSN_GPIO_Port, NRF_CSN_Pin)


typedef enum
{
    NRF_CMD_NOP = 0xFF,
    NRF_CMD_READ_RX_PL = 0x61,
    NRF_CMD_WRITE_TX_PL = 0xA0,
    NRF_CMD_FLUSH_TX = 0xE1,
    NRF_CMD_FLUSH_RX = 0xE2,
    NRF_CMD_REUSE_TX_PL = 0xE3,
    NRF_CMD_ACTIVATE    = 0x50,
    NRF_CMD_READ_RX_PL_WID = 0x60,
    NRF_CMD_WRITE_ASK_PL_1 = 0xA8,
    NRF_CMD_WRITE_ASK_PL_2 = 0xA9,
    NRF_CMD_WRITE_ASK_PL_3 = 0xAA,
    NRF_CMD_WRITE_ASK_PL_4 = 0xAB,
    NRF_CMD_WRITE_ASK_PL_5 = 0xAC,
    NRF_CMD_WRITE_ASK_PL_6 = 0xAD,
    NRF_CMD_WRITE_TX_PL_NO_ASK = 0xB0
}nrf_commands_t;

int8_t nrf_init(void)
{
    int8_t result = 0; 
    NRF_CS_DISABLE;

    syslog("Init nrf %d", result);
    return result;
}

int8_t nrf_read_status(uint8_t *status)
{
    *status = 0;
    return 0;
}

static bool _nrf_transmit_receive_data(uint8_t *tx, uint8_t *rx, uint32_t size)
{
    return false;
}

