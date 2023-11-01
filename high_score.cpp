#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
typedef long long ll;
 
using namespace std;
ll neg_inf = -10000000000000;
 
ll n, m;
vector<ll> distances;
bool possible;
vector< pair<ll, pair<ll, ll> > > edges;
int groups[2505];
int ranks[2505];
int breaker = -1;


int findParent(int i){
  return (groups[i] != i) ? findParent(groups[i]) : i;
}

void connect(int a, int b){
  int A = findParent(a);
  int B = findParent(b);
  if(A==B) return;
  if(A == n-1){
    groups[B] = A;
    ranks[A] = max(ranks[A], ranks[B]+1);
    return;
  }
  if(B == n-1){
    groups[A] = B;
    ranks[B] = max(ranks[B], ranks[A]+1);
    return;
  }
  if(ranks[A] >= ranks[B]){
    groups[B] = A;
    ranks[A] = max(ranks[B]+1, ranks[A]);
  }else{
    groups[A] = B;
  }
}

void findConnectedToCycle(){
  for(int i=0;i<n;i++){
    groups[i] = i;
    ranks[i] = 1;
  }

  for(int i=0;i<n; i++){
    for(pair<ll, pair<ll, ll> > edge : edges)
      if(findParent(edge.first) != n-1 && findParent(edge.second.first) == n-1)
        connect(edge.first, edge.second.first);
  }
}

bool relax(){
  breaker = -1;
  bool relaxed = false;
  for(pair<ll, pair<ll, ll> > edge: edges){
    if (distances[edge.first] == neg_inf) continue;
    if (distances[edge.second.first] < distances[edge.first] + edge.second.second){
      distances[edge.second.first] = distances[edge.first] + edge.second.second;
      relaxed = true;
      if(findParent(edge.second.first) == n-1) breaker = edge.second.first;
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
  if(breaker==-1){
    possible = true;
  }
}

int main(){
  cin>>n>>m;
  for(int i=0;i<m;i++){
    ll a, b, c; cin>>a>>b>>c;
    edges.push_back(make_pair(a-1, make_pair(b-1, c)));
  }
  findConnectedToCycle();
  belmanFord();
  if(!possible || distances[n-1] == -1){
    cout<<-1;
  }else{
    cout<<distances[n-1];
  }
  return 0;
}

