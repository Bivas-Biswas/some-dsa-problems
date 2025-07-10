#include <bits/stdc++.h>

using namespace std;
#define endl "\n";

int n;
string s;


void rec(int level, int open_c){
    if(level == n){
        if(open_c == 0)
            cout << s << endl;
            return;
        }

    if(!open_c){
        s.append("(");
        rec(level + 1, open_c + 1);
        s.pop_back();
    } else {
        int rem_l = n - level + 1;
        if(rem_l > open_c){
            s.append("(");
            rec(level + 1, open_c + 1);
            s.pop_back();
        }

        s.append(")");
        rec(level + 1, open_c - 1);
        s.pop_back();
    }
}

void solve() {
    // Your code goes here
    cin >> n;
    rec(0, 0);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    // Call your solve function or write code here
    solve();
    return 0;
}

// Sample Input 1
// input:
// 2
// output: 
// ()

// Sample Input 2
// input:
// 4
// output:
// (())
// ()()