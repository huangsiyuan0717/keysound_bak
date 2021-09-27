#pragma once

#include "Audio.hpp"
#include "Mixer.hpp"
#include <string>

const int KEY_RELEASE = 0;
const int KEY_PRESS = 1;
const int KEY_REPEAT = 2;

void keyDetect(std::string str_event_id, Audio *audio, Mixer *mixer);

