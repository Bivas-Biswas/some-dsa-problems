#include <bits/stdc++.h>
using namespace std;

void solve() {
    string s;
    cin >> s;
    int n = s.size();

    vector<int> prefix_t(n+1, 0);
    for (int i = 0; i < n; i++) {
        prefix_t[i+1] = prefix_t[i] + (s[i] == 't');
    }

    vector<int> tpos;
    for (int i = 0; i < n; i++)
        if (s[i] == 't')
            tpos.push_back(i);

    long double ans = 0.0;

    for (int i = 0; i < (int)tpos.size(); i++) {
        for (int j = i+1; j < (int)tpos.size(); j++) {
            int start = tpos[i];
            int end   = tpos[j];
            int len   = end - start + 1;
            if (len < 3) continue;
            int x = prefix_t[end+1] - prefix_t[start];
            if (x <= 2) continue;
            long double rate = ( (long double)x - 2 ) / ( (long double)len - 2 );
            ans = max(ans, rate);
        }
    }

    cout << fixed << setprecision(17) << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
