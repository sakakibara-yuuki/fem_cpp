/*
 * Dirichlet.h
 * Copyright (C) 2022 sakakibara <sakakibara@skk.local>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef DIRICHLET_H
#define DIRICHLET_H

namespace fem{

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
            void setNdis(const std::vector<int>& ndis){ this->ndis = ndis; }
            void setNdie(const std::vector<int>& ndie){ this->ndie = ndie; }
            void setDiri(const std::vector<int>& diri){ this->diri = diri; }

            int getNboun(){ return nboun; }
            int getNdiri(){ return ndiri; }
            std::vector<int>& getNdis(){ return ndis; }
            std::vector<int>& getNdie(){ return ndie; }
            std::vector<int>& getDiri(){ return diri; }
    };

}

#endif /* !DIRICHLET_H */
