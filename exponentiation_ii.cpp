#include <iostream>
typedef long long ll;
using namespace std;

// IDEA: Fermat's little theorem
ll mod = 1000000007;
ll exp(ll a, ll b, ll MOD){
  if(b == 0) return 1;
  ll val = exp(a, b/2, MOD)%MOD;
  val *= val;
  val%=MOD;

  if(b%2 == 0) return val;

  return (val * a)%MOD;
}

int main(){
  int n; cin>>n;
  for(int i=0;i<n;i++){
    ll a, b, c; cin>>a>>b>>c;
    cout<<exp(a, exp(b, c, mod-1), mod)<<endl;
  }

}
