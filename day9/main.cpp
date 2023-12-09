#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>


using namespace  std;


int main(){
    int n = 200, m = 21;
    int ans1 = 0, ans2 = 0;
    for(int i=0;i<n;i++){
        vector<vector<int> > history(m,vector<int>(m,0));
        for(int j=0;j<m;j++){
            cin>>history[0][j];
        }
        for(int j=1;j<m+1;j++){
            for(int k=0;k<m-j;k++){
                history[j][k] = history[j-1][k+1] - history[j-1][k];
            }
        }
        int curans = 0;
        for(int j=m-1;j>=0;j--){
            ans1 = ans1 + history[j][m-j-1];
            curans = history[j][0] - curans;
        }
        ans2 += curans;
    }
    cout<<"Part 1 " <<ans1<<endl;
    cout<<"Part 2 " <<ans2<<endl;
}