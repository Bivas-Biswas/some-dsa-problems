#include <bits/stdc++.h>

using namespace std;
#define endl "\n";

int n;
int ans;
vector<int> board;

bool check(int row, int col){
    // diagonal
    int pcol;
    for(int prow = 0; prow < row; prow++){
        pcol = board[prow];

        if(pcol == col || abs(prow - row) == abs(pcol - col)) return false;

    }
    
    if ((row - 1) >= 0) {
        pcol = board[row - 1];
        if (pcol == col - 2 || pcol == col + 2) return false;
    }
    if ((row - 2) >= 0) {
        pcol = board[row - 2];
        if (pcol == col - 1 || pcol == col + 1) return false;
    }
    return true;
}

void rec(int level){
    if(level == n){
        ans++;
        return;
    }

    for(int col = 0; col < n; col++){
        if(check(level, col)){
            board.push_back(col);
            rec(level+1);
            board.pop_back();
        }
    }
}

void solve() {
    cin >> n;
    
    rec(0);

    cout << ans;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    solve();
    return 0;
}

// Sample Input 1
// input:
// 3
// output: 
// 0

// Sample Input 2
// input:
// 10
// output:
// 4