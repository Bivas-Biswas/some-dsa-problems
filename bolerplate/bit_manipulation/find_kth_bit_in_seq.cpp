#include<bits/stdc++.h>

using namespace std;

void solve(){
    int k;
    cin >> k;
	k++; // make it to 1 index
	
	int len = 1;
	while((1<<(len - 1)) * len < k){
		k -= (1 << (len - 1)) * len;
		len++;	
	}

	int num = (k + len - 1)/len;    //ceil(k/len)
	int val = (1<<(len - 1)) + (num - 1);
	int bitval = (k - 1) % len;
	cout << num << " " << val << " " << bitval << endl;

	int ans = (val >> (len - bitval - 1)) & 1;
	cout << ans << endl;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    solve();
}
