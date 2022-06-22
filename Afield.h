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
        // ******物質定数
        // private:
        //     double eair;
        //     double peam;
        //     double eh; //鉄の磁気抵抗

        //     int ihs; //磁気抵抗がehである最初の要素番号
        //     int ihe; //磁気抵抗がehである最後の要素番号
        // public:
        //     void setEair(double eair){ this->eair = eair; }
        //     void setPeam(double peam){ this->peam = peam; }
        //     void setIhs(int ihs){ this->ihs = ihs; }
        //     void setIhe(int ihe){ this->ihe = ihe; }
        //     void setEh(double eh){ this->eh = eh; }

        //     double getEair(){ return this->eair; }
        //     double getPeam(){ return this->peam; }
        //     double getIhs(){ return this->ihs; }
        //     double getIhe(){ return this->ihe; }
        //     double getEh(){ return this->eh; }

        //     void updateEh();

        // ******ディリクレ条件
        //private:
        //    int nboun; //固定境界節点の総数
        //    int ndiri; //ディリクレ条件でポテンシャルが等しい頂点数: ポテンシャルが1.0である頂点が123, 2.0である頂点が456ならndiri = 2

        //public:
        //    std::vector<int> ndis; //ディリクレ条件の最初の頂点番号
        //    std::vector<int> ndie; //ディリクレ条件の最後の頂点番号
        //    std::vector<int> diri; //ディリクレ条件のポテンシャル値1.0と2.0が入る

        //    //ディリクレ条件
        //    void setNdiri(int ndiri){ this->ndiri = ndiri; this->ndis.resize(ndiri); this->ndie.resize(ndiri); this->diri.resize(ndiri); }
        //    int getNdiri(){ return this->ndiri; }
        private:
            PhysicalConstant physicalConstant;
            Dirichlet dirichlet;

        public:
        // **** other
            std::vector<std::vector<double>> h;//全体係数
            // eair は簡単のため1にしている
            // 1.0/(4*M_PI*1e-7) が本来の値 
            // explicit Afield() : eair(1.0), peam(1), eh(eair/peam), ihs(0), ihe(0), ndiri(0), ndis(0), ndie(0), diri(0), h(7, std::vector<double>(7,0)) {};
            explicit Afield() : physicalConstant(), dirichlet(), h(7, std::vector<double>(7,0)) {};
            void setExy();
            void calcElem();
            void calcElemMatrix();
            void calcCoefMatrix();
            void setPhysicalConstant(double eair, double peam, int ihs, int ihe);
    };
}
#endif /* !AFIELD_H */
