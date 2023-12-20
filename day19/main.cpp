#include <iostream>
#include <iterator>
#include <string>
#include <regex>
#include <vector>
#include <map>

using namespace std;
#define int long

class Range{
    public:
        map<string,pair<int,int> > vars;

        Range(){
            vars["x"] = {0,4000};
            vars["m"] = {0,4000};
            vars["a"] = {0,4000};
            vars["s"] = {0,4000};
        }

        int value(){
            auto [lx,rx] = vars["x"];
            auto [lm,rm] = vars["m"];
            auto [la,ra] = vars["a"];
            auto [ls,rs] = vars["s"];
            if(lx>=rx || lm>=rm ||la>=ra ||ls>=rs) return 0;

            int x1 = rx-lx;
            int m1 = rm-lm;
            int a1 = ra-la;
            int s1 = rs-ls;
            return x1*m1*a1*s1;
        }

        void print()
        {
            auto [lx,rx] = vars["x"];
            auto [lm,rm] = vars["m"];
            auto [la,ra] = vars["a"];
            auto [ls,rs] = vars["s"];
            cout<<"x = ("<<lx<<","<<rx<<"] "<<"m = ("<<lm<<","<<rm<<"] "<<"a = ("<<la<<","<<ra<<"] "<<"s = ("<<ls<<","<<rs<<"]"<<endl;
        }
};

int dfs(string state, Range r,const map<string,pair<vector<tuple<string,bool,int,string> >,string> > &rules){
    if(state == "A"){
        return r.value();
    }
    if(state == "R") return 0;
    int ans = 0;
    auto [v,term] = rules.at(state);
     
    for(auto [var,big,count,state]:v){
        Range r1 = r;
        Range r2 = r;
        auto [low,up] = r.vars[var];
        if(big){
            r1.vars[var] = {low,min(count-1,up)};
            r2.vars[var] = {max(count-1,low),up};
            ans += dfs(state,r1,rules);
            r = r2;
        }
        else{
            r1.vars[var] = {low,min(count,up)};
            r2.vars[var] = {max(count,low),up};
            ans += dfs(state,r2,rules);
            r = r1;
        }

    }
    ans += dfs(term,r,rules);
    return ans;
}

signed main(){
    int n = 773;
    string s;
    
    string mid = "(([a-z]+)(>|<)([0-9]+):([a-zA-Z]+),)?";
    std::regex r("^([a-z]+)\\{"+mid+mid+mid+mid+mid+"([a-zA-Z]+)\\}$");
    
    map<string,pair<vector<tuple<string,bool,int,string> >,string> >  rules;
    int j=0;
    for(;j<n;j++){
        string s;
        getline(cin,s);
        if(s=="") break;
        std::smatch m;
    
        std::regex_match(s, m, r);
        vector<tuple<string,bool,int,string> >cur;
        string state = m[1];
        for(int i=2;i<m.size()-1;i++){
            if(m[i]=="")continue;
            i++;
            string var = m[i++];
            bool bigger = m[i++] == "<";
            string c = m[i++];
            int count = atoi(&c[0]);
            string nextstate = m[i];
            cur.push_back({var,bigger,count,nextstate});
        }
        rules[state] = {cur,m[m.size()-1]};
    }
    j++;
    
    std::regex r2("^\\{x=([0-9]+),m=([0-9]+),a=([0-9]+),s=([0-9]+)\\}$");
    r = r2;
    int ans1 = 0;
    
    for(;j<n;j++){
        getline(cin,s);
        std::smatch m;
        std::regex_match(s, m, r);
        map<string,int> res;
        int i = 1;
        string c = m[i++];
        res["x"] = atoi(&c[0]);
        c = m[i++];
        res["m"] = atoi(&c[0]);
        c = m[i++];
        res["a"] = atoi(&c[0]);
        c = m[i++];
        res["s"] = atoi(&c[0]);
        string cur = "in";
        while(true){
            if(cur=="R") break;
            else if(cur=="A"){
                ans1 += res["x"]+res["m"]+res["a"]+res["s"];
                break;
            }
            auto [v,term] = rules[cur];
            cur = term; 
            for(auto [var,big,count,state]:v){
                if(res[var]<count&&big || res[var]>count&&!big){
                    cur = state;
                    break;
                }
            }
        }
    }
    cout<<ans1<<endl;
    cout<<dfs("in",Range(),rules)<<endl;
}



