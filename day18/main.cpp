#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <set>
#include <algorithm>


using namespace  std;

#define int long

const map<string,pair<int,int> > dir1 = {{"U",{-1,0}},{"D",{1,0}},{"L",{0,-1}},{"R",{0,1}}};
const vector<pair<int,int> > dir2 =  {{0,1},{1,0},{0,-1},{-1,0}};

void solve1(){
    int n = 680;

    set<pair<int,int> > grid;
    int x=0,y=0,maxx=0,maxy=0,minx=0,miny=0;
    grid.insert({x,y});

    for(int i=0;i<n;i++){
        string d;
        int range;
        string col;
        cin>>d>>range>>col;
        auto [dx,dy] = dir1.at(d);
        for(int j=0;j<range;j++){
            x += dx;
            y += dy;
            grid.insert({x,y});
            minx=min(x,minx);
            maxx=max(x,maxx);
            miny=min(y,miny);
            maxy=max(y,maxy);
        }
    }

    int ans1 = 0;
    for(int x=minx;x<maxx+1;x++){
        int is_in = 0;
        bool lastborderup = false;
        for(int y = miny;y<maxy+1;y++){
            if(grid.count({x,y})){
                if(!grid.count({x,y-1})) lastborderup = grid.count({x-1,y});
                ans1+=1;
            }
            else{
                if(grid.count({x,y-1})){
                    if(lastborderup == (grid.count({x+1,y-1})!=0)) is_in = 1 - is_in; 
                }
                ans1 += is_in;
            }

        }
    }
    cout<<ans1<<endl;
}

void solve2(){
    int n = 680;

    vector<pair<int,int> > corners1;
    int border1 = 0;
    int x=0,y=0;
    corners1.push_back({x,y});
    int area1 = 0;

    for(int i=0;i<n;i++){
        string d;
        int range;
        string s;
        cin>>d>>range>>s;
        range = 0;
        for(int i=2;i<7;i++){
            range*=16;
            if(isdigit(s[i])) range+=s[i]-'0';
            else range+=s[i]-'a'+10;
        }

        auto [dx,dy] = dir2[s[7]-'0'];

        x += range*dx;
        y += range*dy;
        corners1.push_back({x,y});
        border1+=range;
    }
    for(int i=0;i<n;i++){
        auto [x1,y1] = corners1[i]; 
        auto [x2,y2] = corners1[i+1]; 
        area1+=(y2+y1)*(x2-x1);
    }
    cout<<(area1+border1)/2+1<<endl;
}

signed main(){
    solve2();
}