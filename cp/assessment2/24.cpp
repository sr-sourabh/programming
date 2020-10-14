/*
Author : Shourabh Payal
24. Implement an efficient algorithm to compute the longest common sub-string of two strings.
*/
#include<iostream>
#include<string.h>
#include<unordered_set>
#include<unordered_map>
using namespace std;

typedef long long ll;

ll prime = 1000000009;
ll base = 62;                               //considering a-z A-Z and 0-9 values
int subStringStartPos = -1;                 //start position of max length sub string

//Returns the length of maximum substring in a and b using binary search
int binarySearchForMaxLen(string a, string b);

//Given two string a, b and length len, check if a and b both contain a substring of length = len
int checkIfStringWithLengthIsSubString(string a, string b, int len);

//returns a hashmap containing rolling hash as keys and starting position of string as key
unordered_map<ll, unordered_set<int>> getRollingHashMap(string a, int len);

//Use brute force to check if two string starting somewhere match exactly
int checkIfStringMatchBruteForce(string a, unordered_set<int> startPositionsOfA, string b, int startPosOfB, int len);

//helper functions
void printMap(unordered_map<ll, unordered_set<int>> map);
void unitTest();
void displaySubString(string a, int len);

int main(){
    unitTest();
    return 0;
}

int binarySearchForMaxLen(string a, string b){
    int left = 0;
    int right = min(a.size(), b.size()) + 1;

    while(left < right){
        int mid = (right + left) / 2;
        if(checkIfStringWithLengthIsSubString(a,b, mid))
            left = mid + 1;
        else
            right = mid;
    }
    return (left - 1);
}

int checkIfStringWithLengthIsSubString(string a, string b, int len){
    int result = 0;
    unordered_map<ll, unordered_set<int>> map = getRollingHashMap(a, len);
    //printMap(map);

    ll hashVal = 0;
    ll final = 1;
    int i;

    for(i = 0 ; i < len; ++i){
        hashVal = (hashVal * base + b[i]) % prime;
        final = (final * base) % prime;
    }

    if(map.count(hashVal) > 0){
        result = checkIfStringMatchBruteForce(a, map[hashVal], b, i - len, len);
        if(result) return result;
    }

    while(i < b.size()){
        hashVal = ((hashVal * base) + b[i] - (b[i - len] * final)) % prime;
        if(hashVal < 0) hashVal = hashVal + prime;

        if(map.count(hashVal) > 0){
            result = checkIfStringMatchBruteForce(a, map[hashVal], b, (i + 1 - len), len);
            if(result) return result;
        }
        i++;
    }

    return result;
}

int checkIfStringMatchBruteForce(string a, unordered_set<int> startPositionsOfA, string b, int startPosOfB, int len){
    int result = 0;
    for( auto startPositionOfA : startPositionsOfA ){
        int i = 0;
        for(i = 0; i < len; i++){
            if(a[startPositionOfA + i] != b[startPosOfB + i]) break;
        }
        if(i == len){
            subStringStartPos = startPositionOfA;
            return 1;
        }
    }
    return result;
}


unordered_map<ll, unordered_set<int>> getRollingHashMap(string a, int len){
    unordered_map<ll, unordered_set<int>> map;
    ll hashVal = 0;
    ll final = 1;
    int i;

    for(i = 0 ; i < len; ++i){
        hashVal = (hashVal * base + a[i]) % prime;
        final = (final * base) % prime;
    }
    //This hashvalue corresponds to index 0
    map[hashVal] = {0};

    while(i < a.size()){
        hashVal = ( (hashVal * base) + a[i] - ( a[i - len] * final ) ) % prime;
        if(hashVal < 0) hashVal = hashVal + prime;
        if(map.count(hashVal) > 0){
            map[hashVal].insert(i - len + 1);
        }
        else{
            //starting position of string is i - len + 1
            map[hashVal] = {i - len + 1};
        }
        i++;
    }
    return map;
}

void unitTest(){
    string a = "qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqabcdefghijklmnopqrstuvwxyzpppppppppppppppppppppppppppppppppppp";
    string b = "fffffffffabcdefghijklmnopqrstuvwxyzkkkkkkkkkkkkkkkkkkk";
    cout<<"Test case 1\nString a: "<<a<<endl<<"String b: "<<b<<endl;
    int len = binarySearchForMaxLen(a, b);
    cout<<"Expected: 26\tOutput: "<<len<<endl;
    displaySubString(a, len);

    a = "abcdefghij";
    b = "def";
    cout<<"Test case 2\nString a: "<<a<<endl<<"String b: "<<b<<endl;
    len = binarySearchForMaxLen(a, b);
    cout<<"Expected: 3\tOutput: "<<len<<endl;
    displaySubString(a, len);

    a = "abcccc";
    b = "ggggggggggggggggggggabcccclllllllllllllllllllllllllll11111112222222";
    cout<<"Test case 3\nString a: "<<a<<endl<<"String b: "<<b<<endl;
    len = binarySearchForMaxLen(a, b);
    cout<<"Expected: 6\tOutput: "<<len<<endl;
    displaySubString(a, len);

    a = "111111112222222222229999999999shourabh0000000000000009999999999999999";
    b = "3333333333333333333333rabh8888888888888888";
    cout<<"Test case 4\nString a: "<<a<<endl<<"String b: "<<b<<endl;
    len = binarySearchForMaxLen(a, b);
    cout<<"Expected: 4\tOutput: "<<len<<endl;
    displaySubString(a, len);

    a = "IIIT Bangalore";
    b = "IIIT Bangalore";
    cout<<"Test case 5\nString a: "<<a<<endl<<"String b: "<<b<<endl;
    len = binarySearchForMaxLen(a, b);
    cout<<"Expected: 14\tOutput: "<<len<<endl;
    displaySubString(a, len);
}

void displaySubString(string a, int len){
    cout<<"One of the maximum substring: "<<a.substr(subStringStartPos, len)<<endl<<endl;
}

void printMap(unordered_map<ll, unordered_set<int>> map){
    int c = 0;
    for(auto e : map){
        cout<<"Key: "<<e.first<<"\tValues: ";
        for(auto ee : e.second){
            cout<<ee<<" ";
        }
        cout<<endl;
        c += e.second.size();
    }
    cout<<"Total: "<<c<<endl;
}