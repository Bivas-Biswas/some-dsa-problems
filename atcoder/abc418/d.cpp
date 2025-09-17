#include <bits/stdc++.h>
using namespace std;
using int64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    string T;
    cin >> N >> T;

    int64 cnt[2] = {0, 0};
    int parity = 0;
    cnt[parity]++;

    for (char c : T) {
        if (c == '0') parity ^= 1;
        cnt[parity]++;
    }

    auto choose2 = [](int64 x) -> int64 {
        return x * (x - 1) / 2;
    };

    int64 ans = choose2(cnt[0]) + choose2(cnt[1]);
    cout << ans << '\n';
    return 0;
}
