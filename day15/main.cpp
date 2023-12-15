#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>


using namespace  std;


int main(){
    string s;
    cin>>s;
    int ans1 = 0;
    u_int8_t cur = 0;
    for(int i=0;i<s.size();i++){
        char c = s[i];
        if(c==','){
            ans1+=cur;
            cur = 0;
        }
        else{
            cur += c;
            cur *= 17;
        }
    }
    ans1 += cur;

    cout<<ans1<<endl;

    vector<vector<pair<string,int>>> map(256);
    int ans2 = 0;

    cur = 0;
    string curs = "";

    for(int i=0;i<s.size();i++){
        char c = s[i];
        if(c=='-'){
            for(auto it = map[cur].begin();it!=map[cur].end();it++){
                if(it->first==curs){
                    map[cur].erase(it);
                    break;
                }
            }

            cur = 0;
            i+=1;
            curs = "";
        }
        else if(c=='='){
            int lens = s[i+1] - '0';
            bool cont = false;

            for(auto &[h,l]:map[cur]){
                if(h==curs){
                    l=lens;
                    cont = true;
                }
            }
            if(!cont) map[cur].push_back({curs,lens});

            cur = 0;
            i+=2;
            curs = "";
        }
        else{
            cur += c;
            cur *= 17;
            curs = curs + c;
        }
        
    }

    for(int i=0;i<256;i++){
        for(int j=0;j<map[i].size();j++){
            ans2+=(i+1)*(j+1)*map[i][j].second;
        }
    }
    cout<<ans2<<endl;


}