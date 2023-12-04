#include <iostream>
#include <stdlib.h> 
#include <math.h>
#include <vector>
#include <set>
#include <algorithm>

using namespace  std;

int main(){
    int n = 206;
    string s;
    cin>>s;

    vector<vector<int> > nums; 
    vector<set<int> > win_nums;

    for(int i=0;i<n;i++){
        vector<int> curnums;
        set<int> curwin_nums;

        cin>>s>>s;
        while(s[0]!='|'){
            int cur = atoi(s.data());
            curnums.push_back(cur);
            cin>>s;
        }

        cin>>s;
        while (s[0]!='C'){
            int cur = atoi(s.data());
            curwin_nums.insert(cur);
            cin>>s;
        }

        nums.push_back(curnums);
        win_nums.push_back(curwin_nums);
    }

    int ans1=0,ans2=0;
    vector<int> cards(n,1);

    for(int i=0;i<n;i++){
        int count=0;

        for(int num:nums[i]){
            if(win_nums[i].count(num))
                count++;
        }

        if(count)
            ans1+= pow(2,count-1);

        ans2+=cards[i];

        for(int j=i+1;j<min(i+count+1,n);j++){
            cards[j]+=cards[i];
        }
        
    }

    cout<<"Part 1 "<<ans1<<endl;
    cout<<"Part 2 "<<ans2<<endl;
}