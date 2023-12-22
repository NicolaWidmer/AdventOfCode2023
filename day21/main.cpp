#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>

#define int long

using namespace  std;

bool check(const vector<string> &grid,int i,int j,int n,int m){
    if(i>0 && (grid[i-1][j] == 'O' ||grid[i-1][j] == 'S')) return true;
    if(i<n-1 && (grid[i+1][j] == 'O' ||grid[i+1][j] == 'S')) return true;
    if(j>0 && (grid[i][j-1] == 'O' ||grid[i][j-1] == 'S')) return true;
    if(j<m-1 && (grid[i][j+1] == 'O' ||grid[i][j+1] == 'S')) return true;

    return false;
}

int count(vector<string> grid,int n,int m,int rounds){
    if(rounds<0) return 0;
    for(int r = 0;r<rounds;r++){
        vector<string> newgrid = grid;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(newgrid[i][j] == '.'){
                    if(check(grid,i,j,n,m)) newgrid[i][j] = 'O';
                }
                else if(newgrid[i][j] == 'O' || newgrid[i][j] == 'S'){
                    newgrid[i][j] = '.';
                }
            }
        }
        grid = newgrid;
    }
    int ans1 = 0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(grid[i][j] == 'O' || grid[i][j] == 'S' ){
                ans1++;
            }
        }
    }
    return ans1;
}


signed main(){
    int n = 131,rounds = 64;
    int nh = n/2;
    vector<string> grid(n);
    for(int i = 0; i<n;i++) cin>>grid[i];
    int m = grid[0].size();

    cout<<count(grid,n,m,rounds)<<endl;

    rounds = 26501365;
    int fullodd = count(grid,n,m,501);
    int fulleven = count(grid,n,m,500);
    grid[nh][nh] = '.';
    
    int ans2 = fullodd;

    for(int i=0;i*n+nh<rounds;i++){
        if(i*n+nh<rounds-500){
            ans2 += 4*(i%2==1?fullodd:fulleven);
            ans2 += 4*(i+1)*(i%2==1?fulleven:fullodd);
        }
        else{
            grid[0][nh] = 'S';
            ans2 += count(grid,n,m,rounds-i*n-nh-1);
            grid[0][nh] = '.';

            grid[n-1][nh] = 'S';
            ans2 += count(grid,n,m,rounds-i*n-nh-1);
            grid[n-1][nh] = '.';

            grid[nh][m-1] = 'S';
            ans2 += count(grid,n,m,rounds-i*n-nh-1);
            grid[nh][m-1] = '.';

            grid[nh][0] = 'S';
            ans2 += count(grid,n,m,rounds-i*n-nh-1);
            grid[nh][0] = '.';

            grid[0][0] = 'S';
            ans2 += (i+1)*count(grid,n,m,rounds-(i+1)*n-1);
            grid[0][0] = '.';

            grid[n-1][0] = 'S';
            ans2 += (i+1)*count(grid,n,m,rounds-(i+1)*n-1);
            grid[n-1][0] = '.';

            grid[0][m-1] = 'S';
            ans2 += (i+1)*count(grid,n,m,rounds-(i+1)*n-1);
            grid[0][m-1] = '.';

            grid[n-1][m-1] = 'S';
            ans2 += (i+1)*count(grid,n,m,rounds-(i+1)*n-1);
            grid[n-1][m-1] = '.';
            
        }
    }
    cout<<ans2<<endl;

}