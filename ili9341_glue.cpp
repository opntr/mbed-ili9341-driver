#include <chrono>

#include "mbed.h"
#include "platform/mbed_thread.h"

#include "ili9341_glue.h"

using namespace std::chrono;

DigitalOut backlight(PB_1);

EXTERN_C void
_lcd_bl_on()
{

    backlight = 1;
}

EXTERN_C void
_lcd_bl_off()
{

    backlight = 0;
}

EXTERN_C void
delay_ms(long delay)
{

    ThisThread::sleep_until(Kernel::Clock::now() + delay * 1ms);
}
