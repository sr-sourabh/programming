//count of 1s in string and range update to all 1s or 0s using lazy propagation
//modify as required

const int mysize = 200001;
string s1, f1;
ll tree[4*mysize+2];
ll lazy[4*mysize+2];

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

    if(lazy[index] != -1){
        tree[index] = (lazy[index] == 1) ? (e-s+1) : 0;
        if(s != e){
            lazy[2*index+1] = lazy[index];
            lazy[2*index] = lazy[index];
        }
        lazy[index] = -1;
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
ll query(int index, int s, int e, int qs, int qe){
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