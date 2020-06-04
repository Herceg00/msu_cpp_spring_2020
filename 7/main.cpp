#include <iostream>
#include "custom_vector.h"
#include "cassert"
using namespace std;
int main() {
    Custom_Vector<int> a;
    a.push_back(1);
    int v = a[0];
    cout<<v<<endl;
    size_t size = a.get_size();
    cout<<size<<endl;
    a.push_back(5);
    size = a.get_size();
    cout<<size<<endl;
    cout<<a[1]<<endl;
    a.pop_back();
    size = a.get_size();
    cout<<size<<endl;
    a.push_back(1);
    a.push_back(0);
    a.push_back(0);
    a.push_back(0);
    size = a.get_size();
    cout<<size<<endl;
    a.pop_back();
    a.pop_back();
    a.pop_back();
    a.pop_back();
    a.pop_back();
//    Custom_Iterator<int> it = a.begin();
//    for(it = a.begin(); it!=a.end();++it){
//        cout<<*it<<endl;
//    }
}
