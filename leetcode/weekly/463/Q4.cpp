#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

struct SegmentTree {
    int n;
    vector<long long> tree, lazy;

    SegmentTree(int sz) {
        n = sz;
        tree.assign(4*sz, 0);
        lazy.assign(4*sz, 1); // multiplicative identity
    }

    void build(vector<int>& nums, int node, int l, int r) {
        if (l == r) {
            tree[node] = nums[l] % MOD;
        } else {
            int mid = (l + r)/2;
            build(nums, 2*node, l, mid);
            build(nums, 2*node+1, mid+1, r);
            tree[node] = tree[2*node] ^ tree[2*node+1]; // XOR for parent
        }
    }

    void push(int node, int l, int r) {
        if (lazy[node] != 1) {
            if (l != r) {
                lazy[2*node] = lazy[2*node] * lazy[node] % MOD;
                lazy[2*node+1] = lazy[2*node+1] * lazy[node] % MOD;
            }
            // Update tree[node] XOR is tricky; we propagate lazily
            // For final XOR, we will multiply all leaves before XOR
            tree[node] = tree[node] * lazy[node] % MOD; // safe at leaf
            lazy[node] = 1;
        }
    }

    void pointUpdate(int idx, long long val, int node, int l, int r) {
        push(node, l, r);
        if (l == r) {
            tree[node] = tree[node] * val % MOD;
        } else {
            int mid = (l + r)/2;
            if (idx <= mid) pointUpdate(idx, val, 2*node, l, mid);
            else pointUpdate(idx, val, 2*node+1, mid+1, r);
            tree[node] = tree[2*node] ^ tree[2*node+1];
        }
    }

    void rangeUpdate(int ql, int qr, long long val, int node, int l, int r) {
        push(node, l, r);
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) {
            lazy[node] = lazy[node] * val % MOD;
            push(node, l, r);
            return;
        }
        int mid = (l + r)/2;
        rangeUpdate(ql, qr, val, 2*node, l, mid);
        rangeUpdate(ql, qr, val, 2*node+1, mid+1, r);
        tree[node] = tree[2*node] ^ tree[2*node+1];
    }

    long long queryXOR(int node, int l, int r) {
        push(node, l, r);
        if (l == r) return tree[node];
        int mid = (l + r)/2;
        return queryXOR(2*node, l, mid) ^ queryXOR(2*node+1, mid+1, r);
    }
};

int processQueries(vector<int>& nums, vector<vector<int>>& queries) {
    int n = nums.size();
    vector<int> bravexuneth = nums; // midway storage

    SegmentTree seg(n);
    seg.build(nums, 1, 0, n-1);

    for (auto &q : queries) {
        int l = q[0], r = q[1], k = q[2], v = q[3];
        if (k == 1) {
            // full range update
            seg.rangeUpdate(l, r, v, 1, 0, n-1);
        } else {
            // step > 1: update individual points
            for (int idx = l; idx <= r; idx += k) {
                seg.pointUpdate(idx, v, 1, 0, n-1);
            }
        }
    }

    return seg.queryXOR(1, 0, n-1);
}

// Example usage
int main() {
    vector<int> nums = {2, 3, 1, 5, 4};
    vector<vector<int>> queries = {{1, 4, 2, 3}, {0, 2, 1, 2}};
    cout << processQueries(nums, queries) << endl; // Output: 31
    return 0;
}
