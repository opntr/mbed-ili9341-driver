#pragma once

#include "ili9341_cdefs.h"

EXTERN_C void _lcd_bl_on();
#ifndef LCD_BL_ON
#define LCD_BL_ON _lcd_bl_on
#endif /* LCD_BL_ON */

EXTERN_C void _lcd_bl_off();
#ifndef LCD_BL_OFF
#define LCD_BL_OFF _lcd_bl_off
#endif /* LCD_BL_OFF */

EXTERN_C void delay_ms(long delay);
