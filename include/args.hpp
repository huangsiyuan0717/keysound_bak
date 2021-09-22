#pragma once

#include"usage.hpp"
#include<getopt.h>
#include<string>
#include<iostream>

extern char* optarg;

struct argument
{
    int flag = 0;
    bool daemon = false;
    bool kill = false;
    std::string json = "";
    std::string wav_file = "";
    std::string dir = "";
    std::string log = "";
} args = {0, false, false, "", "", "", ""};


void process_command_line_arguments(int argc, char** argv){
    if(argc <= 1){
        usage();
        exit(EXIT_FAILURE);
    }

    struct option long_option[]{
        //通过C提供的结构体option获得参数
        // struct option
        // {
            // const char *name;
            // int         has_arg;
            // int        *flag;
            // int         val;
        // };
        // getopt_long() 在flag = null时返回val值，optarg为参数值

        {"file", required_argument, 0, 'f'},
        {"dir", required_argument, 0, 'd'},
        {"json", required_argument, 0, 'j'},
        {"log", required_argument, 0, 'l'},
        {"daemon", no_argument, 0, 'D'},
        {"kill", no_argument, 0, 'k'},
        {"help", no_argument, 0, '?'},
        {0, 0, 0, 0}
    };

    int c = 0;
    while((c = getopt_long(argc, argv, "kh?d:f:j:l:D", long_option, 0)) != -1){
        switch (c)
        {
        case 'd':
            args.dir = std::string(optarg);
            args.flag = 'd';
            break;
        case 'f':
            args.wav_file = std::string(optarg);
            args.flag = 'f';
            break;
        case 'j':
            args.json = std::string(optarg);
            args.flag = 'j';
            break;
        case 'l':
            args.log = std::string(optarg);
            break;
        case 'D':
            args.daemon = true;
            break;
        case 'k':
            args.kill = true;
            break;
        case 'h':
        case '?':
        default:
            usage();
            exit(EXIT_FAILURE);
            break;
        }
    }

}

