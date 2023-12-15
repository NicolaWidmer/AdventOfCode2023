#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
#include <sstream>


using namespace  std;

#define int long

int rec(int si,int ni, int take_last,const string &s,const vector<int> &nums,vector<vector<vector<int> > > &dp){
    if(si==0) return ni==0?1:0;
    if(ni==0) return s[si-1]=='#'?0:rec(si-1,ni,take_last,s,nums,dp);
    if(dp[si][ni][take_last]!=-1) return dp[si][ni][take_last];

    int ans = s[si-1]=='#'?0:rec(si-1,ni,1,s,nums,dp);

    int cur_num = nums[ni-1];
    if(take_last&&cur_num<=si){
        bool isPoss = true;
        for(int k = si-1;k>si-cur_num-1;k--)
            if(s[k] == '.') isPoss = false;
        if(isPoss) ans+=rec(si-cur_num,ni-1,0,s,nums,dp);
    }
    return dp[si][ni][take_last] = ans ;
}

signed main(){
    int n = 1000;

    int ans1 = 0;
    int ans2 = 0;

    for(int i=0;i<n;i++){
        string s;
        cin>>s;
        string line; 
        getline(cin,line);


        vector<int> cur_nums;
        int cou = 0;
        for(char c:line){
            if(c==',') cou++;
        }
        stringstream stream(line);

        for(int j=0;j<cou;j++){
            int c;stream>>c;
            cur_nums.push_back(c);
            char ch;stream>>ch;
        }

        int c;stream>>c;
        cur_nums.push_back(c);
        
        vector<vector<vector<int> > > dp1(s.size()+1,vector<vector<int> >(cur_nums.size()+1,vector<int>(2,-1)));
        ans1+=rec(s.size(),cur_nums.size(),1,s,cur_nums,dp1);

        vector<int> cur_nums2 = cur_nums;
        string s2=s;
        for(int i=0;i<4;i++){
            for(int num:cur_nums) cur_nums2.push_back(num);
            s2 = s2+"?"+s;
        }

        vector<vector<vector<int> > > dp2(s2.size()+1,vector<vector<int> >(cur_nums2.size()+1,vector<int>(2,-1)));
        ans2+=rec(s2.size(),cur_nums2.size(),1,s2,cur_nums2,dp2);

    }
    cout<<ans1<<endl;
    cout<<ans2<<endl;
}