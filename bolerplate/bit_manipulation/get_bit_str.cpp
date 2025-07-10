#include<bits/stdc++.h>

using namespace std;

// convert the integer in bit string
// eg. 5 -> "101", 8 -> "1000" 
string get_bit_str(int x){
    string curr = "";
    while(x){
        if(x%2 == 1) curr += "1";
        else curr += "0";
        x /= 2;
    }
    if(curr == "") return "0";
    
    // answer will be back direction
    // remember how digital logic base 10 to base 2 conversion happen
    reverse(curr.begin(), curr.end());
    return curr;
}

void solve(){
    int n;
    cin >> n;
    cout << get_bit_str(n) << endl;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}