// https://atcoder.jp/contests/dp/tasks/dp_b

#include<bits/stdc++.h>
using namespace std;

#define int long long

int n, k;
int dp[100100];
int height[100100];
const int INF = 1e19;


int rec(int i){
	if(i < 0) return INF;
	
	if(i==0) return 0;

	if(dp[i] != -1) return dp[i];

	int ans = INF;
	for(int prev = i-1; prev >= max(i- k, 0LL); prev--){
		int cost = abs(height[i] - height[prev]);
		ans = min(ans, cost + rec(prev));
	}

	return dp[i] = ans;
}


void solve(){
	cin >> n >> k;
	for(int i=0; i<n; i++) cin >> height[i];
	memset(dp, -1, sizeof(dp));

	cout << rec(n-1) << endl;
}


signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	solve();
}