#include <iostream>
#include <vector>
#include <cmath>

#include "traffic.h"
#include "const.h"
using namespace std;

void trafficv::wait(int waittime){
  if(flag==0){
    starttime2+=waittime;
    flag=1;
  }
}

/*一様乱数生成*/
double Uniform( double max ){
  return max*(double)rand()/((double)RAND_MAX+1.0);
}
/*指数分布生成*/
double randexp( double lambda ){
   return -log(Uniform(1.0))/lambda;
}

//lambda    時間変動可能なように
double lambda(int t0){
  return Lambda;
}
//Vehicleの次のトラヒックの発生時刻
int nexttime(int t0){
  return t0+int(randexp(lambda(t0)));
}


/*YouTubeの動画長分布*/
double youtube(double x){
    double result=0;
    double a0=5.813*pow(10.0,-2.0);
    double a1=2.747*pow(10.0,-3.0);
    double a2=2.082*pow(10.0,-5.0);
    double b0=2.318*pow(10.0,-3.0);
    double b1=2.088*pow(10.0,-5.0);

    result = (a1-a0*b0 +(2*a2-2.0*a0*b1)*x+(a2*b0-a1*b1)*x*x)/((1.0+b0*x+b1*x*x)*(1.0+b0*x+b1*x*x));

    return result;
}

/*トラヒック長の決定*/
int maketrafficlength(){
  while(1){
    int a;
    a=1+rand()%(3000);  //1~3000秒のトラヒック発生

    double b;
    b=0.0035*Uniform(1.0);

    double line=youtube(a);
    if(line>=b){
      return a;
      break;
    }
  }
}

void initqc(int qc[][Nc]){
  vector<trafficc> trac;
  trafficc tmptra;
  int t;
  for(int i=0;i<Nc;i++){
    t=0;
    while(t<T){
      t=nexttime(t);
      if(t>=T){
        break;
      }
      tmptra.starttime=t;
      tmptra.userid=i;
      tmptra.endtime=t+maketrafficlength();
      trac.push_back(tmptra);
    }
  }
  for(int k=0;k<trac.size();k++){
    for(t=trac[k].starttime;t<trac[k].endtime;t++){
      if(t<T){
        qc[t][trac[k].userid]=1;
      }
    }
  }
}

void inittrav(vector<trafficv> *trav){
  int t;
  for(int i=0;i<Nv;i++){
    trafficv tmptra;
    t=i%Interval;
    while(t<T){
      tmptra.starttime=tmptra.starttime2=t;
      tmptra.userid=i;
      tmptra.flag=0;
      tmptra.datasize=Datasize;
      trav->push_back(tmptra);
      t+=Interval;
    }
  }
}
