#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <ctime>
#include <string>
#include <sstream>
#include <deque>

#include "cell.h"
#include "traffic.h"
#include "control.h"
#include "const.h"

using namespace std;
int main(){
  int t,j;
  int h = H;
  int waittime;
  int dave[M][Tave];
  ofstream fout;
  string filename;

  //トラヒックの発生、Cellerはqc、Vehicleはtrav  =>traffic.cpp
  vector<trafficv> trav1,trav2,trav3;
  inittrav(&trav1, Datasize1, Interval1, P1);
  inittrav(&trav2, Datasize2, Interval2, P2);
  inittrav(&trav3, Datasize3, Interval3, P3);
  //基地局の配置 =>cell.cpp
  cood cell[M];
  initcell(cell);
  vector<int> nj[M];
  setnj(nj);

  //ログデータ読み込み、ユーザの位置入手用
  cood uv[Nv];
  int bv[Nv];

  //待機時間変えて結果取得
  for(waittime=0;waittime<60;waittime+=30){
    filename = "stop_w:"+to_string(waittime)+".csv";
    fout.open(filename);
    //waittimeでループするためのtravのバックップ
    vector<trafficv> copytra1, copytra2, copytra3;
    copytra1 = trav1;
    copytra2 = trav2;
    copytra3 = trav3;
    //dave初期化
    for(t=0; t<Tave; t++){
      for(j=0;j<M ;j++){
        dave[j][t]=0;
      }
    }
    //制御時刻開始
    for(t=0;t<T;t++){
      //logデータ読み込んでユーザの位置を入手 =>cell.cpp
      readlog(uv,0,Nv,h,t);
      setcell(cell,uv,bv,Nv);
      //制御 =>control.cpp
      control(copytra1, copytra2, copytra3, bv, nj, t, waittime, dave);
    }
    fout << endl;
    fout.close();
  }
  return 0;
}
