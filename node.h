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

            void setXy(std::vector<double> xy){
                this->xy = xy;
            };

            void setV(double v){
                this->v = v;
            };

            std::vector<double>& getXy(){
                return xy;
            };
            double getV(){
                return v;
            };
            
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

            void setNodeList(std::vector<int>& nodeList){
                this->nodeList = nodeList;
            }
            void setExy(std::vector<double>& exy){
                this->exy = exy;
            }
            void setC(std::vector<double>& c){
                this->c = c;
            }
            void setD(std::vector<double>& d){
                this->d = d;
            }
            void setSe(std::vector<std::vector<double>> se){
                this->se = se;
            }
            void setDelt(double delt){
                this->delt = delt;
            }
            
            std::vector<int>& getNodeList(){
                return nodeList;
            }
            std::vector<double>& getExy(){
                return exy;
            }
            std::vector<double>& getC(){
                return c;
            }
            std::vector<double>& getD(){
                return d;
            }
            std::vector<std::vector<double>>& getSe(){
                return se;
            }
            double getDelt(){
                return delt;
            }
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
            void setNode(std::vector<Node>& node){
                this->node = node;
            }
            void setElem(std::vector<Elem>& elem){
                this->elem = elem;
            }

            int getNpoint(){ return this->npoint; }
            int getNelem(){ return this->nelem; }
            std::vector<Node>& getNode(){
                return node;
            }
            std::vector<Elem>& getElem(){
                return elem;
            }


    };

}

#endif /* !NODE_H */
