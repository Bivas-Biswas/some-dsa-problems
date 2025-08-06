/*
	N = 5
	arr = [1, 3, 5, 8, 10]
	number of ways to make a sum x = 9
	ans is 2. {1, 3, 4} and {1, 8}
	N, x <= 1000
	arr[i] <= 1e9
*/

#include<bits/stdc++.h>

using namespace std;

int n, x;
int arr[1001];

int rec(int i, int sum_left){
	// pruning
	if(sum_left < 0) return 0;
	// basecase
	if(i == n){
		if(sum_left == 0) return 1;
		return 0;
	}
	// cache check
	// transition
	int ans = 0;
	ans += rec(i + 1, sum_left);
	ans += rec(i + 1, sum_left - arr[i]);

	// save and return
	return ans;
}

void solve(){
	cin >> n;
	for(int i=0; i<n; i++) cin >> arr[i];
	cin >> x;

	cout << rec(0, x) << endl;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	solve();
}


