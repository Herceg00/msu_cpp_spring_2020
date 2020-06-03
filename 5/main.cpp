#include <iostream>
#include "BigInt.h"

using namespace std;
int main() {
    BigInt a(554);
    BigInt b(-655);
    BigInt c = a + b;
    cout<<c<<endl;
    BigInt d(678);
    BigInt e(123);
    BigInt f = d - e;
    cout<<f<<endl;
    BigInt g = a;
    cout << g <<endl;
    BigInt h = -a;
    cout << h <<endl;
    BigInt i(100);
    BigInt j(123);
    BigInt k = i - j;
    cout << k <<endl;
    BigInt m(100);
    BigInt n(3);
    BigInt o = n - m;
    cout << o <<endl;




}
