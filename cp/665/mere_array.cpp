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

void swap(vector<ll>& v, ll i , ll j){
    ll temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

void solve(){
    int n ;
    cin>>n;

    vl v(n);

    ll small = LLONG_MAX;
    REP(i, 0 , n){
        cin>>v[i];
        if(v[i] < small){
            small = v[i];
        }
    }

    vl sep;
    REP(i, 0 , n){
        if(v[i] % small == 0){
            sep.PB(v[i]);
            v[i] = -1;
        }
    }
    sort(sep.begin(), sep.end());

    ll c = 0;
    REP(i, 0 , n){
        if(v[i] == -1){
            v[i] = sep[c++];
        }
    }

    bool flag = true;
    REP(i, 1 , n ){
        if(v[i] < v[i-1]){
            flag = false;
            break;
        }
    }
    if(flag){
        cout<<"YES\n";
    }
    else{
        cout<<"NO\n";
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
