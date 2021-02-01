#include<bits/stdc++.h>
using namespace std;
 
#define maxx INT_MAX 
 
char a[1000][1000];
int n, m; 
int dir[] = {maxx, 1, 2, 3, 4}; //INT_MAX is default, 1 = right, 2= down, 3 = left, 4 = up
 
bool isValidPos(int i, int j){
	if(i < 0 || j < 0 || i >=n || j >= m) return false;
	if(a[i][j] == '*') return false;
	return true;
}
 
class info{
	public:
	int i;
	int j;
	int mydir;
	int pval;
};
 
class com{
    public :
        bool operator()(info &f1, info &f2){
            return f1.pval > f2.pval;
        }
};
 
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>m;
 
	int vx, vy, hx, hy;
	int dp[n][m];
	for(int  i = 0 ; i < n ; i++){
		for(int j = 0 ; j < m; j++){
			cin>>a[i][j];
			if(a[i][j] == 'V'){
				vx = i;
				vy = j;
			}
			else if(a[i][j] == 'H'){
				hx = i;
				hy = j;
			}
			dp[i][j] = maxx;
		}
	}
 
	priority_queue<info, vector<info>, com> q;
	q.push({vx, vy, dir[0], 0});
 
	while(!q.empty()){
		info parent = q.top();
		q.pop();
		int i = parent.i;
		int j = parent.j;
        int pval = parent.pval;
        int pdir = parent.mydir;
 
		if(dp[i][j] >= pval){
			dp[i][j] = pval;
			if(isValidPos(i, j+1)){
				if( dp[i][j+1] >= pval + (pdir != dir[0] && pdir != dir[1]) )
				{
					dp[i][j+1] = pval + (pdir != dir[0] && pdir != dir[1]);
					q.push({i, j+1, dir[1], dp[i][j+1]});
				}
			}
	
			if(isValidPos(i+1, j)){
				if( dp[i+1][j] >= pval + (pdir != dir[0] && pdir != dir[2]) )
				{
					dp[i+1][j] = pval + (pdir != dir[0] && pdir != dir[2]);
					q.push({i+1, j, dir[2], dp[i+1][j]});
				}
			}
	
			if(isValidPos(i, j-1)){
				if( dp[i][j-1] >= pval + (pdir != dir[0] && pdir != dir[3]) )
				{
					dp[i][j-1] = pval + (pdir != dir[0] && pdir != dir[3]);
					q.push({i, j-1, dir[3], dp[i][j-1]});
				}
			}
	
			if(isValidPos(i-1, j)){
				if( dp[i-1][j] >= pval + (pdir != dir[0] && pdir != dir[4]) )
				{
					dp[i-1][j] = pval + (pdir != dir[0] && pdir != dir[4]);
					q.push({i-1, j, dir[4], dp[i-1][j]});
				}
			}
		}
 
 
		
	}
    
 
	int ans = dp[hx][hy] == INT_MAX ? -1 : dp[hx][hy];
	cout<<ans;
 
	return 0;
}
