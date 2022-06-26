/*
 * Afield.h
 * Copyright (C) 2022 sakakibara <sakakibara@skk.local>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef AFIELD_H
#define AFIELD_H

namespace fem{
    class Afield : public Field{
        private:
            PhysicalConstant physicalConstant;
            Dirichlet dirichlet;

        public:
            std::vector<std::vector<double>> h;//全体係数

            explicit Afield() : physicalConstant(), dirichlet(), h(7, std::vector<double>(7,0)) {};

            void setPhysicalConstant(double eair, double peam, int ihs, int ihe);
            void setDirichlet(int nboun, int ndiri, std::vector<int>& ndis, std::vector<int>& ndie, std::vector<int>& diri);

            PhysicalConstant& getPhysicalConstant();
            Dirichlet& getDirichlet();
            void calcElem();
            void calcElemMatrix();
            void calcCoefMatrix();
    };
};
#endif /* !AFIELD_H */
