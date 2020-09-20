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
    int x1, y1, z1;
    int x2, y2, z2;
    cin>>x1>>y1>>z1>>x2>>y2>>z2;

    if(x1 >= z2 ){
        x1 = x1 - z2;
        z2 = 0;
        if(x1 >= x2){
            x1 = x1 - x2;
            x2 = 0;

            cout<<(y2 - x1 - y1) * 2<<"\n";
            return;

        }
        else{
            x2 = x2 - x1;
            x1 = 0;
            if(y1 > x2){
                cout<<(y2 - (y1-x2))*2<<"\n";
                return;
            }
            else{
                cout<<y2*2<<"\n";
                return;
            }
        }
    }
    else{
        x1 = 0;
        z2 = z2 - x1;
        if(y1 >= x2){
            y1 = y1 - x2;
            x2 = 0;
            if(y1 >= y2){
                cout<<(y1 - y2) * (-2)<<"\n";
                return;
            }
            else{
                cout<<2*(y2-y1)<<"\n";
                return;
            }
        }
        else{
            x2 = x2 - y1;
            y1 = 0;
            cout<<2*y2<<"\n";
            return;

        }

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
