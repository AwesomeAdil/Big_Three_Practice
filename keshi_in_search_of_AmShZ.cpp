#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
typedef long long ll;
using namespace std;


struct location{
  ll spot;
  ll dist;
  ll mag; // Number of edges going into that path : useful if its one of the best paths as that means we dont have to spend days blocking these edges
  ll uc_dist; // dist of parent to keep track of worst
  ll par; // for debugging
  bool operator>(const location& other) const{
    return dist > other.dist;
  }
};


ll INF = 2147483646;



 // Ok so here is the idea, weights of outgoing edges are
  // are the outdegree of the current node (all edges out have same weight initially)
  // Then, going backwards, we see if there are 2 or more nodes outgoing that have the same 
  // distance away from the end point node, we can make the distance (#of nodes with same weight - 1) lighter 
  // i.e substract that from the min dist, NOTE FOR change with multiple outgoing edges, we need to make it
  // - num edges outgoing instead, also we need relax to help compare two paths.
  

  // New idea, we do the Dijstras backwards, calculates all the min dists from all nodes to last node,
  // however, if there were two ways to get to the same node with the same weight, we can relax by 1 more
  //
  //

  // OK so that didnt work because of multiple edges so i tried only accounting for one of the edges outward
  //
  // BUT thats not good because we would need to close multiple edges of same street so keep a count of num edges going that way
  //
  //
  // BUT NOW algo breaks, because if we spend too much time closing bridges we could just take less efficient path and finish faster
  // So we will have to min it with outgoing dists
  //
  //
  // Ok so having trouble figuring out when its better to just ignore it, so lets have that as a dist threshold, we have it be the worst choice
  // I think this will require a BFS
  //
  //
  // Ok so we didnt do that but we made some progress, instead, we will keep track of which outgoing nodes are still yet to come from the dijstras,
  // even the bad ones, then we keep track of the weights of the worst of the paths for each node, if we have already seen all the bad nodes, then
  // we will set the dist to be either the smallest of all those nodes or stay the same (depending if we shouldnt waste time blocking roads)
  // (done by keeping track of all the forward edges unexplored in forward_adj set, if we explore all forward edges dist = min(dist, worst_case + 1))
  //
  // 
  //
  // Had memory issue prob from the priority_queue getting too big so we had to reduce its size by limiting amount of stuff we push in
  // by only taking the node if the determine if we take the worst case or not, or if the path is better.
  //
  //
  // Had to fix previous mistake of not ordering the items of the dijstras like i should have
  //





int main(){
  cin.sync_with_stdio(false);
  cin.tie(NULL);

  int n, m; cin>>n>>m;
  if(n==2){
    cout<<1;
    return 0;
  }
  // PQ for Dijstras
priority_queue<location, vector<location>, greater<location> > pq;

// Tells us how many edges going opposite direction
unordered_map<ll, ll> backward_mag[n+1];
// All the in going edges
unordered_set<ll> backward_adj[n+1];
// All outgoing edges (important to see if we can use the worst case)
unordered_set<ll> forward_adj[n+1];

// Out degree of each node
ll out_degree[n+1];
// Dists storage
ll dists[n+1];
// REALLY IMPORANT: If multiple paths are equally good but we alter the distance function already
// this helps keep everything fair by undoing the change by the lack of subtraction of edges
ll relaxed[n+1];
ll worst_case[n+1];
ll add[n+1];

  // Number of outgoing edges we allow -> more if two paths to the end with same weight
  for(int i=1;i<=n;i++) {
    relaxed[i] = 0;
    dists[i] = INF;
    worst_case[i] = 0;
    out_degree[i] = 0;
    add[i] = 0;
  }

  for(int i=0;i<m;i++){
    ll a,b; cin>>a>>b;
    backward_mag[b][a]+=1;
    forward_adj[a].insert(b);
    backward_adj[b].insert(a);
    out_degree[a]+=1;
  }



 
  // Part 1: Keep track of all the distances from start node with this metric
  // Dijstras
  pq.push((location){n, 0, 0, 0, -1});
  while(!pq.empty()){
    location top = pq.top();
    cout<<top.spot<<" "<<top.dist<<" "<<top.uc_dist+1<<" "<<top.par<<endl;
    pq.pop();
    // Old news
    if(top.spot != n&& forward_adj[top.spot].size() == 0){
      //cout<<"EXPOLORED\n";
      continue;
    }

    forward_adj[top.spot].erase(top.par);
    //cout<<"SIZE "<<forward_adj[top.spot].size()<<endl;
    //cout<<"WORSTB "<<worst_case[top.spot]<<" "<<top.uc_dist<<endl;
    worst_case[top.spot] = max(worst_case[top.spot], top.uc_dist);
    //cout<<"WORSTA "<<worst_case[top.spot]<<endl;
    if(dists[top.spot] + relaxed[top.spot] < top.dist){
      //cout<<"Huh? "<<top.dist<<endl;
      if(forward_adj[top.spot].size() == 0){
        cout<<"THIS IS THE WORST "<<top.spot<<" "<<dists[top.spot]<<" "<<worst_case[top.spot]+1<<endl;
        if(worst_case[top.spot]+1 < dists[top.spot]){
          cout<<"taking worse1\n";
          relaxed[top.spot] = 0;
          dists[top.spot] = worst_case[top.spot]+1;
          //cout<<"NEW DIST: "<<dists[top.spot]<<endl;
        }
      }else{
        continue;
          
      }
    }else{
      if(dists[top.spot]!=INF){
        dists[top.spot]-=top.mag;
        relaxed[top.spot]+=top.mag;
      }else{
        dists[top.spot] = top.dist;
      }
      if(forward_adj[top.spot].size() == 0){
        //cout<<"THIS IS THE WORST "<<top.spot<<" "<<dists[top.spot]<<" "<<worst_case[top.spot]+1<<endl;
        if(worst_case[top.spot]+1 < dists[top.spot]){
          cout<<"taking worse2\n";
          relaxed[top.spot] = 0;
          dists[top.spot] = worst_case[top.spot]+1;
          //cout<<"NEW DIST: "<<dists[top.spot]<<endl;
        }
      }
    }




    for(ll u: backward_adj[top.spot]){
     // if(forward_adj[u].size() == 0) continue;
      //if((dists[u] + relaxed[u] < top.dist + out_degree[u] - backward_mag[top.spot][u] + 1) && forward_adj[u].size() > 1){
       // forward_adj[u].erase(top.spot);
       // worst_case[u] = max(worst_case[u], dists[top.spot]);
        //continue;
      //} 
      //if((dists[u] + relaxed[u] >= top.dist + out_degree[u] - backward_mag[top.spot][u] + 1) || (forward_adj[u].size() == 1 && forward_adj[u].find(top.spot) != forward_adj[u].end())){
      pq.push((location){u, top.dist + out_degree[u] - backward_mag[top.spot][u] + 1 - add[u], backward_mag[top.spot][u], dists[top.spot], top.spot});
      //}
      //else{
        //forward_adj[u].erase(top.spot);
        //worst_case[u] = max(worst_case[u], dists[top.spot]);
      //}
    }
  }
  
 
cout<<dists[1]<<endl;

for(int i=1;i<=n;i++) cout<<dists[i]<<" ";
for(int i=1;i<=n;i++) cout<<worst_case[i]<<" ";



}
