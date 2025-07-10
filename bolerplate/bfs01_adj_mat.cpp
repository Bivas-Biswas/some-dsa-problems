#include <bits/stdc++.h>

using namespace std;
#define endl "\n"

// https://maang.in/problems/One-Piece-902
/*
 * Reading 
 * Thinking 
 * Formulate
 * Coding 
 * Debugging 
*/

const int INF = 1e9;

struct state{
    int x;
    int y;
    int weight;
};

int n, m, k = 0;
vector<vector<bool>> vis;
vector<vector<int>> dis;
vector<vector<int>> grid;

int dx[] ={0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

bool check(int x, int y){
    return x >= 0 && x < n && y >= 0 && y < m;
}

vector<state> neighbour(int x, int y){
    vector<state> temp;
    for(int i=0; i<4; i++){
        int nx = dx[i] + x;
        int ny = dy[i] + y;
        int weight = 0;
        if(check(nx, ny)){
            if(grid[x][y] == 1 && dx[i] == 0  && dy[i] == 1){
                weight = 0;
            } else if(grid[x][y] == 2 && dx[i] == 0  && dy[i] == -1){
                weight = 0;
            } else if(grid[x][y] == 3 && dx[i] == 1  && dy[i] == 0){
                weight = 0;
            } else if(grid[x][y] == 4 && dx[i] == -1  && dy[i] == 0){
                weight = 0; 
            } else {
                weight = 1;
            }
            temp.push_back({nx, ny, weight});
        }
    }

    return temp;
}

void bfs01(int x, int y){
    deque<state> dq;
    dq.push_back({x, y, 0});
    dis[x][y] = 0;

    while(!dq.empty()){
        state temp = dq.front();
        dq.pop_front();

        for(auto v: neighbour(temp.x, temp.y)){
            if(dis[v.x][v.y] > dis[temp.x][temp.y] + v.weight){
                dis[v.x][v.y] = dis[temp.x][temp.y] + v.weight;
                if(v.weight == 0){
                    dq.push_front(v);
                }else{
                    dq.push_back(v);
                }
            }
        }
    }
}

void solve() {
    // Your code goes here
    cin >> n >> m;

    grid.resize(n, vector<int> (m, 0));
    dis.resize(n, vector<int> (m, INF));

    for(int i=0; i<n; i++){
        for(int j=0; j < m; j++){
            cin >> grid[i][j];
        }
    }

    bfs01(0, 0);
    cout << dis[n-1][m-1] << endl;
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