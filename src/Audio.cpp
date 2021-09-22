#include "Audio.hpp"

Audio::Audio(const std::string str, int flag) : m_Max_len(0), init_property(false){
    init(str, flag);
}

Audio::Audio(const std::string str) : m_Max_len(0), init_property(false){
    init(str);
}

Audio::Audio(const std::string str, uint16_t channels,
             uint32_t sample_rate, uint16_t bits_per_sample) :
             m_Max_len(0), init_property(false), m_Channels(channels),
             m_Sample_rate(sample_rate), m_Bits_per_sample(bits_per_sample){
    init(str);        
}

void Audio::init(const std::string& str){
    if(is_dir(str)){
        from_dir(str);
    }else if(is_json(str)){
        from_json(str);
    }else if(is_wav(str)){
        from_file(str);
    }else{
        std::cout << "not json or dir or wav" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void Audio::init(const std::string& str, int flag){

}




