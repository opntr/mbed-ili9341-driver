#pragma once

#include <cstdint>

#include "contrib/ili9341/ili9341.h"

class ili9341 {
private:
    unsigned short backlight;
    volatile uint16_t *fsmc_cmd_baddr;
    volatile uint16_t *fsmc_data_baddr;

protected:
    void setup_ctrl_lines();
    void setup_fscm();

public:
    ili9341();
    ~ili9341();

    void setup();
    void set_backlight(unsigned short percent);
};
