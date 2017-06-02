#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <ctime>
#include <string>
#include <sstream>

#include "cell.h"
#include "traffic.h"
#include "control.h"
#include "const.h"

using namespace std;
int main(){
  int i,j,t,k,l,L,Kv;
  int waittime;

  //トラヒックの発生、Cellerはqc、Vehicleはtrav  =>traffic.cpp
  int qc[T][Nc]={0};
  initqc(qc);
  vector<trafficv> trav;
  inittrav(&trav);


  //基地局の配置 =>cell.cpp
  cood cell[M];
  initcell(cell);
  vector<int> nj[M];
  setnj(nj);


  //ログデータ読み込み、ユーザの位置入手用
  cood uc[Nc],uv[Nv];
  int bc[Nc],bv[Nv];



  //混雑度
  int Dc[M],D[M];
  //待機時間変えて結果取得
  for(waittime=0;waittime<600;waittime+=30){
    //制御時刻開始
    for(t=0;t<T;t++){
      //Dc初期化
      for(j=0;j<M;j++){
        Dc[j]=0;
      }

      //logデータ読み込んでユーザの位置を入手 =>cell.cpp
      readlog(uc,0,Nc,t);
      readlog(uv,Nc,Nv,t);
      setcell(cell,uc,bc,Nc);
      setcell(cell,uv,bv,Nv);
      //制御
      control(trav, &qc[t][0],bc,bv,nj,t,waittime);
    }
  }


  return 0;
}
