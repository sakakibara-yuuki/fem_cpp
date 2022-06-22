/*
 * PhysicalConstant.h
 * Copyright (C) 2022 sakakibara <sakakibara@skk.local>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef PHYSICALCONSTANT_H
#define PHYSICALCONSTANT_H

namespace fem{

    class PhysicalConstant{
        private:
            double eair;
            double peam;
            double eh; //鉄の磁気抵抗

            int ihs; //磁気抵抗がehである最初の要素番号
            int ihe; //磁気抵抗がehである最後の要素番号
        public:
            PhysicalConstant() : eair(1.0), peam(1), eh(eair/peam), ihs(0), ihe(0) {};
            void setEair(double eair){ this->eair = eair; }
            void setPeam(double peam){ this->peam = peam; }
            void setEh(double eh){ this->eh = eh; }
            void setIhs(int ihs){ this->ihs = ihs; }
            void setIhe(int ihe){ this->ihe = ihe; }

            double getEair(){ return this->eair; }
            double getPeam(){ return this->peam; }
            double getEh(){ return this->eh; }
            double getIhs(){ return this->ihs; }
            double getIhe(){ return this->ihe; }
    };

}

#endif /* !PHYSICALCONSTANT_H */
