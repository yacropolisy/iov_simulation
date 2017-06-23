#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>
#include <sstream>

#include "cell.h"
#include "const.h"
using namespace std;

//セルの座標を設定
void initcell(cood cell[]){
  for(int j=0;j<M;j++){
    if(j%26<13){
      cell[j].x=2*1000*(j%26);
      cell[j].y=2*1732*(j/26);
    }else{
      cell[j].x=1000*(2*(j%13)+1);
      cell[j].y=1732*(2*(j/26)+1);
    }
  }
}

//時刻ｔにおけるタクシーログデータの取り込み
void readlog(cood usercood[],int startid,int N, int h, int t){
  ifstream fin;
  string filename,ss,x,y;
  stringstream stio;
  for(int i=0;i<N;i++){
    filename="splitedID"+to_string(i+startid)+"_"+to_string(h)+".txt";
    fin.open(filename);
    if(!fin){
      cout<<"open error:"<< filename <<endl;
    }
    for(int a=0;a<=t;a++){
      getline(fin,ss);
    }
    stio.str(ss);
    stio >>x >>x >>y; //ファイル中、1列目はtimeなので捨てる
    usercood[i].x=stod(x)+2500;
    usercood[i].y=stod(y)+1000;
    fin.close();
  }
}

void setcell(cood cell[],cood usercood[],int b[],int N){
  double tmp,min;
  int i,j,cellnum;
  for(int i=0;i<N;i++){
    cellnum=-1;
    min=1400000;
    for(int j=0;j<M;j++){
      tmp=(cell[j].x-usercood[i].x)*(cell[j].x-usercood[i].x)+(cell[j].y-usercood[i].y)*(cell[j].y-usercood[i].y);
      if(min>tmp){
        min=tmp;
        cellnum=j;
      }
    }
    b[i]=cellnum;
  }
}

void setnj(vector<int> nj[]){
    int j;
    nj[0].push_back(1);
    nj[0].push_back(13);
    for(j=1;j<12;j++){
      nj[j].push_back(j-1);
      nj[j].push_back(j+1);
      nj[j].push_back(j+12);
      nj[j].push_back(j+13);
    }
    nj[12].push_back(11);
    nj[12].push_back(24);
    nj[12].push_back(25);
    for(j=13;j<78;j++){
      if(j%13==0){  //左端
        if(j%26==0){  //左端奇数
          nj[j].push_back(j+1);
          nj[j].push_back(j+13);
          nj[j].push_back(j-13);
        }else{  //左端偶数
          nj[j].push_back(j+1);
          nj[j].push_back(j+13);
          nj[j].push_back(j+14);
          nj[j].push_back(j-13);
          nj[j].push_back(j-12);
        }
      }else if(j%13==12){ //右端
        if(j%26==12){ //　右端奇数
          nj[j].push_back(j-1);
          nj[j].push_back(j+12);
          nj[j].push_back(j+13);
          nj[j].push_back(j-14);
          nj[j].push_back(j-13);
        }else{  //　右端偶数
          nj[j].push_back(j-1);
          nj[j].push_back(j+13);
          nj[j].push_back(j-13);
        }
      } else if(j%26<13){ //　中央奇数
        nj[j].push_back(j+1);
        nj[j].push_back(j-1);
        nj[j].push_back(j+12);
        nj[j].push_back(j+13);
        nj[j].push_back(j-14);
        nj[j].push_back(j-13);
      } else{ //　中央偶数
        nj[j].push_back(j+1);
        nj[j].push_back(j-1);
        nj[j].push_back(j+13);
        nj[j].push_back(j+14);
        nj[j].push_back(j-13);
        nj[j].push_back(j-12);
      }
    }
    nj[78].push_back(79);
    nj[78].push_back(65);
    for(j=79;j<90;j++){
      nj[j].push_back(j-1);
      nj[j].push_back(j+1);
      nj[j].push_back(j-13);
      nj[j].push_back(j-14);
    }
    nj[90].push_back(76);
    nj[90].push_back(77);
    nj[90].push_back(89);

}
