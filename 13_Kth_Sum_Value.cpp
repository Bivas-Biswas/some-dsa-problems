#include <bits/stdc++.h>

using namespace std;
#define endl "\n"
#define int long long

int n,m,k;
vector<int> a, b;

bool check(int x){
    int cnt = 0;
    for(int i=0; i < n; i++){
        cnt += upper_bound(b.begin(), b.end(), x - a[i]) - b.begin();
    }

    return cnt >= k;
}

void solve() {
    // Your code goes here
    cin >> n >> m >> k;
    a.resize(n);
    b.resize(m);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }

    for(int i = 0; i < m; i++){
        cin >> b[i];
    }

    if(n > m){
        swap(n, m);
        swap(a, b);
    }

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    int lo = a[0] + b[0];
    int hi = a[n-1] + b[m-1];
    int ans = lo;

    while(lo <= hi){
        int mid = (lo + hi)/2;
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