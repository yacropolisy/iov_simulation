#ifndef INCLUDED_control_h
#define INCLUDED_control_h

#include <deque>

#include "const.h"
#include "traffic.h"
using namespace std;

void control(vector<trafficv> &copytra, int qc[],int bc[],int bv[],vector<int> nj[],int t,int waittime,double alpha, int dave[][Tave]);
#endif
