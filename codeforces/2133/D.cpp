#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve() {
    int n;
    cin >> n;
    vector<long long> h(n+1);
    long long total = 0;
    for (auto x : h) total += x;
    long long ans = LLONG_MAX;
    for (int i = 0; i+1 < n; i++) {
        ans = min(ans, total - h[i] - h[i+1] + max(h[i], h[i+1]));
    }

    cout << ans << "\n";
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
