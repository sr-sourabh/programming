#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

/*
    Q.  Design a data structure to answer the following queries efficently
        (a) Insert an integer to the list.
        (b) Given an integer x, you’re about to find an integer k which rep-
        resent x’s index if the list is sorted in ascending order. Note that
        in this problem we will use 1-based indexing.

    Idea    Implement avl tree with count field.
            Count(x) gives the number of elements in the subtree rooted at x.
            Define a function rank(x) = the number of elements which are smaller than or equal to x in the avl tree.
            This can be used to answer the 2 operation in the question.
            Each query can be answered in O(logn) time which is proportional to height of the tree.

    Example Input
        11
        1 0
        1 100
        1 74
        2 100
        2 70
        1 152
        1 21
        1 33
        2 100
        2 21
        2 1

    Example output (for 1 based index)
        Rank of: 100 = 3
        Rank of: 70 = no
        Rank of: 100 = 5
        Rank of: 21 = 2
        Rank of: 1 = no
*/

struct avl{
    int key;
    struct avl *left;
    struct avl *right;
    int count;
    int height;
};

int Height(avl * root){
    if(root){
        if(root->left != NULL && root->right != NULL){
            return 1 + max(root->left->height ,  root->right->height);
        }
        else if(root->left) return 1 + root->left->height;
        else if (root->right) return 1 + root->right->height;
        else return 0;
    }
    else{
        return -1;
    }
}

int Count(avl * root){
    if(root){
        if(root->left != NULL && root->right != NULL){
            return 1 + root->left->count + root->right->count;
        }
        else if(root->left) return 1 + root->left->count;
        else if (root->right) return 1 + root->right->count;
        else return 1;
    }
    else{
        return 0;
    }
}

bool isImbalanced(avl * root){
    if(abs(Height(root->left) - Height(root->right)) > 1) return true;
    else return false;
}

avl * rotate(avl * root){
    //z -- y -- x
    int c = 0;
    avl *y;
    avl *z = root;
    if(Height(z->left) + 1 == z->height) y = z->left;
    else {
        y = z->right;
        c = c+1;
    }

    c = c * 2;

    avl *x;
    if(Height(y->left) + 1 == y->height) x = y->left;
    else{
        x = y->right;
        c = c + 1;
    }

    if(c==0){
        //cout<<"left-left"<<endl;
        avl * t2 = y->right;
        y->right = z;
        z->left = t2;

        z->height = Height(z);
        x->height = Height(x);
        y->height = Height(y);

        z->count = Count(z);
        x->count = Count(x);
        y->count = Count(y);

        root = y;
    }
    else if(c==1){
        //cout<<"left-right"<<endl;
        avl * t3 = x->left;
        avl *t4 = x->right;
        y->right = t3;
        z->left = t4;
        x->left = y;
        x->right = z;

        z->height = Height(z);
        y->height = Height(y);
        x->height = Height(x);

        z->count = Count(z);
        y->count = Count(y);
        x->count = Count(x);

        root = x;
    }
    else if(c==2){
        //cout<<"right-left"<<endl;
        avl *t3 = x->left;
        avl *t4 = x->right;
        x->left = z;
        x->right = y;
        z->right = t3;
        y->left = t4;

        z->height = Height(z);
        y->height = Height(y);
        x->height = Height(x);

        z->count = Count(z);
        y->count = Count(y);
        x->count = Count(x);

        root = x;
    }
    else if( c== 3){
        //cout<<"right-right"<<endl;
        avl *t2 = y->left;
        y->left = z;
        z->right = t2;

        z->height = Height(z);
        x->height = Height(x);
        y->height = Height(y);

        z->count = Count(z);
        x->count = Count(x);
        y->count = Count(y);

        root = y;
    }

    return root;
}

struct avl * insert(struct avl * root, int key){
    if(root == NULL){
        avl *newNode = new avl;
        newNode->key = key;
        newNode->left = newNode->right = NULL;
        newNode->height = 0;
        newNode->count = 1;
        return newNode;
    }

    if(key > root->key){
        root->count++;
        root->right = insert(root->right, key);
    }
    else if(key < root->key){
        root->count++;
        root->left = insert(root->left, key);
    }

    root->height = Height(root);

    if(isImbalanced(root)){
        //cout<<"Imbalance at: "<<root->key<<endl;
        root = rotate(root);
    }

    return root;
}

string Rank(avl *root, int key){
    int rank = 1;
    while(root){
        if(root->key == key){
            rank += Count(root->left);
            return to_string(rank);
        }
        else if(key > root->key){
            rank = rank + Count(root->left) + 1;
            root = root->right;
        }
        else{
            root = root->left;
        }
    }
    return "no";
}

void inorder(avl * root){
    if(root != NULL){
        inorder(root->left);
        cout<<root->key<<"\t"<<root->height<<"\t"<<root->count<<endl;
        inorder(root->right);
    }
}

int main(){
    int t;
    cin>>t;

    avl *root = NULL;

    while(t--){
        int operation;
        int val;
        cin>>operation>>val;

        if(operation == 1){
            root = insert(root, val);
        }

        if(operation == 2){
            cout<<endl<<"Rank of: "<<val<<" = "<<Rank(root, val);
        }
    }

    //inorder(root);
    return 0;

}