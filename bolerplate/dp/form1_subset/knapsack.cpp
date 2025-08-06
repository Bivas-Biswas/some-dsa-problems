#include<bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 1e9;
int n, w;
int val[101];
int weight[101];
int dp[101][100100];

int rec(int i, int weight_left){
	// pruning
	if(weight_left < 0) return -INF;

	// basecase
	if(i==n){
		if(weight_left >= 0) return 0;
		return -INF;
	}

	// cache check
	if(dp[i][weight_left] != -1) return dp[i][weight_left];

	// transition
	int ans = -INF;
	ans = max(ans, rec(i+1, weight_left));
	ans = max(ans, val[i] + rec(i+1, weight_left - weight[i]));

	// save and return
	return dp[i][weight_left] = ans;
}

void solve(){
	cin >> n >> w;
	for(int i=0; i<n; i++){
		int x, y;
		cin >> x >> y;
		weight[i] = x;
		val[i] = y;
	}

	memset(dp, -1, sizeof(dp));

	cout << rec(0, w) << endl;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	solve();
}