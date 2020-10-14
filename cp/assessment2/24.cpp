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
ll base = 62;                   //considering a-z A-Z and 0-9 values

//Given two string a, b and length len, check if a and b both contain a substring of length = len
int checkIfStringWithLengthIsSubString(string a, string b, int len);

//returns a hashmap containing rolling hash as keys and starting position of string as key
unordered_map<ll, unordered_set<int>> getRollingHashMap(string a, int len);

//Use brute force to check if two string starting somewhere match exactly
int checkIfStringMatchBruteForce(string a, unordered_set<int> startPositionsOfA, string b, int startPosOfB, int len);

//helper functions
void printMap(unordered_map<ll, unordered_set<int>> map);
void unitTest();

int main(){
    //Ans should be 26 as we have a to z in between both
    string a = "qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqabcdefghijklmnopqrstuvwxyzpppppppppppppppppppppppppppppppppppp";
    string b = "fffffffffabcdefghijklmnopqrstuvwxyzkkkkkkkkkkkkkkkkkkk";

    unitTest();

    return 0;
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
        hashVal = ((hashVal * base) + b[i] - (b[i + 1 - len] * final)) % prime;
        if(hashVal < 0) hashVal = hashVal + prime;
        cout<<b[i + 1 - len]<<" "<<b[i]<<endl;
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
        if(i == len) return 1;
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
            map[hashVal].insert(i - len);
        }
        else{
            //starting position of string is i - len
            map[hashVal] = {i - len};
        }
        i++;
    }
    return map;
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


void unitTest(){
    string a = "qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqabcdefghijklmnopqrstuvwxyzpppppppppppppppppppppppppppppppppppp";
    string b = "fffffffffabcdefghijklmnopqrstuvwxyzkkkkkkkkkkkkkkkkkkk";
    cout<<checkIfStringWithLengthIsSubString(a, b, 26)<<endl;
}