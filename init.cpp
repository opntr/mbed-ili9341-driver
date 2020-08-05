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
    FSMC_NORSRAM_InitTypeDef FSMC_NORSRAMInitStructure;
    FSMC_NORSRAM_TimingTypeDef FSMC_NORSRAMTimingInitStructureRead;
    FSMC_NORSRAM_TimingTypeDef FSMC_NORSRAMTimingInitStructureWrite;
    HAL_StatusTypeDef status = HAL_OK;

    memset(&FSMC_NORSRAMInitStructure, 0, sizeof(FSMC_NORSRAMInitStructure));
    memset(&FSMC_NORSRAMTimingInitStructureRead, 0, sizeof(FSMC_NORSRAMTimingInitStructureRead));
    memset(&FSMC_NORSRAMTimingInitStructureWrite, 0, sizeof(FSMC_NORSRAMTimingInitStructureWrite));

    /* Enable FSMC Clock */
    __HAL_RCC_FSMC_CLK_ENABLE();

    /* Define protocol type */
    FSMC_NORSRAMInitStructure.NSBank = FSMC_NORSRAM_BANK1;
    FSMC_NORSRAMInitStructure.DataAddressMux = FSMC_DATA_ADDRESS_MUX_DISABLE;
    FSMC_NORSRAMInitStructure.MemoryType = FSMC_MEMORY_TYPE_SRAM;
    FSMC_NORSRAMInitStructure.MemoryDataWidth = FSMC_NORSRAM_MEM_BUS_WIDTH_16;
    FSMC_NORSRAMInitStructure.BurstAccessMode =  FSMC_BURST_ACCESS_MODE_DISABLE;
    FSMC_NORSRAMInitStructure.AsynchronousWait = FSMC_ASYNCHRONOUS_WAIT_DISABLE;
    FSMC_NORSRAMInitStructure.WaitSignalPolarity =  FSMC_WAIT_SIGNAL_POLARITY_LOW;
    FSMC_NORSRAMInitStructure.WrapMode = FSMC_WRAP_MODE_DISABLE;
    FSMC_NORSRAMInitStructure.WaitSignalActive = FSMC_WAIT_TIMING_BEFORE_WS;
    FSMC_NORSRAMInitStructure.WriteOperation = FSMC_WRITE_OPERATION_ENABLE;
    FSMC_NORSRAMInitStructure.WaitSignal = FSMC_WAIT_SIGNAL_DISABLE;
    FSMC_NORSRAMInitStructure.ExtendedMode = FSMC_EXTENDED_MODE_ENABLE;
    FSMC_NORSRAMInitStructure.WriteBurst = FSMC_WRITE_BURST_DISABLE;

    status = FSMC_NORSRAM_Init(FSMC_Bank1, &FSMC_NORSRAMInitStructure);

#if notyet
    /* Define Read timing parameters */
    FSMC_NORSRAMTimingInitStructureRead.AddressSetupTime = 2;
    FSMC_NORSRAMTimingInitStructureRead.AddressHoldTime = 0;
    FSMC_NORSRAMTimingInitStructureRead.DataSetupTime = 5;
    FSMC_NORSRAMTimingInitStructureRead.BusTurnAroundDuration = 0;
    FSMC_NORSRAMTimingInitStructureRead.CLKDivision =  0;
    FSMC_NORSRAMTimingInitStructureRead.DataLatency = 0;
    FSMC_NORSRAMTimingInitStructureRead.AccessMode = FSMC_ACCESS_MODE_B;
#endif

    /* Define Write Timing parameters */
    FSMC_NORSRAMTimingInitStructureWrite.AddressSetupTime = 3;
    FSMC_NORSRAMTimingInitStructureWrite.AddressHoldTime = 0;
    FSMC_NORSRAMTimingInitStructureWrite.DataSetupTime = 6;
    FSMC_NORSRAMTimingInitStructureWrite.BusTurnAroundDuration = 0;
    FSMC_NORSRAMTimingInitStructureWrite.CLKDivision = 1;
    FSMC_NORSRAMTimingInitStructureWrite.DataLatency = 0;
    FSMC_NORSRAMTimingInitStructureWrite.AccessMode = FSMC_ACCESS_MODE_A;

    // FSMC_NORSRAM_Init(FSMC_Bank1, &FSMC_NORSRAMInitStructure); // XXXOP ?

    status = FSMC_NORSRAM_Timing_Init(FSMC_Bank1,  &FSMC_NORSRAMTimingInitStructureWrite, FSMC_NORSRAM_BANK1);

    // Enable FSMC
    __FSMC_NORSRAM_ENABLE(FSMC_Bank1, FSMC_NORSRAM_BANK1);

    this->fsmc_cmd_baddr = (volatile uint16_t*)NOR_MEMORY_ADRESS1;
    this->fsmc_data_baddr = (this->fsmc_cmd_baddr + (1<<18));
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
