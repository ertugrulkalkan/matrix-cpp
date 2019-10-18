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
    matrix<int> a(10,10);
    matrix<int> b(10,10);
    matrix<int> c(10,10);

    /* birim matris */
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
            if(i == j) a[i][j] = 1;
    }

    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
            if(i == j) b[i][j] = 1;
    }
    
    c.resize(5, 5, false);
    
    c = a + b;

    print_mat(a);
    print_mat(c);
    
    b = a * c;
    
    print_mat(b);

    return 0;
}