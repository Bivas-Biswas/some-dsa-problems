#include <bits/stdc++.h>
using namespace std;
using int64 = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if(!(cin>>T)) return 0;
    while(T--){
        int n; cin >> n;
        vector<int64> a(n);
        for(int i=0;i<n;i++) cin >> a[i];
        sort(a.begin(), a.end(), greater<int64>()); // descending
        int64 ans = 0;
        for(int i = 0; i < n; i += 2) ans += a[i];
        cout << ans << '\n';
    }
    return 0;
}
