#include<bits/stdc++.h>

using namespace std;

void solve(){
    int n, k;
    cin >> n >> k;
    int arr[n];
    for(int i = 0; i<n; i++){
        cin >> arr[i];
    }

    int prefix[n];
    prefix[0] = arr[0];
    for(int i= 1;i <n; i++){
        prefix[i] = prefix[i-1] + arr[i];
    }


    int max_sum = 0;
    for(int st=0; st+k-1<n; st++){
        int en = st + k -1;
        int sum = prefix[en] - ((st-1) >=0 ? prefix[st-1] : 0);
        // cout << sum << endl;
        max_sum = max(max_sum, sum);
    }

    double result = (max_sum + k) / 2.0;

    cout << fixed << setprecision(12) << result << endl;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int t = 1;
    while(t--) solve();
}