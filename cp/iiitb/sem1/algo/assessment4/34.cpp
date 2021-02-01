#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    
    string sortit(string s){
        int help[26];
        for(int i = 0 ; i < 26; i++){
            help[i] = 0;
        }
        for(int i = 0 ; i < s.size(); i++){
            help[s[i] - 97]++;
        }
        
        string ans = "";
        for(int  i = 25; i > -1 ; i--){
            while(i > -1 && help[i] == 0){
                i--;
            }
            while( i > -1 && help[i] != 0){
                ans += (char) (i + 97);
                help[i]--;
            }
        }
        return ans;
    }
    
    int find(int i, int parent[], int height[]){
        if(parent[i] == i){
            height[i] = 1;
            return i;
        }
        else{
            parent[i] = find(parent[i], parent, height);
            height[i] = 0;
            return parent[i];
        }
    }
    
    void unionAll(int u, int v, int parent[], int height[]){
        if(height[u] > height[v]){
            parent[v] = u;
        }
        else{
            parent[u] = v;
        }
        if(height[u] == height[v]){
            height[v]++;
        }
    }
    
    void printMap(unordered_map<int, string> map){
        for(auto e : map){
            cout<<e.first<<"->"<<e.second<<endl;
        }
    }
    
    string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
        
        int n = s.size();
        
        int parent[n];
        int height[n];
        for(int i = 0 ; i < n ; i++){
            parent[i] = i;
            height[i] = 0;
        }
                
        for(auto e : pairs){
            int parentu = find(e[0], parent, height);
            int parentv = find(e[1], parent, height);
            unionAll(parentu, parentv, parent, height);
        }
        
        //key = componentNumber
        //value = all chars appended as string in all nodes of component
        unordered_map<int, string> map;
        for(int i = 0 ; i < n; i++){
            int root = find(i, parent, height);
            if(map.count(root) == 0){
                map[root] = s[i];
            }
            else{
                map[root] += s[i];
            }
        }
        
        for(auto e : map){
            string temp = e.second;
            map[e.first] = sortit(temp);
        }
        
        string ans = s;
        for(int i = 0 ; i < n; i++){
            ans[i] = map[find(i, parent, height)].back();
            map[find(i, parent, height)].pop_back();
        }
        
        return ans;
        
    }
};

int main(){

	string s = "udyyek";
	vector<vector<int>> pairs = {{3,3},{3,0},{5,1},{3,1},{3,4},{3,5}};
	Solution solution;
	cout<<solution.smallestStringWithSwaps(s, pairs)<<endl;
    return 0;
}

/*
Replace line 107 and 108 with these examples
Possible inputs to try:

	1.
	 	string s = "udyyek";
		vector<vector<int>> pairs = {{3,3},{3,0},{5,1},{3,1},{3,4},{3,5}};
		
	2.  
		string s = "cba";
		vector<vector<int>> pairs = {{0,1},{1,2}};
		
	3.
		string s = "dcab";
		vector<vector<int>> pairs = {{0,3},{1,2},{0,2}};
		
	4.
		string s = "dcab";
		vector<vector<int>> pairs = {{0,3},{1,2}};
		
*/


