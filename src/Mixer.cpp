#include "Mixer.hpp"

Mixer::Mixer(uint32_t t_buffer_len) : buffer_len(t_buffer_len){
    if(t_buffer_len == 0){
        buffer == nullptr;
        pos = buffer;
        buffer_start = buffer;
        buffer_end = buffer;
        std::cout << "buffer_len = 0" << std::endl;
        return;
    }

    buffer = new uint8_t[buffer_len];
    pos = buffer;
    buffer_start = buffer;
    buffer_end = buffer_start + buffer_len;
}


void Mixer::mix(uint8_t *buf, uint32_t size, uint16_t bits_per_sample){
    if(buffer == nullptr || buffer_len == 0) {
        return;
    }

    if(size > buffer_len) size = buffer_len;

    switch(bits_per_sample){
        case 8:
            mix8(buf, size);
            break;
        default:
            break;
    }

}

void Mixer::mix8(uint8_t *buf, uint32_t size){

}

void Mixer::mix16(uint8_t *buf, uint32_t size){

}

void Mixer::mix16(uint8_t *buf, uint32_t size){

}

void Mixer::get_mix(uint8_t *buf, uint32_t size){

}

inline uint8_t Mixer::mix_uint8(uint8_t A, uint8_t B) {
    return 0;
}

inline int8_t Mixer::mix_int8(int8_t A, int8_t B){

}

inline int16_t Mixer::mix_int16(int16_t A, int16_t B){

}

inline int16_t Mixer::mix_int16(int16_t A, int16_t B){

}

inline int32_t Mixer::mix_int32(int32_t A, int32_t B){

}

