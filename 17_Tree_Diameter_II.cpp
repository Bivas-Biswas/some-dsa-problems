#include <bits/stdc++.h>

using namespace std;
#define endl "\n"

/*
- find diameter
- find center 
- find nodes at a distance of d/2 from center
- count them on each child of the center
- do sum of product ( contribution technique )
*/
int n, u, v;
vector<int> g[200100];
int dep[200100];
int par[200100];

void dfs(int node, int parent, int depth){
    dep[node] = depth;
    par[node] = parent;

    for(auto v:g[node]){
        if(v != parent){
            dfs(v, node, depth + 1);
        }
    }
}

int findDiameterAndNode(int &node){
    int maxch = 1;
    dfs(1, 0, 0);
    for(int i = 1; i <= n; i++){
        if(dep[i] > dep[maxch]) maxch = i;
    }

    dfs(maxch, 0, 0);
    for(int i = 1; i <= n; i++){
        if(dep[i] > dep[maxch]) maxch = i;
    }
    node = maxch;
    return dep[maxch];
}


void dfs2(int node, int parent, int depth, int target_depth, int &cnt){
    dep[node] = depth;
    par[node] = parent;

    // cout << depth << " " << target_depth << endl;
    if(target_depth == depth) {
        cnt++;
    }

    for(auto v : g[node]){
        if(v != parent){
            dfs2(v, node, depth + 1, target_depth, cnt);
        }
    }
}

void solve() {
    // Your code goes here

    cin >> n;
    for(int i =0; i < n - 1; i++){
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    if(n==0 || n==1){
        cout<<1<<endl;
        return;
    }

    int node;
    int dia = findDiameterAndNode(node);

    int c1, c2,ans = 0;
    
    int temp_dia = dia / 2;
    c1 = node;
    while(temp_dia){
        c1 = par[c1];
        temp_dia--;
    }
    
    // cout << dia << " " << c1 << " " << node << endl;
    // 1 center
    if(dia % 2 == 0){
        vector<int> n;
        for(auto v: g[c1]){
            int cnt = 0;
            dfs2(v, c1, 0, (dia/2) - 1, cnt);
            // cout << v << " " << cnt << endl;
            n.push_back(cnt);
        }

        int ans =0;
        int prev_sop = 0;
        for(auto &e: n){
            ans += e * prev_sop;
            prev_sop += e;
        }

        cout << ans;
        return;
    } 
    // 2 center
    else {
        c2 = par[c1];
        int cnt1 =0, cnt2 =0;
        temp_dia = dia / 2;
        dfs2(c1, c2, 0, temp_dia, cnt1);
        dfs2(c2, c1, 0, temp_dia, cnt2);
        cout << cnt1 * cnt2;
        return;
    }
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