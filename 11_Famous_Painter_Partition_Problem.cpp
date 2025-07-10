#include <bits/stdc++.h>

using namespace std;
#define endl "\n";

int n, k;
int x[100100];

bool check(int s){
    int curr = -1;
    int cnt = 0;
    for(int i = 0; i < n; i++){
        if(curr >= x[i]){
            curr -= x[i];
        } else {
            curr = s - x[i];
            cnt++;
        }
        if(cnt > k) return 0;
    }
    if(cnt > k) return 0;
    return 1;
}

void solve() {
    // Your code goes here
    cin >> n >> k;
    int lo = 0, hi = 0;
    for(int i = 0; i < n; i++){
        cin >> x[i];
        lo = max(lo, x[i]);
        hi += x[i];
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
    cin  >> t;
    while(t--){
        // Call your solve function or write code here
        solve();
    }
    return 0;
}