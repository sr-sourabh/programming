//https://codeforces.com/contest/1478

#include<bits/stdc++.h>
using namespace std;

int main(){
    int t; cin>>t;
    while(t--){
        int n;
        cin>>n;
        int a[n+1] = {0};
        int maxx = 0;
        for(int i = 0 ; i < n ; i++){

            int temp;
            cin>>temp;
            a[temp]++;
            maxx = max(maxx, a[temp]);
        }
        cout<<maxx<<"\n";

    }


}