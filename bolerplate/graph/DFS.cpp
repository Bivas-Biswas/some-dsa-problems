#include <bits/stdc++.h>

using namespace std;
#define endl "\n"

int n,m,q;
vector<vector<int>> g;
vector<bool> vis;
vector<int> comp;
vector<int> comp_sz;

void dfs(int node, int comp_no){
    vis[node] = true;
    comp[node] = comp_no;
    comp_sz[comp_no]++;

    for(auto v: g[node]){
        if(!vis[v]){
            dfs(v, comp_no);
        }
    }
}

void solve() {
    // Your code goes here
    cin >> n >> m >> q;
    g.resize(n+1);
    vis.resize(n+1, false);
    comp.resize(n+1, -1);
    comp_sz.resize(n+1, 0);

    for(int i=0; i < m; i++){
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int cnt = 1;
    for(int i=1; i <= n; i++){
        if(!vis[i]){
            dfs(i, cnt);
            cnt++;
        }
    }

    while(q--){
        int x, y, op;
        cin >> op;
        if(op == 1){
            cin >> x;
            cout << comp_sz[comp[x]] << endl;
        } else {
            cin >> x >> y;
            if(comp[x] == comp[y]){
                cout << "YES" << endl;
            }else{
                cout << "NO" << endl;
            }
        }
    }

    // for(auto v:comp){
    //     cout << v <<  " ";
    // }
    // cout << endl;
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