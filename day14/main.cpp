#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
#include <map>


using namespace  std;

void rot_north(vector<string> &map,int n,int m){
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++)if(map[i][j] == 'O'){
            map[i][j] = '.';
            for(int ii = i;ii>=0;ii--){
                if(ii == 0||map[ii-1][j]=='#' || map[ii-1][j]=='O'){
                    map[ii][j]='O';
                    break;
                } 
            }
        }
    }
}

void rot_south(vector<string> &map,int n,int m){
    for(int i=n;i>=0;i--){
        for(int j=0;j<m;j++)if(map[i][j] == 'O'){
            map[i][j] = '.';
            for(int ii = i;ii<n;ii++){
                if(ii == n-1||map[ii+1][j]=='#' || map[ii+1][j]=='O'){
                    map[ii][j]='O';
                    break;
                } 
            }
        }
    }
}

void rot_west(vector<string> &map,int n,int m){
    for(int j=0;j<m;j++){
        for(int i=0;i<n;i++)if(map[i][j] == 'O'){
            map[i][j] = '.';
            for(int jj = j;jj>=0;jj--){
                if(jj == 0||map[i][jj-1]=='#' || map[i][jj-1]=='O'){
                    map[i][jj]='O';
                    break;
                } 
            }
        }
    }
}


void rot_east(vector<string> &map,int n,int m){
    for(int j=m;j>=0;j--){
        for(int i=0;i<n;i++)if(map[i][j] == 'O'){
            map[i][j] = '.';
            for(int jj = j;jj<m;jj++){
                if(jj == m-1||map[i][jj+1]=='#' || map[i][jj+1]=='O'){
                    map[i][jj]='O';
                    break;
                } 
            }
        }
    }
}

int solve1(vector<string> cave,int n,int m){
    int ans = 0;

    rot_north(cave,n,m);

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(cave[i][j] == 'O') ans+=n-i;
        }
    }

    return ans;
}

int solve2(vector<string> cave,int n,int m){
    int ans = 0;
    map<vector<string>,int> store;

    for(int i=0;i<1e9;i++){
        auto it = store.find(cave);
        if(it!=store.end()){
          int cyle_length = i-it->second;
          i = 1e9 - ( (1000000000 - it->second) % cyle_length);
        }
        vector<string> cur = cave;
        store[cave]=i;
        rot_north(cave,n,m);
        rot_west(cave,n,m);
        rot_south(cave,n,m);
        rot_east(cave,n,m);
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(cave[i][j] == 'O') ans+=n-i;
        }
    }

    return ans;
}



int main(){
    int n = 100;
    vector<string> cave(n);
    for(int i=0;i<n;i++) cin>>cave[i];

    int m = cave[0].size();

    cout<<solve1(cave,n,m)<<endl;
    cout<<solve2(cave,n,m)<<endl;
}