#include<bits/stdc++.h>

using namespace std;

void solve(){
	int n;
	string s;
	cin >> n;
	cin >> s;
	if(n < 3) {
		cout << "No" << endl;
		return;
	}

	if(s[n-3] == 't' && s[n-2] == 'e' && s[n-1] == 'a'){
		cout << "Yes" << endl;
	}else{
		cout << "No" << endl;
	}

}


signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int t=1;
    while(t--) solve();
}