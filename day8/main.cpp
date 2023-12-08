#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
#include <numeric>


using namespace  std;

#define int long

int stringToInt(string s){
    int ans = 0;
    for(int i=0;i<3;i++){
        ans = ans*26 + (s[i]-'A');
    }
    return ans;
}

void part1(){

    int n = 768;
    string dirs;
    cin>>dirs;
    string s;
    getline(cin, s);
    getline(cin, s);
    vector<pair<int,int> > graph(26*26*26);
    for(int i =0;i<n;i++){
        getline(cin, s);
        graph[stringToInt(s.substr(0,3))] = {stringToInt(s.substr(7,10)),stringToInt(s.substr(12,15))};
    } 
    int ans = 0;
    int cur = 0;
    int instr_len = dirs.size();

    int end = stringToInt("ZZZ");
    while(cur!=end){
        if(dirs[ans%instr_len]=='L'){
            cur = graph[cur].first;
        }
        else{
            cur = graph[cur].second;
        }
        ans++;
    }
    cout<<ans<<endl;
}

void part2(){

    int n = 768;
    string dirs;
    cin>>dirs;
    string s;
    getline(cin, s);
    getline(cin, s);
    vector<pair<int,int> > graph(26*26*26);
    vector<int> curnodes;
    vector<int> is_end(26*26*26);

    for(int i = 0;i<n;i++){
        getline(cin, s);
        int u = stringToInt(s.substr(0,3));

        if(u%26==0){
            curnodes.push_back(u);
        }
        if(u%26==25){
            is_end[u] = true;
        }
        graph[u] = {stringToInt(s.substr(7,10)),stringToInt(s.substr(12,15))};
    } 
    int instr_len = dirs.size();

    int ans = 1;
    for(int cur:curnodes){
        int rounds = 0;
        while(!is_end[cur]){
            if(dirs[rounds%instr_len]=='L'){
                cur = graph[cur].first;
            }
            else{
                cur = graph[cur].second;
            }
            rounds++;
        }
        ans = lcm(ans,rounds); //only works because input behaves very very very very very nice otherwise it had to be solved using crt
    }

    cout<<ans<<endl;
}


signed main(){
    part2();
}