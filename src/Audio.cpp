#include "Audio.hpp"
#include "keycode.hpp"
#include <fstream>

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

void print_err(std::string err){
    std::cout << err << std::endl;
    exit(EXIT_FAILURE);
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
    std::string err;
    switch (flag) {
        case 'd':
            if (is_dir(str)) from_dir(str);
            else {
                err = "please use directory";
                print_err(err);
            }
            return;
        case 'f':
            if (is_wav(str)) from_file(str);
            else {
                err = "please write a wav file";
                print_err(err);
            }
            return;
        case 'j':
            if (is_json(str)) from_json(str);
            else {
                err = "please use a json file";
                print_err(err);
            }
            return;
        default:
            break;
    }
}


void Audio::from_dir(const std::string& str){
    bool has_file = false;

    for(int i = 0; i < 256; i++){
        if(wav_datas[i].data) continue;

        //TODO datas 和wav_data 可以设计一个map来映射
        if(read_wav(str + "/" + KEYS[i].first + ".wav", wav_datas[i])){
            has_file = true;
            datas[KEYS[i].second] = i;
        }else{
            datas[KEYS[i].second] = 0;
        }
    }

    if(!has_file){
        std::cout << "there is no file exist in " << std::endl;
    }
};

void Audio::from_json(const std::string& str){

};

void Audio::from_file(const std::string& file){
    if(read_wav(file, wav_datas[0])){
        for(int i = 1; i < 256; i++){
            datas[i] = 0;
        }
    }else{
        std::cout << "read " << file << "error" << std::endl;
    }
};

bool Audio::read_wav(const std::string& file, WAV_DATA& wav_data){
    wav_data.data = nullptr;
    wav_data.len = 0;
    wav_data.bits_per_sample = 0;

    WAVE_HEADER header;
    std::ifstream ifs(file);
    if(ifs.is_open()){
        ifs.read((char *)&header, sizeof(WAVE_HEADER));
        
        if(!tag_is_right(header.riff_id, header.riff_type)){
            std::cout << "this file is not a wave " << std::endl;
            ifs.close();
            return false;
        }

        if(header.fmt_audio_format == 1){
            if(!init_property){
                m_Channels = header.fmt_channels;
                m_Bits_per_sample = header.fmt_bits_per_sample;
                m_Sample_rate = header.fmt_sample_rate;
                init_property = true;
            }else if(header.fmt_channels != m_Channels 
                  || header.fmt_bits_per_sample != m_Bits_per_sample
                  || header.fmt_sample_rate != m_Sample_rate){
                      ifs.close();
                      return false;
                  }
        }else{
            std::cout << file << "has not pcm tag" << std::endl;
            ifs.close();
            return false;
        }
        
        wav_data.len = header.data_size;
        wav_data.bits_per_sample = header.fmt_bits_per_sample;
        wav_data.data = new uint8_t[wav_data.len];

        ifs.read((char*)wav_data.data, wav_data.len);

        if(wav_data.len > m_Max_len) m_Max_len = wav_data.len;
        ifs.close();
        return true;
    }
    
};

bool Audio::is_wav(const std::string& file) const{
    WAVE_HEADER header;
    std::ifstream ifs(file);

    if(ifs.is_open()){
        ifs.read((char*)&header, sizeof(WAVE_HEADER));
        ifs.close();
        return tag_is_right(header.riff_id, header.riff_type);
    }else{
        ifs.close();
        return false;
    }
};

bool Audio::tag_is_right(const uint8_t *riff_id, const uint8_t *riff_type) const{
    return (riff_id[0] == 'R' && riff_id[1] == 'I' &&
            riff_id[2] == 'F' && riff_id[3] == 'F' &&
            riff_type[0] == 'W' && riff_type[1] == 'A' &&
            riff_type[2] == 'V' && riff_type[3] == 'E');
};

WAV_DATA Audio::get_way_by_code(uint16_t code){

}

Audio::~Audio(){

}

