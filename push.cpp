/*
 * push.cpp
 * Copyright (C) 2022 sakakibara <sakakibara@skk.local>
 *
 * Distributed under terms of the MIT license.
*/

#include <iostream>
#include <vector>
#include <fstream>
// #include "push.h"

// clang++ -std=c++11 push.cpp -o push

int main(int argc, char *argv[]){

    std::vector<int> v(2, 1);

    v.push_back(3);

    for(int i : v){
        std::cout << i << std::endl;
    }

    std::cout << "======" << std::endl;
    std::cout << v.size() << " " << std::endl;

    return 0;
}

