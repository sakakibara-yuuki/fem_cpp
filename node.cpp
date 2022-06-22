/*
 * node.cpp
 * Copyright (C) 2022 sakakibara <sakakibara@skk.local>
 *
 * Distributed under terms of the MIT license.
*/

#include <iostream>
#include <vector>
#include <eigen3/Eigen/Core>
#include <cmath>
#include "node.h"
#include "PhysicalConstant.h"
#include "Dirichlet.h"

// clang++ -std=c++11 node.cpp -o node
// Field method

#define DEBUG 1

using namespace fem;

double Elem::delmax = 0;
double Elem::delmin = 0;

// void fem::Field::setNpoint(int npoint){
//     this->npoint = npoint;
//     node.resize(npoint);
// }

// int fem::Field::getNpoint(){
//     return this->npoint;
// }

// void fem::Field::setNelem(int nelem){
//     this->nelem = nelem;
//     elem.resize(nelem);
// }

// int fem::Field::getNelem(){
//     return this->nelem;
// }


PhysicalConstant PhysicalConstant::getPhysicalConstant(){
    return physicalConstant;
};

