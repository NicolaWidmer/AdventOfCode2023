#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>


using namespace  std;

#define int long


signed main(){
    int n = 7;
    string s; cin>>s;
    vector<int> seeds;
    vector<pair<int,int> > ranges;
    while(true){
        cin>>s;
        if(!isdigit(s[0])){
            break;
        }
        seeds.push_back(atol(s.data()));
    }

    for(int i=0;i<seeds.size()/2;i++){
        ranges.push_back(make_pair(seeds[2*i],seeds[2*i+1]));
    }

    cin>>s;

    vector<vector<vector<int> > > maps;

    for(int i=0;i<n;i++){
        vector<vector<int> > map;
        while(true){
            cin>>s;
            if(!isdigit(s[0])){
                cin>>s;
                break;
            }
            vector<int> cur;
            cur.push_back(atol(s.data()));
            for(int j=0;j<2;j++){
                cin>>s;
                cur.push_back(atol(s.data()));
            }
            map.push_back(cur);
        }
        maps.push_back(map);
    }
    int ans1 = -1, ans2 = -1;

    for(int cur:seeds){
        for(auto map:maps){
            for(auto range:map){
                int a= range[0],b= range[1],c= range[2];
                if(b<=cur&&cur<b+c){
                    cur = a + (cur-b);
                    break;
                }
            }
        }
        if(ans1==-1||cur<ans1) ans1 = cur;
    }

    for(auto p : ranges){ //Brute force takes supppppper long
        for(int i=p.first;i<p.first+p.second;i++){
            int cur = i;
            for(auto map:maps){
                for(auto range:map){
                    int a= range[0],b= range[1],c= range[2];
                    if(b<=cur&&cur<b+c){
                        cur = a + (cur-b);
                        break;
                    }
                }
            }
            if(ans2==-1||cur<ans2) ans2 = cur;
        }
        cout<<p.first<<endl;
    }

    cout<<"Part 1 "<<ans1<<endl;

    cout<<"Part 2 "<<ans2<<endl;
    
}