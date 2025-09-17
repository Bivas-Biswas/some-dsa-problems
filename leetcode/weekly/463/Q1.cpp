#include <bits/stdc++.h>
using namespace std;

long long maxProfitAfterModification(vector<int>& prices, vector<int>& strategy, int k) {
    int n = prices.size();
    long long original_profit = 0;
    for (int i = 0; i < n; i++) original_profit += 1LL * strategy[i] * prices[i];
    
    long long max_gain = LLONG_MIN;
    long long sum_strategy_window = 0;
    long long sum_prices_last_half = 0;
    int half_k = k / 2;

    for (int i = 0; i < n; i++) {
        sum_strategy_window += 1LL * strategy[i] * prices[i];
        if (i >= half_k) sum_prices_last_half += prices[i];
        
        if (i >= k) {
            sum_strategy_window -= 1LL * strategy[i - k] * prices[i - k];
            sum_prices_last_half -= prices[i - half_k];
        }

        if (i >= k - 1) {
            long long gain = sum_prices_last_half - sum_strategy_window;
            max_gain = max(max_gain, gain);
        }
    }
    
    return original_profit + max(0LL, max_gain);
}

int main(){
	vector<int> prices = {5, 4, 3};
	vector<int> strategy = {1, 1, 0};
	cout << maxProfitAfterModification(prices, strategy, 2) << endl;
}
