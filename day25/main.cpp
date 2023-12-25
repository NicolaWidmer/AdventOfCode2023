#include <iostream>
#include <math.h>
#include <vector>
#include <set>
#include <algorithm>

// BGL include
#include <boost/graph/adjacency_list.hpp>

// BGL flow include *NEW*
#include <boost/graph/push_relabel_max_flow.hpp>

using namespace std;


// Graph Type with nested interior edge properties for flow algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;

typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;

// Custom edge adder class, highly recommended
class edge_adder {
  graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}

  void add_edge(int from, int to, long capacity) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    const auto e = boost::add_edge(from, to, G).first;
    const auto rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
  }
};

void dfs(int u,vector<bool> &vis,const vector<vector<int> > &g){
  if(vis[u]) return;
  vis[u] = true;
  for(auto v:g[u]) dfs(v,vis,g);
}

int main(){
  int n = 1190;
  set<string> nodes;
  map<string,vector<string> > g;
  
  string s;
  cin>>s;
  
  for(int i=0;i<n;i++){
    nodes.insert(s.substr(0,3));
    vector<string> to;
    string cur;
    cin>>cur;
    while(cur.size()==3){
      to.push_back(cur);
      nodes.insert(cur);
      cin>>cur;
    }
    g[s.substr(0,3)] = to;
    s = cur;
  }
  
  graph G(nodes.size());
  edge_adder adder(G);
  int i=0;
  for(auto it = nodes.begin();it!=nodes.end();it++){
    for(auto to:g[*it]){
      int j = distance(nodes.begin(),nodes.find(to));
      adder.add_edge(i,j,1);
      adder.add_edge(j,i,1);
    }
    i++;
  }
  
  int cut1 = 0;
  
  for(int i=1;i<nodes.size();i++){
      int flow = boost::push_relabel_max_flow(G, 0, i);
      if(flow == 3){
        
        vector<vector<int> > rev_graph(nodes.size());
        
        auto rev_map = boost::get(boost::edge_residual_capacity, G);
        graph::edge_iterator e_, eend_;
        for (boost::tie(e_, eend_) = boost::edges(G); e_ != eend_; ++e_) {
          int fr = boost::source(*e_, G);
          int to = boost::target(*e_, G);
          if(rev_map[*e_]!=0) rev_graph[fr].push_back(to);
        }
        
        vector<bool> vis(nodes.size());
        dfs(0,vis,rev_graph);
        for(int j = 0;j<nodes.size();j++){
          if(vis[j]) cut1++;
        }
        
        break;
      }
  }
  cout<<cut1*(nodes.size()-cut1)<<endl;

}