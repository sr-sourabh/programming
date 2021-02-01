#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

ll gcd(ll x, ll y){
    if(y == 0) return x;
    return gcd(y, x%y);
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t; cin>>t;
    while(t--){
        int n; cin>>n;
        ll k; cin>>k;

        ll a[n];
        string ans = "NO\n";

        cin>>a[0];
        if(n==1){
            if(k % a[0] == 0){
                cout<<"YES\n";
            }
            else{
                cout<<"NO\n";
            }
            continue;
        }

        for(int i = 1 ; i < n ; i++){
            cin>>a[i];
            a[i] -= a[0];
        }

        ll gcdd = a[1];
        for(int i = 2 ; i < n; i++){
            gcdd = gcd(gcdd, a[i]);
        }

        if((k-a[0]) % gcdd == 0){
            ans = "YES\n";
        }

        cout<<ans;
    }
}