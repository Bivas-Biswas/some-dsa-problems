#include <bits/stdc++.h>

using namespace std;
#define endl "\n"

vector<int> g[200100];
int subtreeSz[200100];
int par[200100];

void dfs(int node, int parent){
    par[node] = parent;
    subtreeSz[node] = 1;

    for(auto v: g[node]){
        if(v != parent){
            dfs(v, node);
            subtreeSz[node] += subtreeSz[v];
        }
    }
}

void solve() {
    // Your code goes here
    int n, u, v;
    cin >> n;
    for(int i = 0; i < n - 1; i++){
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1, 0);
    int ans = 0;
    for(int i = 1; i <= n; i++){
        ans += subtreeSz[i] * (n - subtreeSz[i]);
    }
    cout << ans;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int t = 1;
    // cin  >> t;
    while(t--){
        // Call your solve function or write code here
        solve();
    }
    return 0;
}