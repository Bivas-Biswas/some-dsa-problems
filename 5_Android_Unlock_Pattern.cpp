#include <bits/stdc++.h>

using namespace std;
#define endl "\n";

int skip[10][10];
bool visited[10];

int dfs(int level, int remLen){
    if(remLen == 0) return 1;

    visited[level] = true;

    int ans = 0;
    for(int i = 1; i < 10; i++){
        if(!visited[i] && (!skip[level][i] || !visited[skip[level][i]])){
            ans += dfs(i, remLen - 1);
        }
    }

    visited[level] = false;
    return ans;
}

void solve() {
    int n, ans = 0;

    memset(skip, 0, sizeof(skip));
    memset(visited, false, sizeof(visited));

    cin >> n;
    // Your code goes here
    skip[1][7] = skip[7][1] = 4;
    skip[1][3] = skip[3][1] = 2;
    skip[3][9] = skip[9][3] = 6;
    skip[7][9] = skip[9][7] = 8;

    skip[1][9] = skip[9][1] = 
    skip[3][7] = skip[7][3] = 
    skip[2][8] = skip[8][2] = 
    skip[4][6] = skip[6][4] = 5;

    ans += dfs(1, n - 1) * 4;

    ans += dfs(2, n - 1) * 4;

    ans += dfs(5, n - 1);

    cout << ans;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    // Call your solve function or write code here
    solve();
    return 0;
}