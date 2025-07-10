#include <bits/stdc++.h>

using namespace std;
#define endl "\n";
#define pii pair<int, int>

char s[48];
int n = 7;
bool grid[7][7];

int dir[5] = {0, -1, 0, 1, 0};

bool isvalid(int x, int y)
{
    return (x >= 0 && y >= 0 && x < n && y < n && grid[x][y] == false);
}

int dfs(int row, int col, int remLen){
    
    if (!isvalid(row, col)) return 0;

    if(row == 6 && col == 0)
        return remLen == 48 ? 1 : 0;

    // pruning logic: coridor concept
    // 1. Vertical corridor: up and down close but left and right open
    if(isvalid(row - 1, col) && isvalid(row+1, col) && !isvalid(row, col + 1) && !isvalid(row, col - 1)){
        return 0;
    }
    // 2. Horizontal corridor: left and right close but up and down open
    if (isvalid(row, col + 1) && isvalid(row, col - 1) && !isvalid(row - 1, col) && !isvalid(row+1, col))
        return 0;

    grid[row][col] = true;
    int ans = 0;
    
    if(s[remLen] == 'U'){
        ans += dfs(row-1, col, remLen + 1);
    }
    else if(s[remLen] == 'D'){
        ans += dfs(row+1, col, remLen + 1);
    }
    else if(s[remLen] == 'L'){
        ans += dfs(row, col - 1, remLen + 1);
    }
    else if(s[remLen] == 'R'){
        ans += dfs(row, col + 1, remLen + 1);
    } else {
        for(int i = 0; i < 4; i++){
            int nx = dir[i] + row;
            int ny = dir[i + 1] + col;

            ans += dfs(nx, ny, remLen + 1);
        }
    }

    grid[row][col] = false;

    return ans;
}


void solve() {
    // Your code goes here
    memset(grid, false, sizeof(grid));

    int ans = 0;
    for(int i = 0; i < 48; i++){
        cin >> s[i];
    }

    ans = dfs(0, 0, 0);

    cout << ans;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    // Call your solve function or write code here
    solve();
    return 0;
}

// input: ??????R??????U??????????????????????????LD????D?
// output: 201