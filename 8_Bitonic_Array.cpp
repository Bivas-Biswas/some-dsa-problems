#include <bits/stdc++.h>

using namespace std;
#define endl "\n";

int n, q, x;
int *arr;

int bs(int lo, int hi, int init_ans, int (*check)(int)){
    int ans = init_ans;
    while (lo <= hi)
    {
        int mid = (lo + hi) / 2;
        if(check(mid) == 0){
            lo = mid + 1;
        } else {
            ans = mid;
            hi = mid - 1;
        }
    }
    return ans;
}

int bs2(int lo, int hi, int init_ans, int (*check)(int)){
    int ans = init_ans;
    while (lo <= hi)
    {
        int mid = (lo + hi) / 2;
        if(check(mid) == 0){
            lo = mid + 1;
        } else {
            if(arr[mid] == x){
                ans = mid;
            }
            hi = mid - 1;
        }
    }
    return ans;
}

int checkPeak(int mid){
    if(mid == n - 1) return 1;
    return arr[mid] > arr[mid + 1];
}

int checkLeft(int mid){
    return arr[mid] >= x;
}

int checkRight(int mid){
    return arr[mid] <= x;
}

void solve() {
    // Your code goes here
    cin >> n >> q;
    arr = new int[n];
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }

    int peak = bs(0, n - 1, -1, checkPeak);

    // cout << peak << endl;

    for(int i = 0; i < q; i++){
        cin >> x;

        // check if peak is the answer
        if(arr[peak] == x){
            cout << peak + 1 << endl;
            continue;
        }

        // check in left search space
        int left_x = bs2(0, peak - 1, -1, checkLeft);
        
        // check in right search space
        int right_x = bs2(peak + 1, n - 1, -1, checkRight);

        if(left_x != -1 && right_x != -1){
            cout << left_x + 1 << " " << right_x + 1 << endl;
        } else if(left_x != -1){
            cout << left_x + 1 << endl;
        } else if(right_x != -1){
            cout << right_x + 1 << endl;
        }

    }

    delete[] arr;
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

// input:
// 1
// 6 4
// 1 2 5 3 2 1
// 1
// 2
// 5
// 3
// output:
// 1 6
// 2 5
// 3
// 4