#ifndef INCLUDED_traffic_h
#define INCLUDED_traffic_h

#include <vector>
#include "const.h"

using namespace std;

//trafficクラス
class traffic{
public:
  int starttime;
  int userid;
};

//celler
class trafficc : public traffic{
public:
  int endtime;
};

//vehicle
class trafficv : public traffic{
public:
  int flag; //待機したかどうか　初期０、待機後１
  double datasize;
  int starttime2;
  void wait(int waittime);
};

void initqc(int qc[][Nc]);
void inittrav(vector<trafficv> *trav);

#endif
