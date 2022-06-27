/*
 * Afield.cpp
 * Copyright (C) 2022 sakakibara <sakakibara@skk.local>
 *
 * Distributed under terms of the MIT license.
*/

#include <iostream>
#include <vector>
#include <eigen3/Eigen/Core>
#include <cmath>
#include "PhysicalConstant.h"
#include "Dirichlet.h"
#include "Afield.h"

#define DEBUG 1

using namespace fem;

double Elem::delmax = 0;
double Elem::delmin = 0;

void Afield::setPhysicalConstant(double eair, double peam, int ihs, int ihe){
    physicalConstant.setEair(1.0);
    physicalConstant.setPeam(peam);
    physicalConstant.setEh(this->getPhysicalConstant().getEair()/this->getPhysicalConstant().getPeam());
    physicalConstant.setIhe(ihe);
    physicalConstant.setIhs(ihs);

    for(int i=0; i<this->getNelem(); i++){
        this->elem[i].exy[0] = this->physicalConstant.getEair();
        this->elem[i].exy[1] = this->physicalConstant.getEair();
    }
    for(int i=this->physicalConstant.getIhs(); i<this->physicalConstant.getIhe(); i++){
        this->elem[i].exy[0] = this->physicalConstant.getEh();
        this->elem[i].exy[1] = this->physicalConstant.getEh();
    }
}

void Afield::setDirichlet(int nboun, int ndiri, const std::vector<int>& ndis, const std::vector<int>& ndie, const std::vector<int>& diri){
    dirichlet.setNboun(nboun);
    dirichlet.setNdiri(ndiri);
    dirichlet.setNdis(ndis);
    dirichlet.setNdie(ndie);
    dirichlet.setDiri(diri);
}

PhysicalConstant& Afield::getPhysicalConstant(){
    return physicalConstant;
}

Dirichlet& Afield::getDirichlet(){
    return dirichlet;
}

void Afield::calcElem(){
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

void Afield::calcElemMatrix(){
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

#ifndef DEBUG
void Afield::calcCoefMatrix(){
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

void Afield::calcCoefMatrix(){
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

