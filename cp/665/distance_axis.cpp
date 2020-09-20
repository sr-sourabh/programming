#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> vl;
typedef pair<int, int> pi;

#define F first
#define S second
#define PB push_back
#define MP make_pair

#define REP(i,a,b) for (int i = a; i < b ; i++)
#define SQ(a) (a)*(a)

void solve(){
    int a, k;
    cin>>a>>k;
    if(a >= k){
        if((a+k) % 2 == 0){
            cout<<"0\n";
            return;
        }
        else{
            cout<<"1\n";
            return;
        }
    }
    else{
        cout<<k-a<<"\n";
        return;
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin>>t;

    while(t--){
        solve();
    }
}
