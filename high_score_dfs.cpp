#include <iostream>
#include <vector>
#include <utility>
typedef long long ll;
 
using namespace std;
ll neg_inf = -10000000000000;
 
ll n, m;
vector<ll> distances;
bool possible;
vector< pair<ll, pair<ll, ll> > > edges;
vector<ll> adjlist[2505];
bool connected [2505];
bool seen [2505];
 
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
bool relax(){
  bool relaxed = false;
  for(pair<ll, pair<ll, ll> > edge: edges){
    if (distances[edge.first] == neg_inf) continue;
    if (connected[edge.second.first] && distances[edge.second.first] < distances[edge.first] + edge.second.second){
      distances[edge.second.first] = distances[edge.first] + edge.second.second;
      relaxed = true;
    }
  }
  return relaxed;
}
 
void belmanFord(){
  for(int i=0;i<n;i++) distances.push_back(neg_inf);
  distances[0] = 0;
  for(int round = 0; round < n-1; round++){
    if(!relax())
      break;
  }
  possible = !relax();
}
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
