#include <iostream>
#include <unordered_map>
#include <set>
using namespace std;



// This is the main part of the algorithm that calculates Grundy Number
// Must see through observation, before was calculating grundy numbers
// using dp, however, this observation speeds up memory, 
int convert(int a, int b){
  if((a%(b+1))%2) return 1;
  if(a%(b+1) == b) return 2;
  return 0;
}


int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  // Input parsing
  int n, q; cin>>n>>q;
  int amts[n];
  int fruits[n];
  int convs[n];
  for(int i=0;i<n;i++) cin>>amts[i];
  for(int i=0;i<n;i++) cin>>fruits[i];

  //Storing the Grundy Numbers for all games
  for(int i=0;i<n;i++) convs[i] = convert(fruits[i], amts[i]);


  int pre_convs[n+1];
  pre_convs[0] = 0;

  // Prefix Xor for better range calcultation
  for(int i=0;i<n;i++) pre_convs[i+1] = pre_convs[i] ^ convs[i];


  while(q--){
    int l, r; cin>>l>>r;

    // We know it works if the xor of range of grundy numbers is not 0
    if(pre_convs[r]^pre_convs[l-1]){
      cout<<"Ivan"<<endl;
    }else{
      cout<<"Isabel"<<endl;
    }
  }
}
