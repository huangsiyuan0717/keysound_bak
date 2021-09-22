#include <stdio.h>
#include <getopt.h>
#include<iostream>
#include<fstream>
#include<string>
#include <unistd.h>

using namespace std;
int main(int argc, char *argv[])
{
    std::string str;
    pid_t pid = getpid();
    cout << pid << endl;

    cout << program_invocation_name << endl;
    system("read -p '---' var");
    
    return 0;
}