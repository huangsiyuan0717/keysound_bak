#pragma once
#include <iostream>

class Mixer{
public:
    Mixer(uint32_t);

    //混音Mix
    void mix(uint8_t*, uint32_t, uint16_t);

    void get_mix();
    void get_mix(uint8_t*, uint32_t);
};


