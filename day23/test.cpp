#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>


using namespace  std;

bool isGood(char c){
    return c=='.' || c=='^' || c=='>' || c =='<' || c=='v';
}

int main(){
    int n = 141; 
    vector<string> grid(n);
    for(int i=0;i<n;i++) cin>>grid[i];
    int m = grid[0].size();
    vector<vector<bool> > vis(n,vector<bool>(m,false));
    int cross = 0;
    for(int i=1;i<n-1;i++){
        for(int j=0;j<m-1;j++){
            if(isGood(grid[i][j]))
        }
    }
}