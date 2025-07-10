#include<bits/stdc++.h>

using namespace std;
using ll = long long;


// Find the total number of 1's present inside
// the number range [1...x]
// eg: 7 -> 12, 9 -> 15
ll sum_of_1_bits(ll x){
    ll ans = 0;
    ll total = x + 1; // [0..x] total (x - 0 + 1) = x + 1
    for(int i=0; i<60; i++){
        ll full = total / (1LL << (i+1));
        ll left = total % (1LL << (i+1));
        ll extra_one_in_left = max((left - (1LL << i)), 0LL);
        ans += full * (1LL << i);
        ans += extra_one_in_left;
    }
    return ans;
}

void solve(){
    int n;
    cin >> n;
    cout << sum_of_1_bits(n) << endl;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t = 1;
    cin >> t;
    while(t--) solve();
}
