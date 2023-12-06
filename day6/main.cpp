#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>

#define int long

using namespace  std;


signed main(){
    int n=4;
    vector<int> time(n);
    vector<int> dist(n);
    string s;
    cin>>s;
    for(int i=0;i<n;i++){
        cin>>time[i];
    }
    cin>>s;
    for(int i=0;i<n;i++){
        cin>>dist[i];
    }


    int ans1=1;
    for(int i=0;i<n;i++){
        int d = dist[i];
        int t = time[i];
        int cur = 0;
        for(int v = 0;v<time[i];v++){
            if(v*(t-v)>=d) cur++;
        }
        ans1 *= cur;
    }

    int t2 = 53916768;
    int d2 = 250133010811025;
    /*  
        (t2 - x) * x = d2 => x^2 - t2*x + d2 = 0 =>
        x_1,2 = (t2 +- sqrt(t2^2-4*d2)) / 2
    */
    double disc = sqrt(t2*t2-4*d2);
    int ans2 = floor((t2 + disc)/2) - ceil((t2-disc)/2) + 1;

    cout<<"Part 1 "<<ans1<<endl;

    cout<<"Part 2 "<<ans2<<endl;
}