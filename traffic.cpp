#include <iostream>
#include <vector>
#include <cmath>

#include "traffic.h"
#include "const.h"
using namespace std;

/*一様乱数生成*/
double Uniform( double max ){
  return max*(double)rand()/((double)RAND_MAX+1.0);
}

void trafficv::wait(int waittime){
  if(flag==0){
    starttime2+=waittime;
    flag=1;
  }
}

void inittrav(vector<trafficv> *trav, double datasize, int interval, double p){
  int t;
  for(int i=0;i<Nv;i++){
    if(Uniform(1.0) <= p){
      trafficv tmptra;
      t=i%interval;
      while(t<T){
        tmptra.starttime=tmptra.starttime2=t;
        tmptra.userid=i;
        tmptra.flag=0;
        tmptra.datasize=datasize;
        trav->push_back(tmptra);
        t+=interval;
      }
    }
  }
}
