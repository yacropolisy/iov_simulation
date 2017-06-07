#include <iostream>
#include <vector>
#include <string>

#include "eval.h"
#include "traffic.h"
#include "const.h"

using namespace std;

int eval(vector<trafficc> &trac, int dave[][Tave],int bc[], int now){
  int k,sum,t,stopcount=0,count;
  for(k=0; k<trac.size(); k++){
    sum = 0;
    count = 0;
    if(trac[k].starttime >= now || trac[k].endtime < now){
      continue;
    }
    for(t = now - 9; t <= now; t++){
      if(trac[k].starttime <= t){
        sum += dave[bc[trac[k].userid]][t%Tave];
        count++;
      }
    }
    if(dave[bc[trac[k].userid]][now%Tave] > sum/double(count)*Stoprate){
      stopcount++;
    }
  }
  return stopcount;
}
