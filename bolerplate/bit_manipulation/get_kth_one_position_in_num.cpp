#include<bits/stdc++.h>

using namespace std;

using ll = long long;

string get_bit_str(ll x){
    string curr = "";
    while(x){
        if(x%2 == 1) curr += "1";
        else curr += "0";
        x /= 2;
    }
    if(curr == "") return "0";
    reverse(curr.begin(), curr.end());
    return curr;
}

// Give the index of the kth one in the number x from left to right
// x = 5("101"), k = 1 --> 0 
// x = 5("101"), k = 2 --> 2 
// x = 12("1100"), k = 2 --> 1 
ll get_kth_one_position_in_num(ll x, ll k){
    ll cnt = 0;
    string num = get_bit_str(x);
    for(ll i=0; i < num.size(); i++){
        if(num[i] == '1') cnt++;
        if(cnt == k) return i;
    }
}

void solve(){
    ll n, k;
    cin >> n >> k;
    cout << get_kth_one_position_in_num(n, k) << endl;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int t = 1;
    cin >> t;
    while(t--) solve();
}

