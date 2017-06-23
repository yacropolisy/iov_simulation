#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <deque>

#include "control.h"
#include "const.h"
#include "traffic.h"

using namespace std;


//反応率計算
double calpr(int D, double datasize, int st, int t, int waittime, double alpha){
  double a,b;
  a=exp(U0*exp(-alpha*(int(D*datasize)+t+waittime-st)));
  b=exp(U0*exp(-alpha*(int(D*datasize)+t-st)));
  return a/(a+b);
}

//制御関数f
void f(vector<trafficv> &copytra1, vector<trafficv> &copytra2, vector<trafficv> &copytra3, int D[],int bv[],vector<int> nj[],int t,int waittime){
  double f;
  int i,j,k;
    for(j=0;j<M;j++){
      f=0;
      //周囲の混雑度を合計
      for(i=0;i<nj[j].size();i++){
        f+=D[nj[j][i]];
      }
      //自分の基地局と比較
      if(f/nj[j].size()*1.5<D[j]&&(D[j]-f/nj[j].size())>=10){ //周囲の混雑度より1.5倍かつ１０以上多いなら制御実行
        for(k=0;k<copytra1.size();k++){
          if(bv[copytra1[k].userid]==j){
            if(Uniform(1.0)<calpr(D[j],copytra1[k].datasize, copytra1[k].starttime, t, waittime, Alpha1)){
              copytra1[k].wait(waittime);
            }
          }
        }
        for(k=0;k<copytra2.size();k++){
          if(bv[copytra2[k].userid]==j){
            if(Uniform(1.0)<calpr(D[j],copytra2[k].datasize, copytra2[k].starttime, t, waittime, Alpha2)){
              copytra2[k].wait(waittime);
            }
          }
        }
        for(k=0;k<copytra3.size();k++){
          if(bv[copytra3[k].userid]==j){
            if(Uniform(1.0)<calpr(D[j],copytra3[k].datasize, copytra3[k].starttime, t, waittime, Alpha3)){
              copytra3[k].wait(waittime);
            }
          }
        }
      }
    }
  }

void control(vector<trafficv> &copytra1, vector<trafficv> &copytra2, vector<trafficv> &copytra3, int bv[],vector<int> nj[],int t,int waittime, int dave[][Tave]){
  int i,j,k,l,L,Kv1, Kv2, Kv3;
  Kv1=copytra1.size();
  Kv2=copytra2.size();
  Kv3=copytra3.size();
  int D[M];
  ofstream fout;
  string outfile;
  //出力用ファイルオープン
  outfile="D_wt"+to_string(waittime)+".csv";
  fout.open(outfile,ios::app);

  //Vehicleの通信端末数計算
  for(j=0;j<M;j++){
    l=0;
    for(k=0;k<Kv1;k++){
    if(t>=copytra1[k].starttime2&&copytra1[k].datasize>0&&bv[copytra1[k].userid]==j){
        l++;
      }
    }
    for(k=0;k<Kv2;k++){
    if(t>=copytra2[k].starttime2&&copytra2[k].datasize>0&&bv[copytra2[k].userid]==j){
        l++;
      }
    }
    for(k=0;k<Kv3;k++){
    if(t>=copytra3[k].starttime2&&copytra3[k].datasize>0&&bv[copytra3[k].userid]==j){
        l++;
      }
    }
    //混雑度計算
    L=l;
    D[j]=L;
    //Vehicleの計算処理
    for(k=0;k<Kv1;k++){
      if(t>=copytra1[k].starttime2&&copytra1[k].datasize>0&&bv[copytra1[k].userid]==j){
        copytra1[k].datasize -= 1.0/D[j];
        copytra1[k].starttime2++;
      }
    }
    for(k=0;k<Kv2;k++){
      if(t>=copytra2[k].starttime2&&copytra2[k].datasize>0&&bv[copytra2[k].userid]==j){
        copytra2[k].datasize -= 1.0/D[j];
        copytra2[k].starttime2++;
      }
    }
    for(k=0;k<Kv3;k++){
      if(t>=copytra3[k].starttime2&&copytra3[k].datasize>0&&bv[copytra3[k].userid]==j){
        copytra3[k].datasize -= 1.0/D[j];
        copytra3[k].starttime2++;
      }
    }
  }

  //制御判定
  if(waittime!=0){
    f(copytra1,copytra2,copytra3,D,bv,nj,t,waittime);
  }

  //dave更新
  for(j=0; j<M; j++){
    dave[j][t%Tave]=D[j];
  }

  //record
  for(j=0;j<M;j++){
    fout<<D[j]<<",";
  }
  fout<<endl;
  //recorded
  fout.close();
}
