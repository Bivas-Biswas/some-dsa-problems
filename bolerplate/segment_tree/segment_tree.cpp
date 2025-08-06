class SegmentTree{
    public:
    vector<int> t_;
    SegmentTree(int n){
        t_.resize(4 * n);
    }

    SegmentTree(){
    }

    void init(int n){
        t_.resize(4 * n);
    }

    void build(int idx, int l, int r, vector<int>& arr){
        if(l==r){
            t_[idx] = arr[l];
            return;
        }

        int mid = (l+r) >> 1;
        build(idx *2, l, mid, arr);
        build(idx * 2 + 1, mid+1, r, arr);
        t_[idx] = t_[idx * 2] + t_[idx*2 + 1];
    }

    void update(int idx, int l, int r, int val_idx, int val){
        // if(l > r) return;
        if(l==r){
            // cout << val_idx << " " << idx << " " << l << " " << r << endl;
            t_[idx] = val;
            return;
        }

        int mid = (l+r)>>1;
        if(val_idx >= l && val_idx <= mid){
            update(idx * 2, l, mid, val_idx, val);
        }else{
            update(idx * 2 + 1, mid + 1, r, val_idx, val);
        }
        t_[idx] = t_[idx * 2] + t_[idx*2 + 1];
    }

    int sum_range(int idx, int l, int r, int lq, int rq){
        if(l > rq || lq > r) return 0;

        if(l >= lq && r <= rq){
            return t_[idx];
        }
        
        int mid = (l+r) >> 1;
        return sum_range(idx * 2, l, mid, lq, rq) + sum_range(idx * 2 + 1, mid + 1, r, lq, rq);
    }
};

class NumArray {
public:
    SegmentTree segt;
    int n;
    NumArray(vector<int>& nums) {
        n = nums.size();
        segt.init(n);
        segt.build(1, 0, n-1, nums);
    }
    
    void update(int index, int val) {
        segt.update(1, 0, n -1, index, val);
    }
    
    int sumRange(int left, int right) {
        return segt.sum_range(1, 0, n - 1, left, right);
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(index,val);
 * int param_2 = obj->sumRange(left,right);
 */