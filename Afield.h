/*
 * Afield.h
 * Copyright (C) 2022 sakakibara <sakakibara@skk.local>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef AFIELD_H
#define AFIELD_H

#ifndef NODE_H
#include "node.h"
#endif

namespace fem{
    class Afield : public Field{
        private:
            PhysicalConstant physicalConstant;
            Dirichlet dirichlet;

        public:
            std::vector<std::vector<double>> h;//全体係数
            Eigen::MatrixXd H;

            explicit Afield() : physicalConstant(), dirichlet(), h(7, std::vector<double>(7,0)), H(7,7) {};

            void setPhysicalConstant(double eair, double peam, int ihs, int ihe);
            void setDirichlet(int nboun, int ndiri, const std::vector<int>& ndis, const std::vector<int>& ndie, const std::vector<int>& diri);

            PhysicalConstant& getPhysicalConstant();
            Dirichlet& getDirichlet();
            void calcElem();
            void calcElemMatrix();
            void calcCoefMatrix();
    };
};
#endif /* !AFIELD_H */
