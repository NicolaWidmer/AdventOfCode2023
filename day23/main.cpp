#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>


using namespace  std;

int rec(int x,int y,const vector<string> &grid,vector<vector<bool> > &vis,int n,int m){
    if(x<0||x>n-1||y<0||y>m-1||grid[x][y]=='#'||vis[x][y]) return -1000000;
    if(x==n-1&&y==m-2) return 0;

    vis[x][y] = true;
    int ans = -100000;
    if(grid[x][y] == '>' ||grid[x][y] == '.') ans = max(ans,rec(x,y+1,grid,vis,n,m));
    if(grid[x][y] == '<' ||grid[x][y] == '.') ans = max(ans,rec(x,y-1,grid,vis,n,m));
    if(grid[x][y] == 'v' ||grid[x][y] == '.') ans = max(ans,rec(x+1,y,grid,vis,n,m));
    if(grid[x][y] == '^' ||grid[x][y] == '.') ans = max(ans,rec(x-1,y,grid,vis,n,m));

    vis[x][y] = false;
    return ans+1;
}

int rec2(int x,int y,const vector<string> &grid,vector<vector<bool> > &vis,int n,int m){
    if(x<0||x>n-1||y<0||y>m-1||grid[x][y]=='#'||vis[x][y]) return -100000;
    if(x==n-1&&y==m-2) return 0;

    vis[x][y] = true;
    int ans = -100000;
    ans = max(ans,rec2(x,y+1,grid,vis,n,m));
    ans = max(ans,rec2(x,y-1,grid,vis,n,m));
    ans = max(ans,rec2(x+1,y,grid,vis,n,m));
    ans = max(ans,rec2(x-1,y,grid,vis,n,m));

    vis[x][y] = false;
    return ans+1;
}


int main(){
    int n = 141; 
    vector<string> grid(n);
    for(int i=0;i<n;i++) cin>>grid[i];
    int m = grid[0].size();
    vector<vector<bool> > vis(n,vector<bool>(m,false));

    cout<<rec(0,1,grid,vis,n,m)<<endl;
    cout<<rec2(0,1,grid,vis,n,m)<<endl; //needs about 5 min on my laptop
}