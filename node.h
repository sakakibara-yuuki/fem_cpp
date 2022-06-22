/*
 * node.h
 * Copyright (C) 2022 sakakibara <sakakibara@skk.local>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef NODE_H
#define NODE_H

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

    class Dirichlet{
        private:
            int nboun; //固定境界節点の総数
            int ndiri; //ディリクレ条件でポテンシャルが等しい頂点数: ポテンシャルが1.0である頂点が123, 2.0である頂点が456ならndiri = 2
            std::vector<int> ndis; //ディリクレ条件の最初の頂点番号
            std::vector<int> ndie; //ディリクレ条件の最後の頂点番号
            std::vector<int> diri; //ディリクレ条件のポテンシャル値1.0と2.0が入る

        public:

            //ディリクレ条件
            Dirichlet() : nboun(0), ndiri(0), ndis(0,0), ndie(0,0), diri(0,0) {};
            void setNboun(int nboun){
                this->nboun = nboun;
            }
            void setNdiri(int ndiri){
                this->ndiri = ndiri;
                setNdis(ndis);
                setNdie(ndie);
                setDiri(ndie);
            }
            void setNdis(std::vector<int>& ndis){ this->ndis = ndis; }
            void setNdie(std::vector<int>& ndie){ this->ndie = ndie; }
            void setDiri(std::vector<int>& diri){ this->diri = diri; }

            int getNboun(){ return this->nboun; }
            int getNdiri(){ return this->ndiri; }
            std::vector<int> getNdis(){ return this->ndis; }
            std::vector<int> getNdie(){ return this->ndie; }
            std::vector<int> getDiri(){ return this->diri; }
    };

    class Node{
        public:
            std::vector<double> xy; //位置
            double v; //ポテンシャル

            explicit Node() : xy(2), v(0){};
    };

    class Elem{
        public:
            std::vector<int> nodeList;
            std::vector<double> exy; //磁気抵抗
            std::vector<double> c;
            std::vector<double> d;
            std::vector<std::vector<double>> se;
            double delt;
            static double delmax;
            static double delmin;

            explicit Elem() : nodeList(3), exy(2), c(3), d(3), se(3, std::vector<double>(3,0)) {};
    };

    class Field{
        // ******Field固有のメンバ
        private:
            int npoint;
            int nelem;
        public:
            std::vector<Node> node;
            std::vector<Elem> elem;

            explicit Field(){};
            void setNpoint(int npoint){ this->npoint = npoint; node.resize(npoint); }
            void setNelem(int nelem){ this->nelem = nelem; elem.resize(nelem); }

            int getNpoint(){ return this->npoint; }
            int getNelem(){ return this->nelem; }
    };

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

#endif /* !NODE_H */
