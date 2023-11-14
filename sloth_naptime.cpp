#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

vector<int> adjlist[300005];
int ancestor[300005][21];
int depths[300005];

void DFS(int spot, int parent, int depth){
  ancestor[spot][0] = parent;
  depths[spot] = depth;
  for(int i=1;i<21;i++)
    ancestor[spot][i] = ancestor[ancestor[spot][i-1]][i-1];

  for(int u: adjlist[spot])
    if(u!=parent)
      DFS(u,spot, depth+1);
}

int kthAncestor(int x, int k){
  for(int i=0;i<21;i++)
    if((k>>i) & 1) x = ancestor[x][i];
  return x;
}

int LCA(int a, int b){
  if(depths[a]>depths[b]) swap(a, b);
  b = kthAncestor(b, depths[b]-depths[a]);
  if(a==b) return a;
  for(int i=20;i>=0; i--){
    if(ancestor[a][i] != ancestor[b][i]){
      a = ancestor[a][i];
      b = ancestor[b][i];
    }
  }
  return ancestor[a][0];
}

int dist_between(int a, int b){
  return depths[a] + depths[b] - 2*depths[LCA(a, b)];
}

int main(){
  int n; cin>>n;
  for(int i=0;i<n-1;i++){
    int a,b; cin>>a>>b;
    adjlist[a].push_back(b);
    adjlist[b].push_back(a);
  }

  DFS(1,0,1);
  int q; cin>>q;
  for(int i=0; i<q;i++){
    int a, b, c; cin>>a>>b>>c;
    int lca = LCA(a, b);
    if(dist_between(a, b) <= c) cout<<b<<endl;
    else if(dist_between(a, lca) >= c) cout<<kthAncestor(a, c)<<endl;
    else cout<<kthAncestor(b, dist_between(a, b) - c)<<endl;
  }
}
