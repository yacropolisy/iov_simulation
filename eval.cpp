#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
#include <deque>

#include "eval.h"
#include "traffic.h"

using namespace std;

void eval(vector<trafficc> &trac, deque<int> &dave,int bc[], int now){
  int k,j,sum,t,stopcount;
  for(k=0; k<trac.size(); k++){
    sum = 0;
    if(trac[k].starttime >= now || trac[k].endtime < now){
      break;
    }
    for(t = 9; t >= 0; t--){
      if(trac[k].starttime <= now - t){
        dave[1];
        sum += dave[bc[trac[k].userid]][t];
    }

    }
  }
}
