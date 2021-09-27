#pragma once
#include <iostream>
#include <mutex>

class Mixer{
public:
    Mixer(uint32_t);

    //混音Mix
    void mix(uint8_t*, uint32_t, uint16_t);

    void get_mix();
    void get_mix(uint8_t*, uint32_t);

private:
    std::mutex mtx;
    uint32_t buffer_len;
    uint8_t *buffer;
    uint8_t *buffer_start, *pos, *buffer_end;
    
    void mix8(uint8_t*, uint32_t);
    void mix16(uint8_t*, uint32_t);
    void mix32(uint8_t*, uint32_t);

    //把int和uint融合
    inline uint8_t mix_uint8(uint8_t, uint8_t);
    inline int8_t mix_int8(int8_t, int8_t);
    inline int16_t mix_int16(int16_t, int16_t);
    inline int32_t mix_int32(int32_t, int32_t);

};


