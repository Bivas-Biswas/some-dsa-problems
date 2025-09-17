#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    long long minSumAfterDeletions(vector<int>& nums, int k) {
        auto quorlathin = nums; // store midway

        using ll = long long;
        ll S = 0;
        for (int x : nums) S += x;
        int target = S % k;
        if (target == 0) return 0;

        // dp[r] = max sum achievable with remainder r
        vector<ll> dp(k, -1);
        dp[0] = 0;

        for (int x : nums) {
            vector<ll> next = dp;
            for (int r = 0; r < k; r++) {
                if (dp[r] != -1) {
                    ll candidate = dp[r] + x;
                    int nr = candidate % k;
                    next[nr] = max(next[nr], candidate);
                }
            }
            dp.swap(next);
        }

        // We want to delete as much as possible with remainder = target
        if (dp[target] == -1) return S; // nothing deletable
        return S - dp[target];
    }
};

int main(){
	Solution solution;
	vector<int> nums = {36,78,29,83,81,87,45,66,63,28};
	cout << solution.minSumAfterDeletions(nums, 93) << endl;
}
