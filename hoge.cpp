/*
 * test.cpp
 * Copyright (C) 2022 sakakibara <sakakibara@skk.local>
 *
 * Distributed under terms of the MIT license.
*/

#include <iostream>
#include <typeinfo>
// #include <cxxabi.h>

// clang++ -std=c++11 test.cpp -o test


class Hoge{
    public:
    int a;
    void huga(){
        int status;
        // std::cout << abi::__cxa_demangle(typeid(this).name(), 0, 0, &status) << std::endl;
        std::cout << typeid(this).name() << std::endl;
    }
};

int main(int argc, char *argv[]){
    Hoge hoge;
    hoge.a = 77777777;
    hoge.huga();
    // printf("%u\n", hoge);
    // std::cout << typeid(hoge).name() << std::endl; 

    return 0;
}

