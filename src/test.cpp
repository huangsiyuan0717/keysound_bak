#include <iostream>

int main(int argc, char** argv){
    int *a;
    a = new int[10];

    for(int i = 0; i < 10; i++){
        a[i] = i * 2;
        std::cout << a[i] << std::endl;
    }
    return 0;

}