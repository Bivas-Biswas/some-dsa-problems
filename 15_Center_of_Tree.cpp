#include <bits/stdc++.h>

using namespace std;
#define endl "\n"

int n, u, v;
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

int findDiameter(int& node){
    int maxCh = 1;
    dfs(1, 0, 0);

    for(int i = 1; i <= n; i++){
        if(dep[i] > dep[maxCh]) maxCh = i;
    }

    dfs(maxCh, 0, 0);
    for(int i = 1; i <= n; i++){
        if(dep[i] > dep[maxCh]) maxCh = i;
    }
    node = maxCh;
    return dep[maxCh];
}

void solve() {
    // Your code goes here
    cin >> n;
    for(int i = 0; i < n - 1; i++){
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int leaf = -1;
    int dia = findDiameter(leaf);
    // cout << dia << " " << leaf << endl;

    int ans = -1;
    if(dia % 2 == 0){
        int curr = leaf;
        dia = dia / 2;
        while(dia){
            curr = par[curr];
            dia--;
        }
        ans = curr;
    }

    cout << ans;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int t = 1;
    // cin  >> t
    while(t--){
        // Call your solve function or write code here
        solve();
    }
    return 0;
}