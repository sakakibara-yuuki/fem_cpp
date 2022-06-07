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

// clang++ -std=c++11 node.cpp -o node
// Field method

#define DEBUG 1

double fem::Elem::delmax = 0;
double fem::Elem::delmin = 0;

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

// void fem::Afield::setIhs(int ihs){
//     this->ihs = ihs;
// }

// void fem::Afield::setIhe(int ihe){
//     this->ihe = ihe;
// }

// void fem::Afield::setPeam(double peam){
//     this->peam = peam;
//     setEh( this->eair/this->peam);
// }

// void fem::Afield::setEh(double eh){
//     this->eh = eh;
//     updateEh();
// }

// double fem::Afield::getEh(){
//     return this->eh;
// }

// 磁気抵抗は空間が持っているというよりその要素が持っている性質では?
void fem::Afield::setExy(){
    for(int i=0; i<this->getNelem(); i++){
        this->elem[i].exy[0] = this->physicalConstant.getEair();
        this->elem[i].exy[1] = this->physicalConstant.getEair();
    }
    for(int i=this->physicalConstant.getIhs(); i<this->physicalConstant.getIhe(); i++){
        this->elem[i].exy[0] = this->physicalConstant.getEh();
        this->elem[i].exy[1] = this->physicalConstant.getEh();
    }
}

// void fem::Afield::setNdiri(int ndiri){
//     this->ndiri = ndiri;
//     this->ndis.resize(ndiri);
//     this->ndie.resize(ndiri);
//     this->diri.resize(ndiri);
// }

// int fem::Afield::getNdiri(){
//     return this->ndiri;
// }


void fem::Afield::calcElem(){

    for(int i=0; i<this->getNelem(); i++){

        int j1 = elem[i].nodeList[0];
        int j2 = elem[i].nodeList[1];
        int j3 = elem[i].nodeList[2];

        elem[i].c[0] = node[j2].xy[1] - node[j3].xy[1];
        elem[i].c[1] = node[j3].xy[1] - node[j1].xy[1];
        elem[i].c[2] = node[j1].xy[1] - node[j2].xy[1];


        elem[i].d[0] = node[j3].xy[0] - node[j2].xy[0];
        elem[i].d[1] = node[j1].xy[0] - node[j3].xy[0];
        elem[i].d[2] = node[j2].xy[0] - node[j1].xy[0];

        elem[i].delt = 0.5*( elem[i].c[1]*elem[i].d[2] - elem[i].c[2]*elem[i].d[1] );

        std::cout << "c : ";
        std::cout << elem[i].c[0] << " ";
        std::cout << elem[i].c[1] << " ";
        std::cout << elem[i].c[2] << " " << std::endl;

        std::cout << "d : ";
        std::cout << elem[i].d[0] << " ";
        std::cout << elem[i].d[1] << " ";
        std::cout << elem[i].d[2] << " " << std::endl;

        std::cout << "delt :" << elem[i].delt << " " << std::endl;
        std::cout << std::endl;

    }
}

void fem::Afield::calcElemMatrix(){
    for(int e=0; e<this->getNelem(); e++){

        double delt4 = 0.25/this->elem[e].delt;

        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                this->elem[e].se[i][j] = (this->elem[e].exy[1]*this->elem[e].c[i]*this->elem[e].c[j] + this->elem[e].exy[0]*this->elem[e].d[i]*this->elem[e].d[j] )*delt4;
            }
        }


        std::cout << "e : " << e << std::endl;
        std::cout << elem[e].exy[0] << " " << elem[e].exy[1] << std::endl;

        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                std::cout << elem[e].se[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;

    }
}


#if DEBUG
void fem::Afield::calcCoefMatrix(){

    int m = 0;
    int n = 0;

    for(int e=0; e<this->getNelem(); e++){
        for(int i=0; i<3; i++){

            m = this->elem[e].nodeList[i];

            for(int j=0; j<3; j++){
                n = this->elem[e].nodeList[j];

                // if( n > np ){
                //     this->node[m].v -= this->elem[e].se[i][j]*v[n];
                //     continue;
                // }
                // if( n < m ){
                //     continue;
                // }
                // int nd = n - m;
                this->h[m][n] += this->elem[e].se[i][j];
                // this->node[m].v -= this->elem[e].se[i][j]*v[n];
            }
        }
    }
}
#endif

void fem::Afield::calcCoefMatrix(){

    int m = 0;
    int n = 0;

    for(int e=0; e<this->getNelem(); e++){
        for(int i=0; i<3; i++){

            m = this->elem[e].nodeList[i];

            for(int j=0; j<3; j++){

                n = this->elem[e].nodeList[j];

                this->h[m][n] += this->elem[e].se[i][j];
            }
        }
    }
}

