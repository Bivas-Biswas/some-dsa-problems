#include<bits/stdc++.h>
using namespace std;

using ll = long long;

// find the total number of bit present in [0....x]
// x = 4, [0(0), 1(1), 2(10), 3(11), 4(100)] =  011011100 -> 9
// jump happen by power of 2 
// TC = logN
ll total_bit_till(ll x){
    ll ans = 0;
    ll num = 1;
    ll len = 1;
    while(num <= x){
        ll same_till = (num * 2LL) - 1;
        if(same_till <= x){
            ans += len * (same_till - num + 1LL);
            num = same_till + 1;
            len++;
        }else{
            ans += len * (x - num + 1LL);
            break;
        }
        // cout << same_till << " " << num << endl;
    }

    // include 0, because ans have [1...x]
    ans = ans + 1;
    return ans;
}

void solve(){
    ll n;
    cin >> n;
    cout << total_bit_till(n) << endl;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int t = 1;
    cin >> t;
    while(t--) solve();
}