#include<stdio.h>

/*
    Q25

    1. Assumptions
        Atleast one A, G, T is present in the array

    2. Idea
        Count the number of G’s that appear in the given array (Let it be GTotal).
        Now take two pointers i = 0 and j = n-1.
        Increment i and decrement j till each have 1, 2, 3 etc. number of A’s and T’s respectively.
        Keep track of number of G’s encountered on both sides using AGcount and TGcount.
        Calculate the number of G’s in middle part of array using
                        GMiddle = GTotal - AGcount - TGcount

    3. Time Complexity
        O(n)

    4. Space Complexity
        O(1)
*/
void main(){

    char a[] = {'G', 'T', 'A', 'C', 'T', 'G', 'T', 'A', 'A', 'G', 'C', 'T', 'C', 'T', 'G', 'T', 'G', 'C', 'A', 'T' };
    int len = sizeof(a)/sizeof(a[0]);

    int GTotal = 0, AGcount = 0, TGcount = 0;
    int totalCount = 0;
    for (int i = 0 ; i < len ; i++){
        if(a[i] == 'G') GTotal++;
    }

    int i = 0, j= len - 1;
    int found = 0;
    while(i < j){
        while(a[i] != 'A' && i<len){
            if(a[i] == 'G') AGcount++;
            i++;
        }
        while(a[j] != 'T' && j>-1){
            if(a[j] == 'G') TGcount++;
            j--;
        };

        totalCount++;

        if(totalCount == (GTotal - AGcount - TGcount) ){
            found = 1;
            break;
        }
        i++;
        j--;
    }
    if(found){
        printf("Suitable i: %d and j: %d found\n", i, j-1);
    }
    else{
        printf("Sorry no suitable i and j found\n");
    }

}