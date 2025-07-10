#include <bits/stdc++.h>

using namespace std;
#define endl "\n"
#define int long long


int sum_of_digit(int x){
    int s = 0;
    while(x){
        s += x % 10;
        x /= 10;
    }
    return s;
}

bool check(int x, int s){
    return (x - sum_of_digit(x) >= s);
}

void solve() {
    int n, s;
    // Your code goes here
    cin >> n >> s;
    int lo = 1;
    int hi = n;
    int ans = n + 1;
    while(lo <= hi){
        int mid = (lo + hi) / 2;
        if(check(mid, s) == 0){
            lo = mid + 1;
        } else {
            ans = mid;
            hi = mid - 1;
        }
    }

    cout << (n - ans + 1) << endl;
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