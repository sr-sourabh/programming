#include<bits/stdc++.h>
using namespace std;

int minSwap(vector<int>& a, vector<int>& b) {
    
    int swap[1000];
    int no_swap[1000] = {0};
    swap[0] = 1;
    
    for(int i = 1 ; i < a.size(); i++){
        swap[i] = a.size();
        no_swap[i] = a.size();
        
        if(a[i] > a[i-1] && b[i] > b[i-1]){
            //swap is not required
            //calculate swap and no_swap accordingly
            swap[i] = swap[i-1] + 1;
            no_swap[i] = no_swap[i-1];
        }
        
        if(a[i] > b[i-1] && b[i] > a[i-1]){
            //swap is required
            //calculate swap and no_swap accordingly
            swap[i] = min(swap[i], no_swap[i-1] + 1);
            no_swap[i] = min(no_swap[i], swap[i-1]);
        }
    }
    
    return min(swap[a.size()-1], no_swap[a.size()-1]);
    
}

int main(){
	vector<int> a = {1,3,5,4};
	vector<int> b = {1,2,3,7};
	
	cout<<"Input array a: ";
	for(auto e : a){
		cout<<e<<" ";
	}
	cout<<"\nInput array b: ";
	for(auto e : b){
		cout<<e<<" ";
	}
	cout<<"\nExpected output: "<<1;
	cout<<"\nActual output: "<<minSwap(a, b)<<endl;

	return 0;
}

