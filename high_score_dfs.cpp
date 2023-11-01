#include <iostream>
#include <vector>
#include <utility>
typedef long long ll;
 using namespace std;

// Weight will never get this low.
ll neg_inf = -10000000000000;
 
ll n, m;
vector<ll> distances;
bool possible;
vector< pair<ll, pair<ll, ll> > > edges;
vector<ll> adjlist[2505];
bool connected [2505];
bool seen [2505];



// This DFS is used to see if node eventually connected to end point:
// Useful if there is a cycle but we dont know if it is possible to go
// from point in cycle to last point.
void DFS(ll i){
  if(connected[i]) return;
  seen[i] = true;
  for(ll spots : adjlist[i]){
    if(connected[spots] == true){
      connected[i] = true;
      return;
    }
    if(!seen[spots]){
      DFS(spots);
      if(connected[spots]){
        connected[i] = true;
        return;
      }
    }
  }
}
 
// Determines all points that are connected to the end.
void findConnected(){
  seen[n-1] = true;
  connected[n-1] = true;
  for(int i=0;i<n;i++){
    if(!connected[i]){
      for(int j =0 ;j<n-1;j++)seen[j] = false;
      DFS(i);
    }
  }
}

// Relax method of bellman ford, if no distances change (cant do better) then
// we break and stop iterating as this is the best it can be.
// Intuition: best answer only changes is best answer for some node changes before.
// if best stays the same for all, will stay forever
//
// Also note that if node not connected to end point improves, we dont care and dont count
// that as change.
bool relax(){
  bool relaxed = false;
  for(pair<ll, pair<ll, ll> > edge: edges){
    // Important check, if we cant get to this node the know that doesnt matter what edge weight we add.
    // Doesnt improve other result.
    if (distances[edge.first] == neg_inf) continue;
    if (connected[edge.second.first] && distances[edge.second.first] < distances[edge.first] + edge.second.second){
      distances[edge.second.first] = distances[edge.first] + edge.second.second;
      relaxed = true;
    }
  }
  return relaxed;
}
 
// For certain number of operations we see if we stop improving after a while.
// If we keep improving for more than N iterations, then we have a cycle.
void belmanFord(){
  for(int i=0;i<n;i++) distances.push_back(neg_inf);
  distances[0] = 0;
  for(int round = 0; round < n-1; round++){
    if(!relax())
      break;
  }
  possible = !relax();
}

// Find all nodes connected to end
int main(){
  cin>>n>>m;
  for(int i=0;i<m;i++){
    ll a, b, c; cin>>a>>b>>c;
    edges.push_back(make_pair(a-1, make_pair(b-1, c)));
    adjlist[a-1].push_back(b-1);
  }
  findConnected();
  belmanFord();
  if(!possible || distances[n-1] == -1){
    cout<<-1;
  }else{
    cout<<distances[n-1];
  }
  return 0;
}
