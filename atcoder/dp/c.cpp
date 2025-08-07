// https://atcoder.jp/contests/dp/tasks/dp_c

#include<bits/stdc++.h>

using namespace std;

#define int long long

int n;
int happiness[100100][3];
int dp[100100][4];

int rec(int i, int prev){
	// pruning
	// basecase
	if(i == n) return 0;

	// cache check
	if(dp[i][prev] != -1) return dp[i][prev];

	// transition
	int ans = 0;
	for(int cur = 0; cur < 3; cur++){
		if(prev == cur) continue;

		ans = max(ans, happiness[i][cur] + rec(i+1, cur));
	}

	// save and return
	return dp[i][prev] = ans;
}

void solve(){
	cin >> n;
	for(int i=0; i<n; i++){
		cin >> happiness[i][0] >> happiness[i][1] >> happiness[i][2];
	}
	memset(dp, -1, sizeof(dp));
	cout << rec(0, 3) << endl;
}


signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	solve();
}