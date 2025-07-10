#include <bits/stdc++.h>

using namespace std;
#define endl "\n"
#define int long long

/*
 * Reading 
 * Thinking 
 * Formulate
 * Coding 
 * Debugging 
*/
#define F first
#define S second
using state = pair<int, int>;

int n, m;
vector<state> g[100100]; // node, weight
bool vis[100100];
int dis[100100];

void dijkstra(int st){
    for(int i=0; i<= n; i++){
        vis[i]= 0;
        dis[i] = 1e19; // long long used maxium
    }

    priority_queue<state> pq; // dis, node
    pq.push(make_pair(-0, st));
    dis[st] = 0;

    while(!pq.empty()){
        state temp = pq.top(); pq.pop();

        if(vis[temp.S]) continue;
        vis[temp.S] = 1;

        for(auto v:g[temp.S]){
            if(dis[v.F] > dis[temp.S] + v.S){
                dis[v.F] = dis[temp.S] + v.S;
                pq.push(make_pair(-dis[v.F], v.F));
            }
        }
    }
}

void solve() {
    // Your code goes here
    cin >> n >> m;
    
    for(int i = 0; i <= n; i++) g[i].clear(); // clear everytime

    while(m--){
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back(make_pair(v, w));
    }

    dijkstra(1);
    for(int i=1; i<=n; i++){
        cout << dis[i] << " ";
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