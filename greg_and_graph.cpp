#include <iostream>
#include <algorithm>
typedef long long ll;
using namespace std;

/*
 * IDEA: We do the floyd warshals with an ordering (the reverse of the removals)
 * This way, we get that the last to remove is the equivalent to the first added.
 * Due to the nature of the floyd warshals, dp[i][j] will represent the min dist
 * at every dist when including all k nodes seen so far as intermediates. We then
 * only added allowed nodes to the sum to get the answers.
 */

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n; cin>>n;
  int order[n];
  bool allowed[n];
  ll adjmat[n][n];
  ll ans[n];

  // Read in adjacency matrix
  for(int i=0;i<n;i++)
    for(int j=0;j<n;j++)
      cin>>adjmat[i][j];

  // Read in and initialize auxilary and answer matricies
  for(int i=0;i<n;i++){
    cin>>order[n-i-1];
    ans[i] = 0;
    allowed[i] = false;
  }

  for(int k=0;k<n;k++){
    //intermediates allowed and note we account for ordering
    int added = order[k]-1;
    allowed[added] = true;
    for(int i=0;i<n;i++){
      for(int j=0;j<n;j++){
        adjmat[i][j] = min(adjmat[i][j], adjmat[i][added] + adjmat[added][j]);
        // Check if this are nodes in graph
        if (i!=j && allowed[i] && allowed[j])
          ans[n-k-1]+=adjmat[i][j];
      }
    }
  }
  for(ll u: ans) cout<<u<<" ";
}
