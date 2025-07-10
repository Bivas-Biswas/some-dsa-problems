#include <bits/stdc++.h>

using namespace std;
#define endl "\n"
#define int long long

vector<int> g[200100];
int dep[200100];
int par[200100];

void dfs(int node, int parent, int depth){
    par[node] = parent;
    dep[node] = depth;

    for(auto v: g[node]){
        if(v != parent){
            dfs(v, node, depth + 1);
        }
    }
}

void solve() {
    // Your code goes here
    int n;
    int u, v;
    cin >> n;
    for(int i = 0; i < n - 1; i++){
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    
    dfs(1, 0, 0);
    int maxch = 0;
    for(int i = 1; i <= n; i++){
        if(dep[i] > dep[maxch]) maxch = i;
    }

    dfs(maxch, 0, 0);
    for(int i = 1; i <= n; i++){
        if(dep[i] > dep[maxch]) maxch = i;
    }

    cout << dep[maxch];
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