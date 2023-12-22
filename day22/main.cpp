#include <iostream>
#include <math.h>
#include <vector>
#include <set>
#include <algorithm>


using namespace  std;

bool intersec(int l1, int r1, int l2, int r2){
    return l1<=r2&&l2<=r1;
}


int main(){
    int n = 1288; 
    vector<vector<int> > tiles(n);
    vector<set<int> > above(n);
    vector<set<int> > below(n);

    for(int i=0;i<n;i++){
        int a;
        char c;
        for(int j=0;j<6;j++){
            cin>>a;
            tiles[i].push_back(a);
            if(j==5) break;
            cin>>c;
        }
    }

    sort(tiles.begin(),tiles.end(),[](const auto &a, const auto &b)
    { 
        return a[2] < b[2]; 
    });

    for(int i=0;i<n;i++){
        vector<int> t1 = tiles[i];
        int z = 0;
        set<int> b;
        for(int j=0;j<i;j++){
            vector<int> t2 = tiles[j];
            if(intersec(t1[0],t1[3],t2[0],t2[3])&&intersec(t1[1],t1[4],t2[1],t2[4])){
                if(z==t2[5]){
                    b.insert(j);
                }
                else if(z<t2[5]){
                     z = t2[5];
                     b = {j};
                }
            }
        }

        t1[5] = z+t1[5]-t1[2]+1;
        t1[2] = z+1;
        tiles[i] = t1;

        below[i] = b;
        for(int a:b) above[a].insert(i);
    }

    int ans1 = 0;
    int ans2 = 0;

    for(int i=0;i<n;i++){
        int can_remove = 1;
        for(int a:above[i]){
            if(below[a].size()<=1) can_remove = 0;
        }
        ans1+=can_remove;

        set<int> fall = {i};
        for(int j=0;j<n;j++){
            bool all_below_fall = true;
            for(int a:below[j]){
                if(fall.find(a)==fall.end()) all_below_fall = false;
            }
            if(all_below_fall&&below[j].size()!=0) fall.insert(j);
        }
        ans2+=fall.size()-1;
    }
    
    cout<<ans1<<endl;
    cout<<ans2<<endl;

}