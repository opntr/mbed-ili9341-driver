#include <mbed.h>

#include "init.h"

ili9341::ili9341()
{
    this->fsmc_cmd_baddr = NULL;
    this->fsmc_data_baddr = NULL;
}

ili9341::~ili9341()
{
    // teardown

    this->fsmc_cmd_baddr = NULL;
    this->fsmc_data_baddr = NULL;
}

/*
 * Mostly based on information from
 * http://stm32res.ru/ru/%20STM32F4VE_LCD_ili9341%2016bit site.
 */

void
ili9341::setup_ctrl_lines()
{
    GPIO_InitTypeDef GPIO_InitStructure;

    memset(&GPIO_InitStructure, 0, sizeof(GPIO_InitStructure));

    /* configure port_d */

    __HAL_RCC_GPIOD_CLK_ENABLE();

    GPIO_InitStructure.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_7 |
        GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
    GPIO_InitStructure.Alternate = GPIO_AF12_FSMC;
    GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStructure.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStructure);

    /* configure port_e */

    __HAL_RCC_GPIOE_CLK_ENABLE();

    GPIO_InitStructure.Pin = GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 |
        GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
    GPIO_InitStructure.Alternate = GPIO_AF12_FSMC;
    GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStructure.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStructure);
}

void
ili9341::setup_fscm()
{
#if 0
#endif /* 0 */
}

void
ili9341::setup()
{

    this->setup_ctrl_lines();
    this->setup_fscm();
}

void
ili9341::set_backlight(unsigned short percent)
{
    if (percent > 100)
        this->backlight = 0;
    else if (percent < 0)
        this->backlight = 100;
    else
        this->backlight = 100 - percent;

#if 0
#endif /* 0 */
}
