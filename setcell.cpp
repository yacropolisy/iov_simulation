#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
#include <sstream>
using namespace std;
const int T=100;
const int N=20;
const int M=91;


int setcell(double x, double y, double cellx[],double celly[]){
  double min=1400000;
  double tmp;
  int cellnum=-1;
  for(int j=0;j<M;j++){
    tmp=(cellx[j]-x)*(cellx[j]-x)+(celly[j]-y)*(celly[j]-y);
    if(min>tmp){
      min=tmp;
      cellnum=j;
    }
  }
  return cellnum;
}

int main(){

  /*
    vector<int> nj[100];
    for(int j=0;j<100;j++){
      for(int jj=0;jj<100;jj++){
        kyori=(x[j]-x[jj])*(x[j]-x[jj])+(y[j]-y[jj])*(y[j]-y[jj]);
        if(kyori<9000){
          nj[j].push_back(j)
        }
      }

    }
    cout << n[0][4]<<endl;
    cout << n[1][4]<<endl;
  */
  vector<int> nj[M];
  double x[M],y[M];
  int i,j,t;
  int a[N][M][T]={0};
  int b[N][T];
  for(j=0;j<M;j++){
    if(j%26<13){
      x[j]=2*1000*(j%26);
      y[j]=2*1732*(j/26);
    }else{
      x[j]=1000*(2*(j%13)+1);
      y[j]=1732*(2*(j/26)+1);
    }
  }

//nj[M]設定

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
  for(j=79;j<91;j++){
    nj[j].push_back(j-1);
    nj[j].push_back(j+1);
    nj[j].push_back(j-13);
    nj[j].push_back(j-14);
  }
  nj[90].push_back(76);
  nj[90].push_back(77);
  nj[90].push_back(89);

  //debug
  int test=42;
  for(int testi=0;testi<nj[test].size();testi++){
    cout<<nj[test][testi]<<endl;
  }

  //debug
  for(j=0;j<M;j++){
    cout<<x[j]<<","<<y[j]<<" ";
  }
  cout <<endl;
  //debugend

  string filename;
  int filenum=1;
  ifstream fin;
  string ss;
  string tmp;
  string ax;
  string ay;
  string aho;
  double bx,by;
  for(i=0;i<N;i++){
    filenum=i+1;
    filename="formatedID"+to_string(filenum)+".txt";
    fin.open(filename);
    for(int t=0;t<T;t++){
      getline(fin,ss);
      stringstream data(ss);
      getline(data,tmp,' ');
      getline(data,ax,' ');
      getline(data,ay,' ');
      bx=stod(ax);
      by=stod(ay);
      b[i][t]=setcell(bx+1500,by+1000,x,y);
      for(int w=0;w<9;w++){
        getline(fin,ss);
      }

    }
    fin.close();
  }
  for(i=0;i<N;i++){
    for(t=0;t<T;t++){
      if(b[i][t]!=-1){
        a[i][b[i][t]][t]=1;
      }
    }
  }
  return 0;
}
