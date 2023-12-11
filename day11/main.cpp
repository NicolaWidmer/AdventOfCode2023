#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>


using namespace  std;

#define int long


signed main(){
    int n = 140;
    vector<string> map(n);
    for(int i=0;i<n;i++){
        cin>>map[i];
    }
    int m = map[0].size(); 

    vector<pair<int,int> > galaxys;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(map[i][j]=='#') galaxys.push_back({i,j});
        }
    }
    vector<int> cumsumcol(m);
    vector<int> cumsumrow(n);
    int cumsum = 0;
    for(int i=0;i<n;i++){
        bool isEmpty = true;
        for(int j=0;j<m;j++){
            if(map[i][j]=='#') isEmpty = false;
        }
        if(isEmpty)cumsum++;
        cumsumrow[i] = cumsum;
    } 

    cumsum = 0;
    for(int j=0;j<m;j++){
        bool isEmpty = true;
        for(int i=0;i<n;i++){
            if(map[i][j]=='#') isEmpty = false;
        }
        if(isEmpty)cumsum++;
        cumsumcol[j] = cumsum;
    } 

    int ans1 = 0;
    int ans2 = 0;
    int num_galax = galaxys.size();
    for(int i=0;i<num_galax;i++){
        for(int j=i+1;j<num_galax;j++){
            auto [x1,y1] = galaxys[i];
            auto [x2,y2] = galaxys[j];
            ans1 += abs(x1-x2) + abs(y1-y2) + abs(cumsumrow[x1]-cumsumrow[x2]) + abs(cumsumcol[y1]-cumsumcol[y2]);
            ans2 += abs(x1-x2) + abs(y1-y2) + (1000000-1)*abs(cumsumrow[x1]-cumsumrow[x2]) + (1000000-1)*abs(cumsumcol[y1]-cumsumcol[y2]);
        }
    }

    cout<<ans1<<endl;
    cout<<ans2<<endl;
}