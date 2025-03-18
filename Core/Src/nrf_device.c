#include "nrf_device.h"
#include <stdbool.h>
#include "main.h"
#include "stm32g4xx_ll_gpio.h"
#include "stdint.h"
#include "syslog.h"
#include "spi.h"

extern SPI_HandleTypeDef hspi2;

static bool _nrf_transmit_receive_data(const uint8_t *tx, uint8_t *rx, uint32_t size);

#define NRF_CS_ENABLE   LL_GPIO_ResetOutputPin(NRF_CSN_GPIO_Port, NRF_CSN_Pin)
#define NRF_CS_DISABLE  LL_GPIO_SetOutputPin(NRF_CSN_GPIO_Port, NRF_CSN_Pin)
#define NRF_SPI_TIMEOUT (100)

typedef enum
{
    NRF_CMD_NOP = 0xFF,
    NRF_CMD_READ_MASK = 0x00,
    NRF_CMD_WRITE_MASK = 0x20,
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


#define NRF24_REG_CONFIG            0x00
#define NRF24_REG_EN_AA             0x01
#define NRF24_REG_EN_RXADDR         0x02
#define NRF24_REG_SETUP_AW          0x03
#define NRF24_REG_SETUP_RETR        0x04
#define NRF24_REG_RF_CH             0x05
#define NRF24_REG_RF_SETUP          0x06
#define NRF24_REG_STATUS            0x07
#define NRF24_REG_OBSERVE_TX        0x08    // Read-Only
#define NRF24_REG_RPD               0x09    // Read-Only
#define NRF24_REG_RX_ADDR_P0        0x0A
#define NRF24_REG_RX_ADDR_P1        0x0B
#define NRF24_REG_RX_ADDR_P2        0x0C
#define NRF24_REG_RX_ADDR_P3        0x0D
#define NRF24_REG_RX_ADDR_P4        0x0E
#define NRF24_REG_RX_ADDR_P5        0x0F
#define NRF24_REG_TX_ADDR           0x10
#define NRF24_REG_RX_PW_P0          0x11
#define NRF24_REG_RX_PW_P1          0x12
#define NRF24_REG_RX_PW_P2          0x13
#define NRF24_REG_RX_PW_P3          0x14
#define NRF24_REG_RX_PW_P4          0x15
#define NRF24_REG_RX_PW_P5          0x16
#define NRF24_REG_FIFO_STATUS       0x17
#define NRF24_REG_DYNPD             0x1C
#define NRF24_REG_FEATURE           0x1D


int8_t nrf_init(void)
{
    int8_t result = 0; 
    NRF_CS_DISABLE;
    uint8_t status;
    result = nrf_read_status(&status);
    syslog("Init nrf %d|%d", result, status);
    return result;
}

int8_t nrf_read_status(uint8_t *status)
{
    int8_t result = 0;
    *status = 0;
    const uint8_t command = NRF_CMD_NOP;
    
    if (_nrf_transmit_receive_data(&command, status, 1))
    {
        result = -1;
    }
    NRF_CS_DISABLE;
    return result;
}

int8_t nrf_read_configuration(uint8_t *configuration)
{
    const uint8_t command = NRF_CMD_READ_MASK | NRF24_REG_CONFIG;
    _nrf_transmit_receive_data(&command, configuration, sizeof(command));
    syslog("Now config %d", *configuration);
    return 0;
}

static bool _nrf_transmit_receive_data(const uint8_t *tx, uint8_t *rx, uint32_t size)
{
    bool result = false; 
    NRF_CS_ENABLE;
    HAL_StatusTypeDef transmit_res = HAL_SPI_TransmitReceive(&hspi2, tx, rx, size, NRF_SPI_TIMEOUT);  
    if (transmit_res != HAL_OK)
    {
        syslog("Transmit error, %d", (int)transmit_res);
        result = true;
    }
    else
    {
        syslog("Transmit ok");
    }
    return result;
}

