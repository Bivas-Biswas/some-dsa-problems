#include <bits/stdc++.h>
using namespace std;

// Segment Tree implementation for range sum queries and point updates
class SegmentTree {
public:
    vector<int> t; // Segment tree array
    
    // Constructor: initialize tree size for n elements
    SegmentTree(int n) {
        t.resize(4 * n); // why 4n find your own??
    }

    SegmentTree() {
    }

    // Initialize tree with size n
    void init(int n) {
        t.resize(4 * n);
    }

    // in majority of segment tree problem just need to modify this check function only
    int check(int a, int b){
        return a + b;
    }

    // Build segment tree from input array `arr`
    void build(int idx, int l, int r, vector<int>& arr) {
        if (l == r) { // Leaf node
            t[idx] = arr[l];
            return;
        }

        int mid = (l + r) >> 1;
        build(idx * 2, l, mid, arr);           // Build left child
        build(idx * 2 + 1, mid + 1, r, arr);   // Build right child
        t[idx] = check(t[idx * 2], t[idx * 2 + 1]); // Store sum of children
    }

    // Update element at index `val_idx` with value `val`
    void update(int idx, int l, int r, int val_idx, int val) {
        if (l == r) { // Leaf node: direct update
            t[idx] = val;
            return;
        }

        int mid = (l + r) >> 1;
        if (val_idx <= mid) {
            update(idx * 2, l, mid, val_idx, val);     // Update in left child
        } else {
            update(idx * 2 + 1, mid + 1, r, val_idx, val); // Update in right child
        }
        // Recompute sum for current node
        t[idx] = check(t[idx * 2], t[idx * 2 + 1]);
    }

    // Query sum in range [lq, rq]
    int sumRange(int idx, int l, int r, int lq, int rq) {
        if (l > rq || r < lq) return 0; // Completely outside range

        if (lq <= l && r <= rq) { // Completely inside range
            return t[idx];
        }
        
        int mid = (l + r) >> 1;
        // Query left and right children and sum results
        return sumRange(idx * 2, l, mid, lq, rq) + 
               sumRange(idx * 2 + 1, mid + 1, r, lq, rq);
    }
};

// Wrapper class for NumArray using Segment Tree
class NumArray {
public:
    SegmentTree segt; // Segment tree instance
    int n;            // Size of array
    
    // Constructor: build segment tree from nums
    NumArray(vector<int>& nums) {
        n = nums.size();
        segt.init(n);
        segt.build(1, 0, n - 1, nums);
    }
    
    // Update nums[index] = val
    void update(int index, int val) {
        segt.update(1, 0, n - 1, index, val);
    }
    
    // Query sum of nums[left..right]
    int sumRange(int left, int right) {
        return segt.sumRange(1, 0, n - 1, left, right);
    }
};

/**
 * Example Usage
 */
int main() {
    vector<int> nums = {1, 3, 5};
    NumArray* obj = new NumArray(nums);

    // Query sum in range [0,2] → 1 + 3 + 5 = 9
    cout << obj->sumRange(0, 2) << endl;  // Output: 9

    // Update index 1 → set nums[1] = 2 (nums = {1,2,5})
    obj->update(1, 2);

    // Query sum in range [0,2] → 1 + 2 + 5 = 8
    cout << obj->sumRange(0, 2) << endl;  // Output: 8

    // Query sum in range [1,2] → 2 + 5 = 7
    cout << obj->sumRange(1, 2) << endl;  // Output: 7

    delete obj; // Clean up allocated memory
    return 0;
}
