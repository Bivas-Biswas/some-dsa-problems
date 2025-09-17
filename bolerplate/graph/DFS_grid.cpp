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

int n,m;
vector<string> grid;
vector<vector<bool>> vis;

bool valid(int x, int y){
    return x >=0 && x < n && y >= 0 && y < m && grid[x][y] != '#';
}

int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

vector<pair<int, int>> neighbour(int x, int y){
    vector<pair<int, int>> ans;
    for(int k=0; k<4; k++){
        int nx, ny;
        nx = x + dx[k];
        ny = y + dy[k];
        if(valid(nx, ny))
            ans.push_back(make_pair(nx, ny));
    }

    return ans;
}

void dfs(int x, int y){
    
    // if() return;

    vis[x][y] = true;
    for(auto v: neighbour(x, y)){
        if(!vis[v.first][v.second]){
            dfs(v.first, v.second);
        }
    }
}

void solve() {
    // Your code goes here
    cin >> n >> m;
    vis.resize(n, vector<bool> (m, false));
    for(int i = 0; i < m; i++){
        string s;
        cin >> s;
        grid.push_back(s);
    }

    int cnt = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(!vis[i][j] && grid[i][j] != '#'){
                dfs(i, j);
                cnt++;
            }
        }
    }

    cout << cnt << endl;
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