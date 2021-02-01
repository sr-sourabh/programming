#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

ll a[200007];



int main(){
    int t; cin>>t;
    while(t--){
        int n; cin>>n;
        for(int i = 0 ; i < 2*n; i++){
            cin>>a[i];
        }

        sort(a, a+2*n);
        int ans = 1;
        ll d[n];
        for(int i = 1 ; i < 2*n ; i++){
            if(i % 2 == 0){
                if(a[i] == a[i-1]){
                    ans = 0; break;
                }
            }
            else{
                d[i/2] = a[i];
                if(a[i] != a[i-1]){
                    ans = 0; break;
                }
            }
        }


        if(ans == 1){
            ll sum = 0;
            for(int i = n-1; i > -1; i--){
                ll num = d[i] - sum;
                if(num <= 0 || (num % ((i+1)*2) != 0)){
                    ans = 0; break;
                }
                sum += (num/((i+1)*2)) * 2;
                //cout<<sum<<" ";
            }
        }
        //cout<<endl;
        cout<<(ans? "YES" : "NO")<<endl;

    }


}