#pragma once

#include <string>
#include <sys/stat.h>
#include <iostream>

#pragma pack(push, 1)
typedef struct {
    // RIFF chuck
    uint8_t  riff_id[4];           // 文档标识							File ID
    uint32_t riff_size;            // 大小，整个文件-ID和riffsize				Size, Whole size of ID and riffsize
    uint8_t  riff_type[4];         // "wav"，表示需要format区块和data区块，需要判断		Indicates that the format block and data block are required, needs to be checked
    // FORMAT chuck
    uint8_t  fmt_id[4];            // 小写字符串，"fmt"						Lowercase string "fmt"
    uint32_t fmt_size;             // 表示区块数据的长度，不包括fmt_id和fmt_size		Indicates the length of the block data, excluding fmt_id and fmt_size
    uint16_t fmt_audio_format;     // 1表示pcm，需要判断					1 means PCM, needs to be checked
    uint16_t fmt_channels;         // 声道数量							Number of channels
    uint32_t fmt_sample_rate;      // 采样率，每秒有多少数值					Sampling rate, how many values per second
    uint32_t fmt_byte_rate;        // 每秒数据字节数=采样率*声道数*每个样本点(单)所需的bit数/8	Number of data bytes per second = sampling rate * number of channels * number of bits required for each sample point (single)/8
    uint16_t fmt_block_align;      // 每个采样所需的字节数=声道数*每个样本点(单)所需bit数/8	The number of bytes required for each sample = the number of channels * the number of bits required for each sample point (single)/8
    uint16_t fmt_bits_per_sample;  // 每个样本点(单)所需的bit数					The number of bits required for each sample point (single)
    // DATA chuck
    uint8_t  data_id[4];
    uint32_t data_size;            // 音频数据的长度=每秒字节数*时间				Audio data length = bytes per second * time
} WAVE_HEADER;
#pragma pack(pop)

typedef struct WAV_DATA {
    uint8_t *data = nullptr;
    uint32_t len = 0;
    uint16_t bits_per_sample = 0;
    uint16_t place_hold = 0;
}WAV_DATA;


class Audio {
public:
    Audio(const std::string str, int flat);
    Audio(const std::string str);
    Audio(const std::string str, uint16_t channels, uint32_t sample_rate,
            uint16_t bits_per_sample);

    //没看懂
    Audio(const Audio&) = delete;
    Audio(Audio &&) = delete;
    Audio &operator=(const Audio &) = delete;
    Audio &operator=(Audio &&) = delete;

    WAV_DATA get_way_by_code(uint16_t code);

    ~Audio();

    uint16_t get_channels() const {return m_Channels;}
    uint32_t get_sample_rate() const {return m_Sample_rate;}
    uint16_t get_bits_per_sample() const {return m_Bits_per_sample;}
    // 一个frame有多少字节	How many bytes are in a frame
    uint16_t get_frame_size() const {return m_Channels * m_Bits_per_sample / 8;}

    uint32_t get_max_len() const {return m_Max_len;};

private:
    WAV_DATA wav_datas[256];
    // 键盘编码对应wavdatas中的哪一个	Defines which of the wavdatas corresponds to the keyboard code
    uint16_t datas[256] = {0};
    // 通用属性是否已经初始化		Whether the general properties have been initialized or not
    bool init_property;

    // 最长的音频的长度			The length of the longest audio
    uint32_t m_Max_len;
    uint16_t m_Channels;
    uint32_t m_Sample_rate;
    uint16_t m_Bits_per_sample;

    bool read_wav(const std::string &, WAV_DATA &);
    void init(const std::string&);

    void init(const std::string&, int);
    void from_dir(const std::string& str);
    void from_json(const std::string& str);
    void from_file(const std::string& str);

    bool file_exists(const std::string &file) const {
        struct stat buffer;
        return (stat(file.c_str(), &buffer) == 0);
    }

    bool is_wav(const std::string &str) const;

    bool tag_is_right(const uint8_t *riff_id, const uint8_t *riff_type) const;

    bool is_dir(const std::string &str) const {
        struct stat s;
        stat(str.c_str(), &s);
        return S_ISDIR(s.st_mode);
    }

    bool is_json(const std::string &str) const {
        return str.find(".json") != std::string::npos;
    }
};