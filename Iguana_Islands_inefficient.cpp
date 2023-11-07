#include <iostream>
#include <unordered_map>
#include <set>
using namespace std;

// Let dp[i][j] store the mex or grundy number of the case of food amt i and removal amt j
unordered_map<int, unordered_map<int, int> > dp;
unordered_map<int, unordered_map<int, bool> > seen;
int convert(int a, int b){
  if(a==0) return 0;
  if(b==1) return a%2;
  if(seen[a][b]) return dp[a][b];

  int best = convert(a-1, b);
  set<int> excludents;
  excludents.insert(best);
  int change = b;
  while(a>=b){
    int amt = convert(a-b,change);
    excludents.insert(amt);
    b*=change;
  }
  int start = 0;
  for(int exc : excludents){
    if(start != exc){
      dp[a][change] = start;
      seen[a][change] = true;
      return start;
    }else{
      start+=1;
    }

  }
  dp[a][change] = start;
  seen[a][change] = true;
  return start;
}


int main(){
  int n, q; cin>>n>>q;
  int amts[n];
  int fruits[n];
  int convs[n];
  for(int i=0;i<n;i++) cin>>amts[i];
  for(int i=0;i<n;i++) cin>>fruits[i];
  for(int i=0;i<n;i++) convs[i] = convert(fruits[i], amts[i]);
  int pre_convs[n+1];
  pre_convs[0] = 0;
  for(int i=0;i<n;i++) pre_convs[i+1] = pre_convs[i] ^ convs[i];


  while(q--){
    int l, r; cin>>l>>r;
    if(pre_convs[r]^pre_convs[l-1]){
      cout<<"Ivan"<<endl;
    }else{
      cout<<"Isabel"<<endl;
    }
  }
}

