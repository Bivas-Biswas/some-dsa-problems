#include <bits/stdc++.h>

using namespace std;
#define endl "\n"
#define int long long

const int MOD = 1e9+7;
int n;
// int dp[100100][16];

// int rec(int i, int last3){

//     // base case
//     if(i == n) return 1;

//     if(dp[i][last3] != -1) return dp[i][last3];

//     int ans;
//     // 010 & 10 both are same so only when livel >= 3
//     // then only go in this path
//     if(i >= 3 && last3 == 2){
//         ans = rec(i+1, last3 + 1) % MOD;
//     } else {
//         ans = rec(i + 1, (last3 << 1 | 0) & 7) % MOD;
//         ans = (ans + rec(i + 1, (last3 << 1 | 1) & 7)) % MOD;
//     }

//     return dp[i][last3] = ans;
// }


#include <bits/stdc++.h>
#define int long long
using namespace std;

int n = 0;
int dp[1000001][7];
int mod = 1e9 + 7;

int rec(int level, int match) {
    if (match == 4) return 0;
    if (level == n) return 1;

    if (dp[level][match] != -1) return dp[level][match];

    int ans = 0;

    if (match == 0) {
        ans = (rec(level + 1, 1) + rec(level + 1, 0)) % mod;
    } else if (match == 1) {
        ans = (rec(level + 1, 2) + rec(level + 1, 1)) % mod;
    } else if (match == 2) {
        ans = (rec(level + 1, 0) + rec(level + 1, 3)) % mod;
    } else if (match == 3) {
        ans = (rec(level + 1, 4) + rec(level + 1, 2)) % mod;
    }
    return dp[level][match] = ans;
}

// using Finite Automata
int dp[1000001][7];

int rec(int i, int state){
    if(state == 4) return 0;

    if(i == n) return 1;

    if(dp[i][state] != -1) return dp[i][state];

    int ans = 0;
    if(state == 0){
        ans = rec(i + 1, 0);
        ans = (ans + rec(i + 1, 1)) % MOD;
    } else if(state == 1){
        ans = rec(i + 1, 1);
        ans = (ans + rec(i + 1, 2)) % MOD;
    } else if(state == 2){
        ans = rec(i + 1, 0);
        ans = (ans + rec(i+1, 3)) % MOD;
    } else if(state == 3){
        ans = rec(i + 1, 1);
        ans = (ans + rec(i+1, 4)) % MOD;
    }

    return dp[i][state] = ans;
}

// void solve() {
//     // Your code goes here
//     cin >> n;
//     cout << rec(0, 0) << endl;
// }

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);

    int t = 1;
    cin >> t;
    vector<int> ns(t);
    for (int i = 0; i < t; i++) {
        cin >> ns[i];
        n = max(n, ns[i]);
    }

    memset(dp, -1, sizeof(dp));
    rec(0, 0);

    for(int i=0; i < n; i++){
        for(int j = 0; j < 5; j++){
            cout << dp[i][j]<< "\t";
        }
        cout << endl;
    }
    

    // for (int i = 0; i < t; i++) {
    //     cout << n - ns[i] << " ";
    //     cout << dp[n - ns[i]][0] << "\n";
    // }

    return 0;
}