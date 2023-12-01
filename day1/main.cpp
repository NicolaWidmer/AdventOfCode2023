#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>

#define int long
using namespace  std;


int getDigit(const string &s,int i){
    if('0'<=s[i]&&s[i]<='9') return s[i]-'0';

    if(s.size()-i<3) return -1;

    if(s.substr(i,3)=="one") return 1;
    else if(s.substr(i,3)=="two") return 2;
    else if(s.substr(i,3)=="six") return 6;

    if(s.size()-i<4) return -1;

    if(s.substr(i,4)=="four") return 4;
    else if(s.substr(i,4)=="five") return 5;
    else if(s.substr(i,4)=="nine") return 9;

    if(s.size()-i<5) return -1;

    if(s.substr(i,5)=="three") return 3;
    else if(s.substr(i,5)=="seven") return 7;
    else if(s.substr(i,5)=="eight") return 8;

    return -1;
}

signed main(){
    int n=1000;
    int ans=0;
    for(int j=0;j<n;j++){
        string s;
        cin>>s;
        for(int i = 0;i<s.size();i++){
            int digit = getDigit(s,i);
            if(digit!=-1){
                cout<<digit;
                ans +=10*(digit);
                break;
            }
        }

        for(int i = s.size()-1;i>=0;i--){
            int digit = getDigit(s,i);
            if(digit!=-1){
                cout<<digit<<endl;
                ans +=digit;
                break;
            }
        }
    }
    cout<<ans<<endl;
    
}