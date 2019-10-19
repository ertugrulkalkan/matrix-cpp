#include <iostream>
#include "../matrix.h"
using namespace std;

void print_mat(matrix<int> &tp)
{
  for(int i = 0; i < tp.getRowC(); i++)
  {
    for(int j = 0; j < tp.getColC(); j++)
      cout << tp[i][j] << ",";
    cout << endl;
  }
  cout << endl;
}

void print_mat(matrix<double> &tp)
{
  for(int i = 0; i < tp.getRowC(); i++)
  {
    for(int j = 0; j < tp.getColC(); j++)
      cout << tp[i][j] << ",\t";
    cout << endl;
  }
  cout << endl;
}

int main()
{   
  matrix<double> b(3,4);
  
  b[0][0] = 5.2;
  b[0][1] = 4.5;
  b[0][2] = 70.55;
  b[0][3] = 90.0;

  b[1][0] = 120;
  b[1][1] = -50;
  b[1][2] = 40;
  b[1][3] = -14;

  b[2][0] = -4;
  b[2][1] = 3;
  b[2][2] = 22;
  b[2][3] = -20;

  matrix<double> c(b);
  matrix<double> a(b);
  
  a.transpose();
  
  c = (a * b);
  cout<< (c.det()) << endl;

  return 0;
}