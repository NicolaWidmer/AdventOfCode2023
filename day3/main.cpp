#include <iostream>
#include <math.h>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <ctype.h>

using namespace  std;

struct number { int num, row,start_col,end_col; };

int main(){
    int n=140;

    set<pair<int,int> > symbols;
    map<pair<int,int>,vector<int> > gears;

    vector<number> numbers;
    for(int i=0;i<n;i++){
        string s;
        cin>>s;
        int m = s.size();
        for(int j=0;j<m;j++){
            int cur = 0;
            bool isNum = false;
            int start = j;
            while(j<m&&isdigit(s[j])){
                cur = cur*10 + (s[j]-'0');
                j++;
                isNum = true;
            }
            if(isNum)
                numbers.push_back({cur,i,start,j-1});

            if(j<m&&!isdigit(s[j])&&(s[j]!='.')){
                symbols.insert({i,j});
                if(s[j]=='*') gears[{i,j}] = vector<int>(0);
            }
        }
    }

    int ans1 = 0,ans2 = 0;

    for(auto num:numbers){
        bool isAdj = false;
        for(int i = num.start_col-1;i<=num.end_col+1;i++){
            if(symbols.count({num.row+1,i})||symbols.count({num.row-1,i}))
                isAdj = true;

            auto search = gears.find({num.row+1,i}); 
            if (search != gears.end())
                search->second.push_back(num.num);

            search = gears.find({num.row-1,i}); 
            if (search != gears.end())
                search->second.push_back(num.num);
        }
        if(symbols.count({num.row,num.start_col-1})||symbols.count({num.row,num.end_col+1}))
            isAdj = true;

        auto search = gears.find({num.row,num.start_col-1}); 
        if (search != gears.end())
            search->second.push_back(num.num);

        search = gears.find({num.row,num.end_col+1}); 
        if (search != gears.end())
            search->second.push_back(num.num);      
        

        if(isAdj){
            ans1+=num.num;
        }
    }
    
    for(auto it = gears.begin();it!=gears.end();it++){
        if(it->second.size()==2){
            ans2+=it->second[0]*it->second[1];
        }
    }

    cout<<"Part 1 "<<ans1<<endl;
    cout<<"Part 2 "<<ans2<<endl;
}