#include<bits/stdc++.h>
using namespace std;
#include "library/binaryheap.h"

typedef long long ll;

int main(){
    vector<ll> v;
    binaryheap bh = binaryheap(v);

    bh.addKey(10);
    bh.addKey(5);
    bh.addKey(20);
    bh.addKey(4);
    bh.addKey(34);
    bh.addKey(400);
    bh.addKey(82);

    cout<<bh.heap[4]<<endl;
    bh.changeKey(4, 30);

    while(!bh.heap.empty()){
        cout<<bh.pop()<<" ";
    }
    cout<<endl;


    return 0;
}