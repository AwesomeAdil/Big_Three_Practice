#include <iostream>
#include <algorithm>
typedef long long ll;
using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n; cin>>n;
  ll adjmat[n][n];
  int order[n];
  ll ans[n];
  bool allowed[n];
  for(int i=0;i<n;i++)
    for(int j=0;j<n;j++)
      cin>>adjmat[i][j];

  for(int i=0;i<n;i++){
    cin>>order[n-i-1];
    ans[i] = 0;
    allowed[i] = false;
  }

  for(int k=0;k<n;k++){
    int added = order[k]-1;
    allowed[added] = true;
    for(int i=0;i<n;i++){
      for(int j=0;j<n;j++){
        adjmat[i][j] = min(adjmat[i][j], adjmat[i][added] + adjmat[added][j]);
        if (i!=j && allowed[i] && allowed[j])
          ans[n-k-1]+=adjmat[i][j];
      }
    }
  }
  for(ll u: ans) cout<<u<<" ";
}
