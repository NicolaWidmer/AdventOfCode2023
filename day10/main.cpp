#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>


using namespace  std;
vector<vector<bool> > isBorder;

int dfs(int lastx,int lasty,int x,int y,const vector<string> &map,vector<vector<bool> > &isBorder){
    isBorder[x][y] = true;

    if(map[x][y]=='S') return 1;

    if(map[x][y] == '-'){
        if(lasty == y-1) return 1+dfs(x,y,x,y+1,map,isBorder);
        else return 1+dfs(x,y,x,y-1,map,isBorder);
    }
    else if(map[x][y] == 'F'){
         if(lasty == y+1) return 1+dfs(x,y,x+1,y,map,isBorder);
         else return 1+dfs(x,y,x,y+1,map,isBorder);
    }
    else if(map[x][y] == '7'){
         if(lasty == y-1) return 1+dfs(x,y,x+1,y,map,isBorder);
         else return 1+dfs(x,y,x,y-1,map,isBorder);
    }
    else if(map[x][y] == 'J'){
         if(lasty == y-1) return 1+dfs(x,y,x-1,y,map,isBorder);
         else return 1+dfs(x,y,x,y-1,map,isBorder);
    }
    else if(map[x][y] == 'L'){
         if(lasty == y+1) return 1+dfs(x,y,x-1,y,map,isBorder);
         else return 1+dfs(x,y,x,y+1,map,isBorder);
    }
    else if(map[x][y] == '|'){
         if(lastx == x+1) return 1+dfs(x,y,x-1,y,map,isBorder);
         else return 1+dfs(x,y,x+1,y,map,isBorder);
    }

}

int main(){
    int n = 140;  char s_replace = '|';//manuel
    vector<string> map(n);
    for(int i = 0;i<n;i++){
        cin>>map[i];
    }

    int m = map[0].size();
    vector<vector<bool> >  isBorder(n,vector<bool>(m,false));

    cout<<m<<endl;

    int startx,starty;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(map[i][j] == 'S') {
                startx = i;
                starty = j;
            }
        }
    }

    for(int i=-1;i<2;i++){
        for(int j=-1;j<2;j++){
            cout<<map[startx+i][starty+j];
        }
        cout<<endl;
    }

    int ans;
    if(map[startx-1][starty] == '|' || map[startx-1][starty] == 'F' || map[startx-1][starty] == '7')
        ans = dfs(startx,starty,startx-1,starty,map,isBorder);
    else if(map[startx+1][starty] == '|' || map[startx+1][starty] == 'L' || map[startx+1][starty] == 'J')
        ans = dfs(startx,starty,startx+1,starty,map,isBorder);
    else if(map[startx][starty+1] == '-' || map[startx][starty+1] == '7' || map[startx][starty+1] == 'J')
        ans = dfs(startx,starty,startx,starty+1,map,isBorder);

    cout<<"Part 1 "<<ans/2<<endl;

    map[startx][starty] = s_replace;

    int ans2 =0;
    
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(!isBorder[i][j]) {
                int curans = 0;
                for(int startx = i,starty = j;startx<n&&starty<m;startx++,starty++){
                    if(isBorder[startx][starty]&&map[startx][starty]!='7'&&map[startx][starty]!='L') curans = 1 - curans;
                }
                ans2+=curans;
            }
        }
    }
    cout<<"Part 2 "<<ans2<<endl;
}