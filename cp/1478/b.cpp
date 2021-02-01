#include<bits/stdc++.h>
using namespace std;

int main(){
    int t; cin>>t;
    bitset<1001> dp;
    while(t--){
        int q, d;
        cin>>q>>d;

        for(int i = 0 ; i < q; i++){
            int x;
            cin>>x;

            int temp = d;
            int flag = 0;
            if(x >= 10*d) flag = 1;
            else{
                while(d<= x){
                    if((x-d) % 10 == 0){
                        flag = 1;
                        break;
                    }
                    x -= d;
                }
            }

            cout<<(flag ? "YES": "NO")<<endl;

        }
    }


}