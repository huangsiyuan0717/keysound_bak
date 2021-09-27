#include "keyDetect.hpp"
#include "utils.hpp"

#include <linux/input.h>
#include <iostream>
#include <fcntl.h>
#include <boost/thread/detail/thread.hpp>

static const std::string input_file_header = "/dev/input/event";


void keyDetect(std::string str_event_id, Audio *audio, Mixer *mixer){
    input_event ie;

    int fd;
    fd_set fds;
    struct timeval tv;

    sleep(1);
    fd = open((input_file_header + str_event_id).c_str(), O_RDONLY);

    if(fd == -1){
        std::cout << "Error occured while attempting to open event file: " 
                  << input_file_header + str_event_id << std::endl;
        std::cout << "you may not have access to the file " << std::endl;
        return;
    }

    addEventId(str_event_id);

    //这段没看懂,阻塞模式等不懂
    while(eventIdExists(str_event_id)){
        FD_ZERO(&fds);
        FD_SET(fd, &fds);
        tv.tv_sec = 0;
        tv.tv_usec = 100 * 1000;

        int ret = select(fd + 1, &fds, NULL, NULL, &tv);

        if(ret < 0) continue;
        if(!(ret > 0 && FD_ISSET(fd, &fds))) continue;

        ssize_t num = read(fd, (void *)&ie, sizeof(struct input_event));

        if(num == -1 || num != sizeof(struct input_event)) continue;

        if(ie.type == EV_KEY){
            switch(ie.value){
                case KEY_PRESS:
                {
                    WAV_DATA wd = audio->get_way_by_code(ie.code);
                    std::cout << " [" << ie.code << "] is pressed" << std::endl;
                    mixer->mix(wd.data, wd.len, wd.bits_per_sample);
                    break;
                } 
                case KEY_RELEASE:
                {
                    break;
                }
                case KEY_REPEAT:
                {
                    break;
                }
                default:
                    break;
        }
    }
    if(fd > 0) close(fd);
}
