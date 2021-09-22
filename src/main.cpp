#include"args.hpp"
#include<errno.h>
#include<fstream>
#include <signal.h>
#include <unistd.h>

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

    int a;
    std::cin >> a;
    if(args.kill){
        kill_exists_process();
        exit(EXIT_SUCCESS);
    }

    return 0;
}