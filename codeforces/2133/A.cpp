
#include<bits/stdc++.h>
using namespace std;

void solve(){
    int n; 
    cin>>n;
    vector<int> freq(101,0);
    bool ok=false;
    for(int i=0,x;i<n;i++){
        cin>>x;
        if(++freq[x]==2) ok=true;
    }
    cout<<(ok?"YES":"NO")<<"\n";
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int t=1;
    cin>>t;
    while(t--) solve();
}
