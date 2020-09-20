#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include<unordered_map>
using namespace std;
typedef long long ll;

#define mod 1000000007

unordered_map<ll, ll> dp;

ll count(ll n){
    if(n <= 1){
        return 1;
    }
    if(dp.count(n) == 0){
        dp[n] = 0;
        ll start = n-1;
        while(start >= 0){
            dp[n] += count(start) % mod;
            dp[n] %= mod;
            start -= 2;
        }
    }
    return dp[n] % mod ;
}

int main() {
    ll t;
    cin>>t;
    while(t--){
        ll n ;
        cin>>n;
        cout<<count(n%modls
        )<<endl;
    }
    return 0;
}
