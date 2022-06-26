/*
 * test.cpp
 * Copyright (C) 2022 sakakibara <sakakibara@skk.local>
 *
 * Distributed under terms of the MIT license.
*/

#include <iostream>
#include <vector>

class A{
    private:
        std::vector<int> vec;
    public:
        void setVec(std::vector<int>& vec){
            this->vec = vec;
        }

        std::vector<int>& getVec(){
            return vec;
        }
};


int main(int argc, char *argv[]){
    A a;
    std::vector<int> v(2,1);

    a.setVec(v);
    std::cout << a.getVec().size() << std::endl;
    for(auto i: a.getVec()){
        std::cout << i << std::endl;
    }

    return 0;
}

