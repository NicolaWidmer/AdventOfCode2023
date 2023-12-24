#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/intersections.h>
#include <boost/optional/optional_io.hpp>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;


using namespace  std;

#define int long


signed main(){
    int n = 300; 
    vector<vector<int> > traj(n);
    int upper = 400000000000000;
    int lower = 200000000000000;
    CGAL::Iso_rectangle_2<K> box(K::Point_2(lower,lower),K::Point_2(upper,upper));

    for(int i=0;i<n;i++){
        int a;
        char c;
        for(int j=0;j<6;j++){
            cin>>a;
            traj[i].push_back(a);
            if(j==5) break;
            cin>>c;
        }
    }
    int ans = 0;
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            vector<int> tra1 = traj[i];
            vector<int> tra2 = traj[j];
            K::Point_2 p1(tra1[0],tra1[1]), q1(tra1[0]+tra1[3],tra1[1]+tra1[4]);
            K::Ray_2 ray1(p1,q1);
            K::Point_2 p2(tra2[0],tra2[1]), q2(tra2[0]+tra2[3],tra2[1]+tra2[4]);
            K::Ray_2 ray2(p2,q2);
            
          if(CGAL::do_intersect(ray1,ray2)){
            auto result = intersection(ray1,ray2);
            if (K::Point_2 *intersection_point = boost::get<K::Point_2>(&*result)) {
                cout<<*intersection_point<<endl;
                if(CGAL::do_intersect(box,*intersection_point)) ans++;
            } else if (auto intersection_segment = boost::get<K::Segment_2>(&*result)) {
              cout<<"same line"<<endl;
            }
          }
        }
    }
    cout<<ans<<endl;
}