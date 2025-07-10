#include <bits/stdc++.h>

using namespace std;
#define endl "\n"
#define int long long

int n, k;
int x[100100];

bool check(int s){
    int needed = 0;
    for(int i=1; i < n; i++){
        int d = x[i] - x[i-1];
        needed += ((d + s - 1) / s) - 1;
        if(needed > k) return 0;
    }
    if(needed > k) return 0;
    return 1;
}
void solve() {
    // Your code goes here
    cin >> n >> k;
    int lo = 1, hi = 0;
    for(int i = 0; i< n; i++){
        cin >> x[i];
        if(i){
            hi = max(hi, x[i] - x[i - 1]);
        }
    }

    int ans = 0;
    while(lo <= hi){
        int mid = (lo + hi) / 2;
        if(check(mid) == 0){
            lo = mid + 1;
        } else {
            ans = mid;
            hi = mid - 1;
        }
    }
    cout << ans << endl;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int t;
    cin >> t;
    while(t--){
        // Call your solve function or write code here
        solve();
    }
    return 0;
}