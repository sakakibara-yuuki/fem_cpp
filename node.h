/*
 * node.h
 * Copyright (C) 2022 sakakibara <sakakibara@skk.local>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef NODE_H
#define NODE_H

namespace fem{
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

}

#endif /* !NODE_H */
