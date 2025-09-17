#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
public:
    vector<int> t; // stores count of odd numbers
    
    SegmentTree(int n) {
        t.resize(4 * n);
    }

    SegmentTree() {}

    void init(int n) {
        t.resize(4 * n);
    }

    // Build tree: store 1 if arr[l] is odd, else 0
    void build(int idx, int l, int r, vector<int>& arr) {
        if (l == r) {
            t[idx] = (arr[l] % 2 == 1);
            return;
        }
        int mid = (l + r) >> 1;
        build(idx * 2, l, mid, arr);
        build(idx * 2 + 1, mid + 1, r, arr);
        t[idx] = t[idx * 2] + t[idx * 2 + 1];
    }

    // Update: set arr[val_idx] = val
    void update(int idx, int l, int r, int val_idx, int val) {
        if (l == r) {
            t[idx] = (val % 2 == 1);
            return;
        }
        int mid = (l + r) >> 1;
        if (val_idx <= mid)
            update(idx * 2, l, mid, val_idx, val);
        else
            update(idx * 2 + 1, mid + 1, r, val_idx, val);
        t[idx] = t[idx * 2] + t[idx * 2 + 1];
    }

    // Query count of odds in range [lq, rq]
    int query(int idx, int l, int r, int lq, int rq) {
        if (l > rq || r < lq) return 0; // outside
        if (lq <= l && r <= rq) return t[idx]; // inside
        int mid = (l + r) >> 1;
        return query(idx * 2, l, mid, lq, rq) +
               query(idx * 2 + 1, mid + 1, r, lq, rq);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<int> arr(N);
    for (int i = 0; i < N; i++) cin >> arr[i];

    SegmentTree segt(N);
    segt.build(1, 0, N - 1, arr);

    int Q;
    cin >> Q;
    while (Q--) {
        int type, x, y;
        cin >> type >> x >> y;
        if (type == 0) {
            // Update: set A[x] = y (convert x to 0-index)
            segt.update(1, 0, N - 1, x - 1, y);
        } else {
            // Query: count odds in [l, r] (convert to 0-index)
            cout << segt.query(1, 0, N - 1, x - 1, y - 1) << "\n";
        }
    }

    return 0;
}
