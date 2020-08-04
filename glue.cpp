#include <chrono>

#include "mbed.h"
#include "platform/mbed_thread.h"

#include "glue.h"

using namespace std::chrono;

EXTERN_C void
delay_ms(long delay)
{
    ThisThread::sleep_until(Kernel::Clock::now() + delay * 1ms);
}
