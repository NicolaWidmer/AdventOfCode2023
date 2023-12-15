#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>


using namespace  std;


int main(){
    int n = 1350;

    string s;
    vector<string> cur_map;

    int ans1=0;
    int ans2=0;

    for(int i=0;i<n;i++){

        getline(cin,s);
        if(s.size() == 0){
            int rows = cur_map.size();
            int cols = cur_map[0].size();

            for(int i=1;i<cols;i++){
                bool isMirror = true;
                bool isOneOff = false;

                for(int col1 = i-1,col2 = i;col1>=0&&col2<cols;col1--,col2++){
                    for(int row=0;row<rows;row++){
                        if(cur_map[row][col1] != cur_map[row][col2]){
                            isOneOff = isMirror;
                            isMirror = false;
                        }
                    }
                }

                if(isMirror) ans1+=i;
                else if(isOneOff) ans2+=i;
            }

            for(int i=1;i<rows;i++){
                bool isMirror = true;
                bool isOneOff = false;

                for(int row1 = i-1,row2 = i;row1>=0&&row2<rows;row1--,row2++){
                    for(int col=0;col<cols;col++){
                        if(cur_map[row1][col] != cur_map[row2][col]){
                            isOneOff = isMirror;
                            isMirror = false;
                        }
                    }
                }

                if(isMirror) ans1+=i*100;
                else if(isOneOff) ans2+=i*100;
            }

            cur_map.clear();
            
        }
        else{
            cur_map.push_back(s);
        }
    }
    cout<<ans1<<endl;
    cout<<ans2<<endl;
}