#include "Audio.hpp"
#include "keycode.hpp"

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
            std::cout << "test" << std::endl;
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

void Audio::from_file(const std::string& str){

};

bool Audio::read_wav(const std::string &, WAV_DATA &){
    
};

bool Audio::is_wav(const std::string &str) const{

};

bool Audio::tag_is_right(const uint8_t *riff_id, const uint8_t *riff_type) const{

};


Audio::~Audio(){

}

