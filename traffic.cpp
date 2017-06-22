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

void inittrav(vector<trafficv> *trav, double datasize, int interval){
  int t;
  for(int i=0;i<Nv;i++){
    trafficv tmptra;
    t=i%interval;
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
