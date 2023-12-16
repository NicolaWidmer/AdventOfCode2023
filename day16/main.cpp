#include <iostream>
#include <math.h>
#include <vector>
#include <set>
#include <algorithm>


using namespace  std;

void dfs(int x,int y,int dir,int n,int m,const vector<string> &grid, vector<vector<set<int> > > &vis){
    if(x<0||x>=m||y<0||y>=n) return;
    if(vis[y][x].count(dir)) return;
    
    vis[y][x].insert(dir);

    char c = grid[y][x];

    if(dir == 0){
        if(c == '.'){
            dfs(x+1,y,0,n,m,grid,vis);
        }
        else if(c == '-'){
            dfs(x+1,y,0,n,m,grid,vis);
        }
        else if(c == '|'){
            dfs(x,y-1,3,n,m,grid,vis);
            dfs(x,y+1,1,n,m,grid,vis);
        }
        else if(c == '/'){
            dfs(x,y-1,3,n,m,grid,vis);
        }
        else if(c == '\\'){
            dfs(x,y+1,1,n,m,grid,vis);
        }
    }
    else if(dir == 1){
        if(c == '.'){
            dfs(x,y+1,1,n,m,grid,vis);
        }
        else if(c == '-'){
            dfs(x+1,y,0,n,m,grid,vis);
            dfs(x-1,y,2,n,m,grid,vis);
        }
        else if(c == '|'){
            dfs(x,y+1,1,n,m,grid,vis);
        }
        else if(c == '/'){
            dfs(x-1,y,2,n,m,grid,vis);
        }
        else if(c == '\\'){
            dfs(x+1,y,0,n,m,grid,vis);
        }
    }
    else if(dir == 2){
        if(c == '.'){
            dfs(x-1,y,2,n,m,grid,vis);
        }
        else if(c == '-'){
            dfs(x-1,y,2,n,m,grid,vis);
        }
        else if(c == '|'){
            dfs(x,y-1,3,n,m,grid,vis);
            dfs(x,y+1,1,n,m,grid,vis);
        }
        else if(c == '/'){
            dfs(x,y+1,1,n,m,grid,vis);
        }
        else if(c == '\\'){
            dfs(x,y-1,3,n,m,grid,vis);
        }
    }
    else if(dir == 3){
        if(c == '.'){
            dfs(x,y-1,3,n,m,grid,vis);
        }
        else if(c == '-'){
            dfs(x+1,y,0,n,m,grid,vis);
            dfs(x-1,y,2,n,m,grid,vis);
        }
        else if(c == '|'){
            dfs(x,y-1,3,n,m,grid,vis);
        }
        else if(c == '/'){
            dfs(x+1,y,0,n,m,grid,vis);
        }
        else if(c == '\\'){
            dfs(x-1,y,2,n,m,grid,vis);
        }
    }

}


int main(){
    int n=110;
    vector<string> grid(n);
    for(int i=0;i<n;i++)cin>>grid[i];
    int m = grid[0].size();

    int ans1 = 0;
    int ans2 = 0;
    for(int i=0;i<m;i++){
        vector<vector<set<int> > > vis(n,vector<set<int> >(m));
        dfs(i,0,1,n,m,grid,vis);
        int curans = 0;
        for(auto v:vis){
            for(auto s:v){
                if(!s.empty()) curans++;
            }
        }
        ans2 = max(ans2,curans);

        vis = vector<vector<set<int> > >(n,vector<set<int> >(m));
        dfs(i,n-1,3,n,m,grid,vis);
        curans = 0;
        for(auto v:vis){
            for(auto s:v){
                if(!s.empty()) curans++;
            }
        }
        ans2 = max(ans2,curans);
    }

    for(int i=0;i<n;i++){
        vector<vector<set<int> > > vis(n,vector<set<int> >(m));
        dfs(0,i,0,n,m,grid,vis);
        int curans = 0;
        for(auto v:vis){
            for(auto s:v){
                if(!s.empty()) curans++;
            }
        }

        if(i==0) ans1 = curans;
        ans2 = max(ans2,curans);

        vis = vector<vector<set<int> > >(n,vector<set<int> >(m));
        dfs(m-1,i,2,n,m,grid,vis);
        curans = 0;
        for(auto v:vis){
            for(auto s:v){
                if(!s.empty()) curans++;
            }
        }
        ans2 = max(ans2,curans);
    }

    cout<<ans1<<endl;
    cout<<ans2<<endl;
}