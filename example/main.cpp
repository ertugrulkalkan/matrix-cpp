#include <iostream>
#include "../matrix.h"
using namespace std;

void print_mat(matrix<int> &tp)
{
    for(int i = 0; i < tp.getRowC(); i++){
        for(int j = 0; j < tp.getColC(); j++)
            cout << tp[i][j] << ",";
        cout << endl;
    }
    cout << endl;
}

void print_mat(matrix<double> &tp)
{
    for(int i = 0; i < tp.getRowC(); i++){
        for(int j = 0; j < tp.getColC(); j++)
            cout << tp[i][j];
        cout << endl;
    }
    cout << endl;
}

int main()
{   
    matrix<int> b(4,4);

    int dt;
    
    b[0][0] = 5;
    b[0][1] = 4;
    b[0][2] = 7;
    b[0][3] = 9;

    b[1][0] = 12;
    b[1][1] = -5;
    b[1][2] = 4;
    b[1][3] = -45;

    b[2][0] = -4;
    b[2][1] = 3;
    b[2][2] = 22;
    b[2][3] = -20;
    
    b[3][0] = -6;
    b[3][1] = -3;
    b[3][2] = 220;
    b[3][3] = -50;
    

    dt = b.det();
    print_mat(b);
    cout << dt << endl;

    return 0;
}