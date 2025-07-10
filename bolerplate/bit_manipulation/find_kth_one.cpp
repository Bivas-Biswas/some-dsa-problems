#include<bits/stdc++.h>

using namespace std;

using ll = long long;

ll sum_of_1_bits(ll x){
    ll ans = 0;
    ll total = x + 1; // [0..x] total (x - 0 + 1) = x + 1
    for(int i=0; i < 60; i++){
        ll full = total / (1LL << (i+1));
        ll left = total % (1LL << (i+1));
        ll extra_1_in_left = max((left - (1LL<<i)), 0LL);
        ans += full * (1LL << i);
        ans += extra_1_in_left;
    }

    // cout << x << " " << ans << endl;
    return ans;
}


bool check(ll x, ll k){
    return sum_of_1_bits(x) >= k;
}

// the integer where the kth bit belong
// eg. 10 -> 7, 15 -> 9
ll find_kth_one(ll k){
    ll low = 0, high = k, ans = -1;
    while(low <= high){
        ll mid = (low + high) >> 1;
        if(check(mid, k) == 1){
            ans = mid;
            high = mid -1;
        } else{
            low = mid + 1;
        }
    }

    return ans;
}

void solve(){
    ll n;
    cin >> n;
    cout << find_kth_one(n) << endl;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t = 1;
    cin >> t;
    while(t--) solve();
}

