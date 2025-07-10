#include <bits/stdc++.h>

using namespace std;
#define endl "\n"

int n, u, v, q, x, y, z;

vector<vector<int>> g;
vector<vector<int>> par;
vector<int> dep;

void dfs(int node, int parent, int depth){
    dep[node] = depth;
    par[node][0] = parent;

    // building the binary lifting by 2^i
    for(int i=1; i <= 20; i++){
        par[node][i] = par[par[node][i-1]][i-1];
    }

    for(auto v:g[node]){
        if(v != parent){
            dfs(v, node, depth + 1);
        }
    }
}

int lca(int u, int v){
    // depth of u always big 
    // helpful for clean code
    if(dep[u] < dep[v]){
        swap(u, v);
    }

    // step:1 move to the same level
    for(int i=20; i >= 0; i--){
        if((dep[u] - dep[v]) & (1 << i)){
            u = par[u][i];
        }
    }

    // if v is present in the u's subtree
    if(u == v) return u;

    // step: lift u and v simulateonuly
    for(int i=20; i >= 0; i--){
        if(par[v][i] != par[u][i]){
            u = par[u][i];
            v = par[v][i];
        }
    }

    return par[u][0];
}


/**
 * lca(u, v) = l
 * lca(u, z) = a;
 * lca(v, z) = b;
 * 
 * Case 1:
 * if a == l: then z is the same subtree as v. return b
 * if b == l: then z is the same subtree as u. return a
 * 
 * case 2;
 * if a !=  l and b != l then z outside of both u and v subtree. return l
 */
int lca_twist(int u, int v, int z){
    int l = lca(u, v);
    int a = lca(u, z);
    int b = lca(v, z);

    if(a == l){
        return b;
    } else if(b == l){
        return a;
    } return l;
}


void solve() {
    // Your code goes here
    cin >> n;
    g.assign(n + 1, vector<int>());
    dep.assign(n + 1, 0);
    par.assign(n + 1, vector<int>(21, 0));

    for(int i=0; i < n-1; i++){
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    
    dfs(1, 0, 0);

    cin >> q;
    for(int i=0; i < q; i++){
        cin >> x >> y >> z;
        cout << lca_twist(x, y, z) << endl;
    }

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