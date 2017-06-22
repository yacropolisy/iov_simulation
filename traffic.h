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
  int starttime2; //待機した時にこの値を現在時刻＋Waittimeにする
  void wait(int waittime);  //waittimeだけ通信待機
  double alpha; //許容遅延、指数減衰モデルにおける減衰係数
};

void inittrac(vector<trafficc> *trac);
void initqc(int qc[][Nc], vector<trafficc> &trac);
void inittrav(vector<trafficv> *trav, int datasize, int interval);
double Uniform( double max );

#endif
