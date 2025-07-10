#include <bits/stdc++.h>

using namespace std;
#define endl "\n"
#define int long long

// https://maang.in/problems/Edge-Reverse-900
/*
 * Reading 
 * Thinking 
 * Formulate
 * Coding 
 * Debugging
*/
#define F first
#define S second


int n, m;
int dis[100100];
vector<pair<int, int>> g[100100];

void bfs01(){
    for (int i = 0; i <= n; i++) dis[i] = 1e9;

    deque<int> dq; // deque
    dq.push_back(1);
    dis[1] = 0;

    while(!dq.empty()){
        int cur = dq.front();
        dq.pop_front();

        for(auto v:g[cur]){
            if(dis[v.F] > dis[cur] + v.S){
                dis[v.F] = dis[cur] + v.S;

                if(v.S == 0){ // 0 in front
                    dq.push_front(v.F);
                }else{ // 1 in back
                    dq.push_back(v.F);
                }
            }
        }
    }
     
}

void solve() {
    // Your code goes here
    cin >> n >> m;
    
    for(int i = 0; i <= n; i++) g[i].clear();

    while(m--){
        int u, v;
        cin >> u >> v;
        g[u].push_back(make_pair(v, 0));
        g[v].push_back(make_pair(u, 1));
    }

    bfs01();
    if(dis[n] == 1e9){
    cout << -1 << endl;
    }else
    cout << dis[n] << endl;
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