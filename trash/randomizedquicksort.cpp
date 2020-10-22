#include<iostream>
#include<vector>
#include <stdlib.h>
using namespace std;

int partition(int a[], int l, int r){

	int pivot = rand() % (r-l +1) + l;
	cout<<"Pivot pos: "<<pivot<<endl;
	int t = a[pivot];
	a[pivot] = a[l];
	a[l] = t;
	int i = l+1;
	int j = r;
	int pivVal = a[l];
	cout<<"Pivot val: "<<pivVal<<endl;
	for(int i = 0 ; i < 10; i++) cout<<a[i]<<" ";
	cout<<endl;
	while(i <= j){
		while(a[i] <= pivVal && (i <= j)) i++;
		while(a[j] > pivVal && (i <= j))j--;
		if(i < j){
		
			int temp = a[i];
			a[i] = a[j];
			a[j] = temp;
		}
	}
	i--;
	a[l] = a[i];
	a[i] = pivVal;
	return i;

}

void quicksort(int a[], int l, int r){
	if(l < r)
	{
		int k = partition(a, l, r);
		for(int i = 0 ; i < 10; i++) cout<<a[i]<<" ";
		cout<<endl;
		quicksort(a, l, k-1);
		quicksort(a, k+1, r);
	}

}

int main(){
	
	
	int a[] = {2,3,55,77,44,33,-22, -30, 3, 3};
	for(int i = 0 ; i < 10; i++) cout<<a[i]<<" ";
	cout<<endl;
	quicksort(a,0,9);
	for(int i = 0 ; i < 10; i++) cout<<a[i]<<" ";
	cout<<endl;
}
