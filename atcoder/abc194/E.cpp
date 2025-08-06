#include<bits/stdc++.h>

using namespace std;

struct mexfinder{
    map<int, int> freq;
    set<int> np; // store the not present elements, will be in sorted order

    mexfinder(int n){
        for(int i=0; i<=n; i++){ // in the window 0...n-1 present mex will n
            np.insert(i);
        }
    }

    void insert(int x){
        freq[x]++;
        if(freq[x] == 1) np.erase(x);
    }

    void erase(int x){
        freq[x]--;
        if(freq[x] == 0) np.insert(x);
    }

    int getmex(){
        return *np.begin();
    }
};

void solve(){
    int n, m;
    cin >> n >> m;

    int arr[n];
    for(int i=0; i<n; i++){
        cin >> arr[i];
    }

    int min_mex = 1e9;
    mexfinder ds(n);
    for(int en=0; en< n; en++){
        ds.insert(arr[en]);

        // the element which need to removed
        if(en - m >= 0) ds.erase(arr[en - m]);

        // start of the mth window
        int st = en - m + 1;
        if(st >= 0){
            int curr_mex = ds.getmex();
            // cout << curr_mex << endl;
            min_mex = min(min_mex, curr_mex);
        }
    }
    cout << min_mex << endl;

}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int t=1;
    while(t--) solve();
}