#ifndef INCLUDED_cell_h
#define INCLUDED_cell_h

#include <vector>

using namespace std;
struct cood{
  double x;
  double y;
};
void initcell(cood cell[]);
void readlog(cood usercood[],int startid,int N,int t);
void setcell(cood cell[],cood user[],int b[],int N);
void setnj(vector<int> nj[]);

#endif
