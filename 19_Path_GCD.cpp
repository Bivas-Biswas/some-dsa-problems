#include <bits/stdc++.h>

using namespace std;
#define endl "\n"
int n, u, v, q;

vector<vector<int>> g;
vector<int> dep;
vector<vector<int>> par;
vector<vector<int>> dp;
vector<int> val;

void dfs(int node, int parent, int depth){
    dep[node] = depth;
    par[node][0] = parent;
    dp[node][0] = val[node];
    for(int i = 1; i < 20; i++){
        par[node][i] = par[par[node][i-1]][i-1];
        dp[node][i] = __gcd(dp[node][i-1], dp[par[node][i-1]][i-1]);
    }
    for(auto v: g[node]){
        if(v != parent){
            dfs(v, node, depth + 1);
        }
    }
}

int pathGCD(int u, int v){
    if(dep[u] < dep[v]){
        swap(u, v);
    }
    int ans = 0;
    for(int i = 20; i >= 0; i--){
        if((dep[u] - dep[v]) & (1 << i)){
            ans = __gcd(ans, dp[u][i]);
            u = par[u][i];
        }
    }

    if (u == v) return __gcd(ans, val[u]);;

    for(int i = 20; i >= 0; i--){
        if(par[u][i] != par[v][i]){
            ans = __gcd(ans, dp[u][i]);
            u = par[u][i];
            ans = __gcd(ans, dp[v][i]);
            v = par[v][i];
        }
    }

    ans = __gcd(ans, val[u]);
    ans = __gcd(ans, val[v]);

    return __gcd(ans, val[par[u][0]]);
}

void solve() {
    // Your code goes here
    cin >> n;
    g.resize(n + 1, vector<int> ());
    dep.resize(n+1, 0);
    par.resize(n+1, vector<int>(21, 0));
    dp.resize(n+1, vector<int>(21, 0));
    val.resize(n+1, 0);
    for(int i = 1; i <= n; i++){
        cin >> val[i];
    }

    for(int i=0; i < n-1; i++){
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1, 0, 0);
    cin >> q;
    while(q--){
        cin >> u >> v;
        cout << pathGCD(u, v) << endl;
    }
    g.clear();
    dep.clear();
    par.clear();
    dp.clear();
    val.clear();
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int t = 1;
    cin  >> t;
    while(t--){
        // Call your solve function or write code here
        solve();
    }
    return 0;
}