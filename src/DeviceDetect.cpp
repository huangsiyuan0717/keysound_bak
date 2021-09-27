#include "DeviceDetect.hpp"
#include "keyDetect.hpp"

#include <map>
#include <mutex>
#include <boost/thread.hpp>
#include <string>
#include <linux/input.h>
#include <vector>
#include <thread>
#include <fcntl.h>

const std::string cmd1 = "grep -E 'Handlers|EV=' /proc/bus/input/devices | grep -B1 'EV=1[2]001[3Ff]' | grep -Eo 'event[0-9]+'";
const std::string cmd2 = "grep -B2 'EV=1[2]001[3Ff]' /proc/bus/input/devices | grep event";


static std::vector<std::thread> all_threads;
static std::mutex mtx;
static std::map<std::string, std::string> key_detects;


std::string getEventId(std::string buf){
    auto pos = buf.find("event");

    if(pos == std::string::npos) return "";

    auto pos_stop = buf.find("/", pos);
    if(pos_stop == std::string::npos) pos_stop = buf.size();
    auto event_id = buf.substr(pos + 5, pos_stop - pos - 1);
    return event_id;
}

void addEventId(std::string event_id){
    mtx.lock();
    key_detects[event_id] = event_id;
    mtx.unlock();
}

bool eventIdExists(std::string str_event_id){
    if(!key_detects[str_event_id].empty()) return true;
    else return false;
}



void startExistsDevice(Audio *audio, Mixer *mixer){
    FILE *pip = popen(cmd1.c_str(), "r");

    if(!pip){
        std::cout << "error occured" << std::endl;
    }

    char buf[64];
    while(!feof(pip)){
        if(fgets(buf, 64, pip) != NULL){
            std::string str_event_id = getEventId(buf);
            str_event_id.erase(str_event_id.size() - 1);
            all_threads.push_back(std::thread(keyDetect, str_event_id, audio, mixer));
        }
    }
    pclose(pip);
}

void deviceDectect(Audio *audio, Mixer *mixer){
    startExistsDevice(audio, mixer);


}

