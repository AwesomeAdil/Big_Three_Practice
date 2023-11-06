#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <fstream>
typedef long long ll;
#define pl pair<ll, ll>
using namespace std;

struct location{
  ll dist;
  ll spot;
  ll parent; // the one required to get here
   bool operator>(const location& other) const
    {
        return dist > other.dist;
    }
};

ll n, m;
priority_queue< location ,vector<location>, greater< location > > pq;
vector< pl > adjlist[100005];
ll distances[100005];
ll parents[100005];
ll depth[100005];
ll ancestors[100005][20];
ll INF = 1000000000000005;


// Method for finding kth ancestor
ll findAncestor(ll a, ll k){
  ll spot = a;
  for(int i=0;i<20;i++){
    if(spot == 0) break;
    if((k>>i) & 1) spot = ancestors[spot][i];
  }
  return spot;
}


// Calculated Lowest Common Ancestor
ll LCA(ll a, ll b){
  if(depth[b]<depth[a]) swap(a,b);
  b = findAncestor(b, depth[b]-depth[a]); 

  //If already match
  if(a==b) return a;

  //Stops right before the LCA
  for(int i=19;i>=0;i--){
    if(ancestors[a][i] != ancestors[b][i]){
      a = ancestors[a][i];
      b = ancestors[b][i];
    }
  }
  // Right below it now so need to take parent
  return ancestors[a][0] ;
}


int main(){
  cin>>n>>m;
  for(int i=1;i<=n;i++){
    distances[i] = INF;
    parents[i]=-1;
  }

  for(int i=0;i<m;i++){
    ll a, b, c;
    cin>>a>>b>>c;
    adjlist[a].push_back(make_pair(b,c));
  }
  location init;
  init.dist = 0;
  init.spot = 1;
  init.parent = 0;
  pq.push(init);

  depth[1] = 0;
  while(!pq.empty()){
    location top = pq.top();
    pq.pop();

    // Old news (not best path)
    if(top.dist > distances[top.spot]) continue;
    
    //cout<<top.spot<<endl;

    // If we go back to a node and fix its parent we dont wanna add nodes again
    // But we still need to fix its ancestors, for breaking afterwards.
    bool checked_before = false;

    //If there are multiple connections we point to where they both rely
    if(parents[top.spot] != -1){
      ll moo = parents[top.spot];
      parents[top.spot] = LCA(parents[top.spot], top.parent);
        depth[top.spot] = depth[parents[top.spot]]+1;
        checked_before = true;
    }else{
      distances[top.spot] = top.dist;
      parents[top.spot] = top.parent;
      depth[top.spot] = depth[parents[top.spot]]+1;;
    }

    // Calculate Binary Ancestors
    //
    // Had bug here for the longest time, not allowed to break
    // because we need to fix all previous ancestors.
    ancestors[top.spot][0] = parents[top.spot];
    for(int i=1;i<20;i++)
        ancestors[top.spot][i] = ancestors[ancestors[top.spot][i-1]][i-1];
    

    // Neccessary check, we dont wanna add edges if we've seen this node already
    if(checked_before) continue;

    //Dijkstras
    for(pl u: adjlist[top.spot]){
      if(distances[u.first] < top.dist + u.second) continue;
      location new_loc;
      new_loc.dist = top.dist+u.second;
      new_loc.spot = u.first;
      new_loc.parent = top.spot;
      pq.push(new_loc);
    }
  }

  // Formatting output
  ll spot = n;
  vector<ll> ans;
  ll num = 0;
  while(spot!=0){
    num+=1;
    ans.push_back(spot);
    spot = parents[spot];
  }
  sort(ans.begin(),ans.end());
  cout<<num<<endl;
  for(ll part : ans){
    cout<<part<<" ";
  }
}
