#include "init.h"

/*
 * Mostly based on information from
 * http://stm32res.ru/ru/%20STM32F4VE_LCD_ili9341%2016bit site.
 */

void
ili9341::setup_ctrl_lines()
{
#if 0
#endif /* 0 */
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
