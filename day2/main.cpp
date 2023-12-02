#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>


using namespace  std;

char lastChar(const string &s){
    return s[s.size()-1];
}

int minPosPow(const vector<vector<int> > &game){
    int maxr=0,maxg=0,maxb=0;
    for(auto round:game){
        maxr = max(maxr,round[0]);
        maxg = max(maxg,round[1]);
        maxb = max(maxb,round[2]);
    }
    return maxr*maxg*maxb;
}

bool isPoss(const vector<vector<int> > &game){
    for(auto round:game){
        if(round[0]>12 || round[1]>13 || round[2]>14)
            return false;
    }
    return true;
}

int main(){
    int n = 100;
    vector<vector<vector<int> > > games;

    for(int i=0;i<n;i++){
        vector<vector<int> > game;

        string s;
        int cur;

        cin>>s>>s;

        while(true){
            vector<int> round(3,0);

            while(true){
                cin>>cur;
                cin>>s;
                if(s[0]=='r'){
                    round[0]=cur;
                }
                else if(s[0]=='g'){
                    round[1]=cur;
                }
                else if(s[0]=='b'){
                    round[2]=cur;
                }

                if(lastChar(s)!=',') break;
            }
            game.push_back(round);

            if(lastChar(s)!=';')break;
        }
        games.push_back(game);
    }

    int ans1 = 0;
    int ans2 = 0;

    for(int i=0;i<n;i++){
        if(isPoss(games[i])) ans1 += i+1;
        ans2 += minPosPow(games[i]);
    }
    
    cout<<"Part1 "<<ans1<<endl;
    cout<<"Part2 "<<ans2<<endl;
}