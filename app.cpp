/*
 * This C++ source file was generated by the Gradle 'init' task.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <typeinfo>
#include <eigen3/Eigen/Core>
// #include "app.h"
#include "node.h"
#include "PhysicalConstant.h"
#include "Dirichlet.h"
#include "Afield.h"

void he(int num = 1){
    std::cout << "hello" << num << std::endl;
}

void view(fem::Field &A){
    for(int i=0; i<5; i++){
        std::cout << i << ":";
        for(int j=0; j<3; j++){
            std::cout << A.elem[i].nodeList[j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    for(int i=0; i<7; i++){
        std::cout << i << ":";
        for(int j=0; j<2; j++){
            std::cout << A.node[i].xy[j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int main () {

    fem::Afield A;
    std::ifstream ifs("file1.txt");


    int npoint = 0; //節点の総数
    int nelem = 0; //要素の総数
    ifs >> npoint >> nelem;
    A.setNpoint(npoint);
    A.setNelem(nelem);

    for(int i=0; i<A.getNelem(); i++){
        for(int j=0; j<3; j++){
            int temp = 0; ifs >> temp;
            A.elem[i].nodeList[j] = temp - 1;
        }
    }

    for(int i=0; i<A.getNpoint(); i++){
        for(int j=0; j<2; j++){
            ifs >> A.node[i].xy[j];
        }
    }

    view(A);

    //// 節点及び要素に関するデータ
    int ncheck = 0;
    int nboun = 0;
    int nband = 0;
    int ndiri = 0;
    int ncur = 0;
    int ihs = 0;
    int ihe = 0;
    double peam = 1000.0;

	ifs >> ncheck;
	ifs >> nboun >> nband >> ndiri >> ncur >> ihs >> ihe;
	ifs >> peam;

    // #TODO
    A.setPhysicalConstant(1.0, peam, ihs, ihe);
    // A.physicalConstant.setIhs(ihs);
    // A.physicalConstant.setIhe(ihe);
    // A.physicalConstant.setPeam(peam);//peamしたら必ずupdateする必要があるので捜査としては分離するが, 関数としては組み込む
    // A.setEh(A.getEair()/A.getPeam());

    // A.updateEh();
    // A.setEh();

    // A.physicalConstant.setNdiri(ndiri);

    // TODO
    for(int i=0; i < A.getDirichlet().getNdiri(); i++){
        int temp_ndis, temp_ndie , temp_diri = 0;
        // ifs >> A.ndis[i] >> A.ndie[i];
        // ifs >> A.diri[i];
        ifs >> temp_ndis >> temp_ndie;
        ifs >> temp_diri;
        A.getDirichlet().getNdis().push_back(temp_ndis);
        A.getDirichlet().getNdie().push_back(temp_ndie);
        A.getDirichlet().getDiri().push_back(temp_diri);
    }

    // TODO
    ifs >> fem::Elem::delmax;
    ifs >> fem::Elem::delmin;

	///////////////////////////// ここまでデータ入力

    //// 各要素の材料定数の設定
    //c d deltの計算
    A.calcElem();

    //// 要素係数マトリクスの計算
    A.calcElemMatrix();

    //// 固定境界条件の設定
    for(int i=0; i<A.getDirichlet().getNdiri(); i++){
        for(int j=A.getDirichlet().getNdis()[i]; j<A.getDirichlet().getNdie()[i]; j++){
            A.node[j].v = A.getDirichlet().getDiri()[i];
        }
    }

    ////電流項の計算
    //double ce = 0;
    //if( ncur > 0 ){
    //    for(int i=0; i<ncur; i++){
    //        for(int j=ncus[i]; j<ncue[i]; j++){
    //            ce = cur[i]*delt[j]/3.0;
    //        }
    //        for(int k=0; k<3; k++){
    //            if( nod[j][k] <= np ){
    //                v[nod[j][k]] += ce;
    //            }
    //        }
    //    }
    //}

    //std::vector<std::vector<double>> h;

    //h.resize(npoint);
    //for(int i=0; i<npoint; i++){
    //    h[i].resize(npoint);
    //}

    ////全体係数マトリクスの計算
    //coefMtrx(np, nband, h, v, nelem, npoint, nod, se);

    A.calcCoefMatrix();

    for(int i=0; i<A.getNpoint(); i++){
        for(int j=0; j<A.getNpoint(); j++){
            std::cout << A.h[i][j] << " ";
        }
        std::cout << std::endl;
    }


    ////連立1次方程式の計算
    //gsseq(h, v, nk, np, nband, npoint);

    //// 磁束密度の計算
    //std::vector<double> bx;
    //std::vector<double> by;
    //std::vector<double> bamp;

    //bx.resize(nelem);
    //bx.resize(nelem);
    //bamp.resize(nelem);
    //flux(nelem, nod, c, d, v, bx, by, bamp, delt, npoint);

    //// 計算結果の出力
    //for(int i=0; i<npoint; i++){
    //    std::cout << i << " " << v[i] << std::endl;
    //}

    //for(int i=0; i<nelem; i++){
    //    std::cout << i " " << bx[i] << " " << by[i] << " " << bamp[i] << std::endl;
    //}

    return 0;

}
