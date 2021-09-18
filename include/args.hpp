#pragma once

#include"usage.hpp"

void process_command_line_arguments(int argc, char** argv){
    if(argc <= 1){
        usage();
        exit(EXIT_FAILURE);
    }
    
}

