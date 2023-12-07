#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <algorithm>


using namespace  std;

bool isSmaller(const string &s1,const string &s2){
    map<char,int> order;
    for(int i=2;i<=9;i++){
        order['0'+i] = i;
    }
    order['T'] = 10; 
    order['J'] = 1;// for part 1 change to 11
    order['Q'] = 12;
    order['K'] = 13;
    order['A'] = 14;
    
    for(int i = 0;i<s1.size();i++){
        if(order[s1[i]]!=order[s2[i]]) return order[s1[i]]<order[s2[i]];
    }
    return false;
}

class Hand{
    public:
        int point;
        string cards;
        bool operator < (const Hand& hand2) const
        {
            string cards2 = hand2.cards;
            map<char,int> map1,map2;
            vector<int> counts1(6,0),counts2(6,0);
            counts1[0] = 1;
            counts2[0] = 1;
            int j1 = 0,j2 = 0;

            for(char c:cards){
                if(c=='J')
                    j1++;//remove for part 1
                else
                    map1[c]++;
            }
            for(char c:cards2){
                if(c=='J')
                    j2++;//remove for part 1
                else
                    map2[c]++;
            }

            for(auto e:map1){
                counts1[e.second]++;
            }
            for(auto e:map2){
                counts2[e.second]++;
            }
            //remove for part 1
            for(int i=5;i>=0;i--){
                if(counts1[i]&&j1){
                    counts1[i]--;
                    counts1[i+j1]++;
                    break;
                }
            }
            //remove for part 1
            for(int i=5;i>=0;i--){
                if(counts2[i]&&j2){
                    counts2[i]--;
                    counts2[i+j2]++;
                    break;
                }
            }
            if(counts1[5]||counts2[5]){
                if(!counts1[5]) return true;
                else if(!counts2[5]) return false;
                else return isSmaller(cards,cards2);
            }

            if(counts1[4]||counts2[4]){
                if(!counts1[4]) return true;
                else if(!counts2[4]) return false;
                else return isSmaller(cards,cards2);
            }

            if((counts1[2]&&counts1[3])||(counts2[2]&&counts2[3])){
                if(!(counts1[2]&&counts1[3])) return true;
                else if(!(counts2[2]&&counts2[3])) return false;
                else return isSmaller(cards,cards2);
            }

            if(counts1[3]||counts2[3]){
                if(!counts1[3]) return true;
                else if(!counts2[3]) return false;
                else return isSmaller(cards,cards2);
            }

            if(counts1[2]==2||counts2[2]==2){
                if(counts1[2]!=2) return true;
                else if(counts2[2]!=2) return false;
                else return isSmaller(cards,cards2);
            }

            if(counts1[2]||counts2[2]){
                if(!counts1[2]) return true;
                else if(!counts2[2]) return false;
                else return isSmaller(cards,cards2);
            }

            return isSmaller(cards,cards2);
        }

};


int main(){
    int n = 1000;

    vector<Hand> hands;
    for(int i = 0;i<n;i++){
        int p;
        string c;
        cin>>c>>p;
        hands.push_back({p,c});
    }

    sort(hands.begin(),hands.end());

    int ans = 0;
    for(int i=0;i<n;i++){
        ans += (i+1)*hands[i].point;
    }

    cout<<ans<<endl;
}