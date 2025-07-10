#include <bits/stdc++.h>

using namespace std;

string s;
int dp[1010][1010];

int cnt = 0;
int rec(int l, int r)
{
    if (l >= r)
        return 1;
    if (dp[l][r] != -1)
        return dp[l][r];
        
    cnt++;
    int ans = 0;
    if (s[l] == s[r] && rec(l + 1, r - 1))
    {
        ans = 1;
    }
    return dp[l][r] = ans;
}

void rec2(int i){
    if(i == 0) return;

    for(int j=0; j < i; j++){
        rec(j+1, i);
        rec2(j);
    }

}

void solve()
{
    cin >> s;
    int n = s.size();
    memset(dp, -1, sizeof(dp));
    // rec(0, n - 1);

    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < n; j++)
    //         rec(i, j);
    // }

    rec2(n);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (dp[i][j] == -1)
            {
                cout << "." << " ";
            }
            else
            {
                cout << dp[i][j] << " ";
            }
        }
        cout << endl;
    }

    cout << cnt;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t = 1;
    while (t--)
    {
        solve();
    }
    return 0;
}