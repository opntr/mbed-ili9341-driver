#pragma once

class ili9341 {
private:
    unsigned short backlight;

protected:
    void setup_ctrl_lines();
    void setup_fscm();

public:
    void setup();
    void set_backlight(unsigned short percent);
};
