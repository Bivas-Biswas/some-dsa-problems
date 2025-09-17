#include <bits/stdc++.h>

using namespace std;
#define endl "\n"

/*
 * Reading 
 * Thinking 
 * Formulate
 * Coding 
 * Debugging 
*/
int n, m;
vector<vector<int>> g;
vector<bool> vis;

void bfs(int node){
    queue<int> qu;
    qu.push(node);
    
    while(!qu.empty()){
        int temp = qu.front();
        qu.pop();

        if(vis[temp]) continue;

        vis[temp] = true;

        for(auto v: g[temp]){
            if(!vis[v]){
                qu.push(v);
            }
        }

    }
}

void solve() {
    // Your code goes here
    cin >> n >> m;
    g.resize(n+1);
    vis.resize(n+1);

    for(int i=0; i<m; i++){
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int cnt = 0;
    for(int i=1; i<=n;i++){
        if(!vis[i]){
            bfs(i);
            cnt++;
        }
    }

    cout << cnt - 1 << endl;
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