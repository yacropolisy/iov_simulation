#ifndef INCLUDED_control_h
#define INCLUDED_control_h

#include <deque>

#include "const.h"
#include "traffic.h"
using namespace std;

void control(vector<trafficv> &copytra1, vector<trafficv> &copytra2, vector<trafficv> &copytra3, int bv[],vector<int> nj[],int t,int waittime, int dave[][Tave]);
#endif
