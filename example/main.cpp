#include <iostream>
#include "../matrix.h"
using namespace std;

void print_mat(matrix<int> &tp)
{
    for(int i = 0; i < tp.getRowC(); i++){
        for(int j = 0; j < tp.getColC(); j++)
            cout << tp[i][j];
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
    matrix<int> b(4,3);

    /* birim matris */
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 3; j++)
            b[i][j] = i+j;
    }

    cout << "b" << endl;
    b.transpose();
    print_mat(b);

    b.transpose();
    print_mat(b);
    
    matrix<int> a = b.submatrix(b,1,1);

    print_mat(a);
    return 0;
}