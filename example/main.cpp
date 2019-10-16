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

int main()
{   
    matrix<int> a(10,10);

    /* birim matris */
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++)
            if(i == j) a[i][j] = 1;
    }
    print_mat(a);

    a.resize(10, 5, true);
    print_mat(a);

    a.resize(5, 5, true);
    print_mat(a);

    a.resize(10,10, true);
    print_mat(a);

    return 0;
}