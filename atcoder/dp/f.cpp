// https://atcoder.jp/contests/dp/tasks/dp_f

#include<bits/stdc++.h>
using namespace std;

string s, t;
int n, m;
int dp[3001][3001];

int rec(int i, int j){
	if(i >= n || j >=m)	return 0;


	if(dp[i][j] != -1) return dp[i][j];

	int ans = 0;
	if(s[i] == t[j]){
		ans = max(ans, 1 + rec(i+1, j+1));
	} else {
		ans = max(ans, rec(i+1, j));
		ans = max(ans, rec(i, j+1));
	}

	return dp[i][j] = ans;
}

string ans;
void generate(int i, int j){

	if(i >= n || j >= m) return;

	if(s[i] == t[j]){
		ans.push_back(s[i]);
		generate(i+1, j+1);
		return;
	} else {
		int escape_i = rec(i+1, j);
		int escape_j = rec(i, j+1);
		if(escape_i > escape_j){
			generate(i+1, j);
		}
		else {
			generate(i, j+1);
		}
	}
}

void solve(){
	cin >> s >> t;
	n = s.size();
	m = t.size();
	memset(dp, -1, sizeof(dp));

	generate(0, 0);
	cout << ans << endl;
}


signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	solve();
}