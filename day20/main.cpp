#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <algorithm>
#include <deque>
#include <numeric>


using namespace  std;

long high = 0;
long low = 0;

deque<tuple<string,string,bool> > queue;

class Flip{
    public:
        string name;
        vector<string> out;
        bool is_high;
        Flip(string n,vector<string> o){
            name = n;
            out = o;
        }
        void rec(bool pos){
            //cout<<name<<" "<<pos<<endl;
            if(pos) return;

            is_high = !is_high;
            for(auto s:out){
                queue.push_back({name,s,is_high});
            }
        }

};
class Conjunction{
    public:
        string name;
        vector<string> out;
        map<string,bool>  in;
        Conjunction(string n, vector<string> o){
            name = n;
            out = o;
        }
        void rec(string from, bool pos){
            //cout<<name<<" "<<pos<<endl;
            in[from] = pos;

            bool is_next_high = false;
            for(auto it = in.begin();it!=in.end();it++){
                if(!it->second) is_next_high = true;
            }
            for(auto s:out){
                queue.push_back({name,s,is_next_high});
            }
        }
};
map<string,Flip> flips;
map<string,Conjunction> conjs;

void send(string from,string to,bool pos){
    if(pos) high++;
    else low++;
    if(flips.find(to)!=flips.end())
        flips.find(to)->second.rec(pos);
    if(conjs.find(to)!=conjs.end())
        conjs.find(to)->second.rec(from,pos);
}


int main(){
    int n = 58;

    int rounds = 10000;
    vector<string> broadcast_out;

    for(int i=0;i<n;i++){

        string name;
        cin>>name;
        string curs;
        vector<string> out;
        cin>>curs;
        while(true){
            cin>>curs;
            int len = curs.size();
            if(curs[len-1]==','){
                out.push_back(curs.substr(0,len-1));
            }
            else{
                out.push_back(curs);
                break;
            }
        }
        if(name[0]=='b') broadcast_out = out;
        else if(name[0] == '%'){
            name = name.substr(1,name.size());
            flips.insert({name,Flip(name,out)});
        }
        else if(name[0] == '&'){
            name = name.substr(1,name.size());
            conjs.insert({name,Conjunction(name,out)});
        }
    }

    for(auto it = flips.begin();it!=flips.end();it++){
        for(auto s:it->second.out){
            if(conjs.find(s)!=conjs.end()){
                conjs.find(s)->second.in[it->first] = false; 
            }
        }
    }
    for(auto it = conjs.begin();it!=conjs.end();it++){
        for(auto s:it->second.out){
            if(conjs.find(s)!=conjs.end()){
                conjs.find(s)->second.in[it->first] = false; 
            }
        }
    }
    int ans1 = 0;
    long pv = 0, qh = 0, xm = 0, hz = 0;
    for(int i=1;i<rounds+1;i++){
        low++;
        deque<tuple<string,string,bool> > nqueue;
        queue = nqueue;
        for(string s:broadcast_out){
            queue.push_back({"broadcast",s,false});
        }
        while (!queue.empty())
        {
            auto [from,to,pos] = queue.front();
            if(from == "pv" && pos && !pv)pv = i;
            if(from == "qh" && pos && !qh)qh = i;
            if(from == "xm" && pos && !hz)xm = i;
            if(from == "hz" && pos && !hz)hz = i;
            queue.pop_front();
            send(from,to,pos);
        }
        if(i == 1000) ans1 = low*high;
    }
    
    cout<<ans1<<endl;
    cout<<lcm(pv,lcm(qh,lcm(xm,hz)))<<endl;
}