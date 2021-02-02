#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int mysize = 200001;
char s1[mysize], f1[mysize];
int tree[4*mysize+1];
int lazy[4*mysize+1];

//count of 1s
void buildtree(int index, int s, int e){
    if(s > e) return;
    if(s == e){
        tree[index] = (f1[s] == '1') ? 1 : 0;
        return;
    }

    int mid = (s+e)/2;
    buildtree(index*2, s, mid);
    buildtree(index*2+1, mid+1, e);
    tree[index] = tree[index*2] + tree[index*2+1];
}

//range update
void update(int index, int s, int e, int rs, int re, int val){
    if(s>e) return;

    if(s==e){
        tree[index] = val;
        return;
    }

    if(e < rs || s > re) return;

    //complete overlap stop after pushing to children
    if(s >= rs && e <= re){
        tree[index] = (val == 1)? (e-s+1) : 0;
        //if non leaf node push the value in lazy to children
        if(s != e){
            lazy[2*index] = val;
            lazy[2*index+1] = val;
        }
        return;
    }

    //partial overlap
    int mid = (s+e)/2;
    update(index*2, s, mid, rs, re, val);
    update(index*2+1, mid+1, e, rs, re, val);
    tree[index] = tree[index*2] + tree[index*2+1];
}

//range query
int query(int index, int s, int e, int qs, int qe){
    if(s>e) return 0;

    if(e<qs || s > qe) return 0;

    //fix lazy if applicable
    if(lazy[index] != -1){
        tree[index] = (lazy[index] == 1)? (e-s+1) : 0;
        if(s != e){
            lazy[index*2] = lazy[index];
            lazy[index*2+1] = lazy[index];
        }
        lazy[index] = -1;
    }

    if(s >= qs && e <= qe) return tree[index];

    int mid = (s+e)/2;
    return query(index*2, s, mid, qs, qe) + query(index*2+1, mid+1, e, qs, qe);
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t; scanf("%d", &t);
    while(t--){
        int n; scanf("%d", &n);
        int q; scanf("%d", &q);
        int a[q], b[q];
        scanf("%s", s1);
        scanf("%s", f1);
        for(int i = 0 ; i < q; i++){
            scanf("%d", &a[i]);
            scanf("%d", &b[i]);
        }

        int index = 1;
        int s = 0;
        int e = n-1;
        memset(tree, 0, sizeof(tree));
        memset(lazy, -1, sizeof(lazy));
        buildtree(index, s, e);

        bool flag = 0;
        for(int i = q-1; i > -1; i--){
            int l = a[i]-1;
            int r = b[i]-1;
            int num = r-l+1;
            int ones = query(index, s, e, l, r);
            int zeros = num - ones;
            //cout<<l<<" "<<r<<" "<<num<<" "<<ones<<endl;
            num /= 2;
            if(ones > num){
                update(index, s, e, l, r, 1);
            }
            else if(zeros > num){
                update(index, s, e, l, r, 0);
            }
            else{
                flag = 1;
                break;
            }
        }

        cout<<(flag? "NO\n": "YES\n");
    }
}