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
  matrix<double> b(3,3);
  
  b[0][0] = 1;
  b[0][1] = 0;
  b[0][2] = 0;

  b[1][0] = 0;
  b[1][1] = -3;
  b[1][2] = 0;

  b[2][0] = 0;
  b[2][1] = 0;
  b[2][2] = -2;

  matrix<double> c(b);
  matrix<double> a(b);
  
  print_mat(a);
  //a.cofactor();
  b = a.getInverse();
  print_mat(b);

  b *= 23.2;
  print_mat(b);

  b += 1.5;
  print_mat(b);

  b -= 1.5;
  print_mat(b);

  return 0;
}