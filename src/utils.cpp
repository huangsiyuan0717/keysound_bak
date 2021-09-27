#include "utils.hpp"
#include <iostream>
#include <map>
#include <mutex>

static std::mutex mtx;
static std::map<std::string, std::string> key_detects;

void addEventId(std::string event_id) {
    mtx.lock();
    key_detects[event_id] = event_id;
    mtx.unlock();
}

void delEventId(std::string event_id) {
    mtx.lock();
    key_detects.erase(event_id);
    mtx.unlock();

}

bool eventIdExists(std::string str_event_id){
    if(!key_detects[str_event_id].empty()) return true;
    else return false;
}




