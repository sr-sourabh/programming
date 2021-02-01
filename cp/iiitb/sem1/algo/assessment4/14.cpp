#include<iostream>
#include<limits.h>
#include<algorithm>
#include<vector>
#include<unordered_map>
#include<queue>
#include <utility>

using namespace std;

typedef long long ll;

#define MAXN 1000002
ll n, m , k;
bool visited[MAXN];

struct disjointinfo{
    ll parentu;
    ll parentv;
    bool isdisjoint;
};

//Disjoint union data structure
class disjointunion{
    public:
        vector<ll> parent;
        vector<ll> height;
    
    disjointunion(ll n){
        parent.resize(n);
        height.resize(n);
        for(int i = 0; i < n; i++){
            parent[i] = i;
            height[i] = 0;
        }
    }

    //finds the rot of the tree
    ll find(ll i){
        if(parent[i] == i) return i;
        else return find(parent[i]);
    }

    disjointinfo isdisjoint(ll u, ll v){
        ll parentu = find(u);
        ll parentv = find(v);
        return {parentu, parentv, parentu != parentv};
    }

    //accepts 2 roots.
    //we assume that union is called after isdisjoint which gives us the parent
    //therefore this will take O(1) time
    void dounion(ll root1, ll root2){
        if(height[root1] > height[root2]){
            parent[root2] = root1;
        }
        else{
            parent[root1] = root2;
        }
        if(height[root1] == height[root2]){
            height[root2]++;
        }
    }

};

int main(){

    cin>>n>>m>>k;

    //vector element = {cost, {u, v}}
    vector<pair<ll, pair<ll,ll>>> edges;
    for(int i = 0 ; i < m; i++){
        ll u, v, c;
        cin>>u>>v>>c;
        edges.push_back({c, {u, v}});
        visited[u] = 1;
        visited[v] = 1;
    }

    for(int i = 1 ; i <= n; i++){
        if(visited[i] == 0)
        {
            cout<<-1;
            exit(0);
        }
    }

    sort(edges.begin(), edges.end());

    vector<ll> dis;
    int i = 0;
    disjointunion set = disjointunion(n+1);
    while( i < m && dis.size() != n-1){
        ll cost = edges[i].first;
        ll u = edges[i].second.first;
        ll v = edges[i].second.second;

        disjointinfo info = set.isdisjoint(u, v);

        if(info.isdisjoint){
            set.dounion(info.parentu, info.parentv);
            dis.push_back(cost);
        }
        i++;
    }

    sort(dis.begin(), dis.end(), greater<ll>());
    ll ans = 0;
    ll sum = 0;
    for(ll i = 0 ; i < dis.size(); i++){
        sum += dis[i];
    }

    i = 0;
    while(sum > k && i < dis.size()){
        sum = sum - dis[i] + 1;
        ans++;
        i++;
    }

    ans = sum > k ? -1 : ans;
    ans = dis.size() != (n-1) ? -1 : ans;
    cout<<ans<<endl;
    
    cout<<k<<endl<<sum<<endl<<dis.size()<<endl<<i;

    //for(int i = 1 ; i<= n ; i++) cout<<dis[i]<<" ";
    
    return 0;
}
