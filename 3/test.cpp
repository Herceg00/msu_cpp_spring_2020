#include <iostream>
#include "matrix.h"
#include <assert.h>
using namespace std;

int main() {
    Matrix m(3,3);
    m[0][1] = 1;
    m[2][2] = 14;
    m.print_matrix();
    Matrix m1(3,4);
    cout<<(m == m1)<<endl;
    //m[0][5] = 8;  program falls:)
    Matrix m2(3,3);
    m2[0][1] = 1;
    m2[2][2] = 14;
    assert(m == m2); //works
    int x = m[2][2];
    cout<<x<<endl;
    m*=4;         //works
    m.print_matrix();
}