#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
#include <queue>


using namespace  std;

typedef tuple<int,int,int,int> state;


const vector<pair<int,int>> dir_map = {{0,1},{1,0},{0,-1},{-1,0}};

int dijs1(int n,int m,const vector<vector<int> > &grid){
    priority_queue<pair<int,state> > queue;

    vector<vector<vector<vector<int> > > > dist(n,vector<vector<vector<int> > >(m,vector<vector<int> >(4,vector<int>(3,-1))));
    queue.push({0,{0,1,0,0}});
    queue.push({0,{1,0,1,0}});

    while(!queue.empty()){
        auto [d,s] = queue.top();
        auto [x,y,dir,cont] = s;
        queue.pop();
        
        if(dist[x][y][dir][cont]!=-1) continue;
        if(x==n-1&&y==m-1){
            return -d+grid[x][y];
        }

        dist[x][y][dir][cont] = -d;
        for(int i = -1;i<2;i++){
            int next_dir = (dir+i+4)%4;
            auto [dx,dy] = dir_map[next_dir];
            int next_cont = i==0?cont+1:0;
            if(!(x+dx<0||x+dx>n-1||y+dy<0||y+dy>m-1||next_cont>2))
                queue.push({d-grid[x][y],{x+dx,y+dy,next_dir,next_cont}});
        }
    }
    return -1;
}

int dijs2(int n,int m,const vector<vector<int> > &grid){
    priority_queue<pair<int,state> > queue;

    vector<vector<vector<vector<int> > > > dist(n,vector<vector<vector<int> > >(m,vector<vector<int> >(4,vector<int>(10,-1))));
    queue.push({0,{0,1,0,0}});
    queue.push({0,{1,0,1,0}});
    while(!queue.empty()){
        auto [d,s] = queue.top();
        auto [x,y,dir,cont] = s;
        queue.pop();
        
        if(dist[x][y][dir][cont]!=-1) continue;
        if(x==n-1&&y==m-1){
            if(cont>=3)
                return -d+grid[x][y];
            else
                continue;
        }

        dist[x][y][dir][cont] = -d;
        for(int i = -1;i<2;i++){
            int next_dir = (dir+i+4)%4;
            auto [dx,dy] = dir_map[next_dir];
            int next_cont = i==0?cont+1:0;
            if(!(x+dx<0||x+dx>n-1||y+dy<0||y+dy>m-1||next_cont>9)&&(cont>=3||i==0))
                queue.push({d-grid[x][y],{x+dx,y+dy,next_dir,next_cont}});
        }
    }
    return -1;
}


int main(){
    int n = 141,m = 0;
    vector<vector<int> > grid(n);
    for(int i=0;i<n;i++){
        string s;
        cin>>s;
        m = s.size();
        for(int j=0;j<m;j++){
            grid[i].push_back(s[j]-'0');
        }
    }

    cout<<dijs1(n,m,grid)<<endl;
    cout<<dijs2(n,m,grid)<<endl;
}