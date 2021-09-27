#include "Audio.hpp"
#include"args.hpp"
#include "Mixer.hpp"

#include<errno.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <string>
#include <cstring>

const std::string PID_FILE = "/tmp/keysound_pid";

void create_pid_file(){
    int fd = open(PID_FILE.c_str(), O_WRONLY | O_CREAT | O_EXCL, 0644);

    if(fd != -1){
        char pid[16] = {0};
        sprintf(pid, "%d", getpid());

        if(write(fd, pid, strlen(pid)) == -1){
            close(fd);
            remove(PID_FILE.c_str());

            std::cout << "write pid file error" << std::endl;
        }else{
            close(fd);
        }
    }else{
        if(errno == EEXIST){
            std::cout << "another process is running " << std::endl;
        }else{
            std::cout << "read file error" << std::endl;
        }
        exit(EXIT_FAILURE);
    }
}




void kill_exists_process(){
    std::string cmd = 
        std::string("ps ax | grep ") +
        program_invocation_name +
        " | grep -v grep";

        pid_t pid = 0;
        
        FILE* pipe = popen(cmd.c_str(), "r");
        std::string str;
        if(pipe){
            char buf[64];
            while(!feof(pipe)){
                if(fgets(buf, 64, pipe)){
                    str += buf;
                }
            }
        }
        sscanf(str.c_str(), "%d", &pid);

        if(pid > 0 && pid != getpid()){
            kill(pid, 2);
        }
        
}


int main(int argc, char** argv){
    process_command_line_arguments(argc, argv);

    if(args.kill){
        kill_exists_process();
        exit(EXIT_SUCCESS);
    }

    std::string str;
    switch (args.flag)
    {
    case 'd':
        str = args.dir;
        break;
    case 'f':
        str = args.wav_file;
        break;
    case 'j':
        str = args.json;
        break;
    default:
        exit(EXIT_FAILURE);
    }

    if(args.daemon){
        if(daemon(1, 0) == -1){
            std::cout << "daemon creat error" << std::endl;
            exit(EXIT_FAILURE);
        }
    }    

    
    Audio audio(str, args.flag);
    Mixer mixer(audio.get_max_len());

    kill_exists_process();
    create_pid_file();
    
    
    
    return 0;
}