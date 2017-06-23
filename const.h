#ifndef INCLUDED_const_h
#define INCLUDED_const_h

#define ln2 0.693147
#define T 30
#define M 91
#define Nv 3
#define Lambda 0.01
#define Interval1 60  //通信周期
#define Interval2 10
#define Interval3 30
#define Datasize1 0.001  //user数:500,500 Lamda:0.01 Interval:30の時0.1くらいでトラヒックはサチらない
#define Datasize2 0.1
#define Datasize3 0.005
#define P1 1.0 //全車両に対するそのセンサ車両の割合
#define P2 1.0
#define P3 1.0
#define Alpha1 (ln2/60) //許容遅延、指数減衰の係数
#define Alpha2 (ln2/10)
#define Alpha3 (ln2/300)
#define U0 1  //1の時が程よく反応率が数１０％になる
#define Tave 10  //通信のスループットで移動平均取る時間
#define H 10  //taxiデータの読み込み開始時刻


#endif
