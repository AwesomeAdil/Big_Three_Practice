#include <iostream>
typedef long long ll;
using namespace std;
ll MOD = 1000000007;
ll exp(ll a, ll b){
  if(b == 0) return 1;
  ll val = exp(a, b/2)%MOD;
  val *= val;
  val%=MOD;
  
  if(b%2 == 0) return val;
  return (val * a)%MOD;
}

int main(){
  int n; cin>>n;
  for(int i=0;i<n;i++){
    ll a, b; cin>>a>>b;
    cout<<exp(a, b)<<endl;
  }
}
