#include <bits/stdc++.h>

using namespace std;

#define endl "\n"
#define F first
#define S second

const int INF = 100;
using state = pair<int,int>;
int n, m;
vector<string> arr;

// Up, Right, Down, Left
int dx[] = {1, 0, -1, 0};
int dy[] = {0, -1, 0, 1};

bool inside(int x, int y){
    return x >= 0 && x < n && y >= 0 && y < m && arr[x][y] != '#';
}

vector<state> neighbour(state s){
    vector<state> ans;
    for(int i = 0; i < 4; i++){
        state temp = make_pair(s.F + dx[i], s.S + dy[i]);
        if(inside(temp.F, temp.S)){
            ans.push_back(temp);
        }
    }

    return ans;
}

vector<vector<int>> vis, dis;
vector<vector<state>> par;

void bfs(state st){
    vis = vector<vector<int>> (n, vector<int> (m, 0));
    dis = vector<vector<int>> (n, vector<int> (m, INF));
    par = vector<vector<state>> (n, vector<state> (m, make_pair(-1, -1)));

    queue<state> q;
    dis[st.F][st.S] = 0;
    q.push(st);

    while(!q.empty()){
        state cur = q.front(); q.pop();

        if(vis[cur.F][cur.S]) continue;

        vis[cur.F][cur.S] = 1;
        for(auto v:neighbour(cur)){
            // why not vis check ??
            // it is redudant, because here all edge positive and 
            // traversing level by level so, for same level the minimum distance 
            // already found. 
            if(dis[v.F][v.S] > dis[cur.F][cur.S] + 1){
                dis[v.F][v.S] = dis[cur.F][cur.S] + 1;
                par[v.F][v.S] = cur;
                q.push(v);
            }
        }
    }

    // print the dis matrix
    // for(int i = 0; i < n; i++){
    //     for(int j=0; j < m; j++){
    //         cout << dis[i][j] << "\t";
    //     }
    //     cout << endl;
    // }
}

// Up, Right, Down, Left
// int dx[] = {1, 0, -1, 0};
// int dy[] = {0, -1, 0, 1};

void printPath(state en){
    state cur = en;
    vector<state> path;
    while(cur != make_pair(-1, -1)){
        path.push_back(cur);
        cur = par[cur.F][cur.S];
    }

    reverse(path.begin(), path.end());

    // for(auto p: path){
    //     cout << p.F << " " << p.S << endl;
    // }

    state prev = path[0];
    for(int i=1; i < path.size(); i++){
        state cur = path[i];
        int f_diff = prev.F - cur.F;
        int s_diff = prev.S - cur.S;
        if(f_diff == 1 && s_diff == 0){
            cout << "U";
        } else if(f_diff == 0 && s_diff == -1){
            cout << "R";
        } else  if(f_diff == -1 && s_diff == 0){
            cout << "D";
        } else if(f_diff == 0 && s_diff == 1){
            cout << "L";
        }
        prev = cur;
    }
}

void solve() {
    // Your code goes here
    cin >> n >> m; 
    arr.resize(n);

    state st, en;
    
    for(int i = 0; i < n; i++){
        cin >> arr[i];
        for(int j =0; j < m; j++){
            if(arr[i][j] == 'A'){
                st = make_pair(i, j);
            }

            if(arr[i][j] == 'B'){
                en = make_pair(i, j);
            }
        }
    }

    bfs(st);

    if(vis[en.F][en.S]){
        cout << "YES" << endl;
        cout << dis[en.F][en.S] << endl;
        printPath(en);
        
    }else {
        cout << "NO" << endl;        
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

// You are given a map of a labyrinth, and your task is to find a path from start to end. You can walk left, right, up and down.
// Input
// The first input line has two integers n and m: the height and width of the map.
// Then there are n lines of m characters describing the labyrinth. Each character is . (floor), # (wall), A (start), or B (end). There is exactly one A and one B in the input.
// Output
// First print "YES", if there is a path, and "NO" otherwise.
// If there is a path, print the length of the shortest such path and its description as a string consisting of characters L (left), R (right), U (up), and D (down). You can print any valid solution.
