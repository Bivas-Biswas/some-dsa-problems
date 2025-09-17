#include <bits/stdc++.h>
using namespace std;
using int64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;
    vector<int> A(N);
    int maxA = 0;
    int64 total = 0;
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
        maxA = max(maxA, A[i]);
        total += A[i];
    }

    vector<int> B(Q);
    int maxB = 0;
    for (int i = 0; i < Q; ++i) {
        cin >> B[i];
        maxB = max(maxB, B[i]);
    }

    int M = max(maxA, maxB);
    vector<int64> freq(M + 1, 0);
    for (int v : A) freq[v]++;

    vector<int64> pref_cnt(M + 1, 0), pref_sum(M + 1, 0);
    pref_cnt[0] = freq[0];
    pref_sum[0] = 0 * freq[0];
    for (int v = 1; v <= M; ++v) {
        pref_cnt[v] = pref_cnt[v-1] + freq[v];
        pref_sum[v] = pref_sum[v-1] + freq[v] * (int64)v;
    }

    for (int i = 0; i < Q; ++i) {
        int b = B[i];
        int k = b - 1;
        if (k < 0) {
            cout << -1 << '\n';
            continue;
        }
        int64 cnt_le_k = (k <= M) ? pref_cnt[k] : pref_cnt[M];
        int64 sum_le_k = (k <= M) ? pref_sum[k] : pref_sum[M];
        int64 larger = N - cnt_le_k;
        int64 S = sum_le_k + (int64)k * larger; // S(b)
        if (S == total) {
            cout << -1 << '\n';
        } else {
            cout << (S + 1) << '\n';
        }
    }
    return 0;
}
