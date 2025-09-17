#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct PairHash {
    size_t operator()(const pair<int,int> &p) const noexcept {
        return ((size_t)p.first << 32) ^ (unsigned)p.second;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    cin >> N;
    vector<ll> X(N), Y(N);
    for(int i = 0; i < N; i++) cin >> X[i] >> Y[i];
    
    unordered_map<pair<int,int>, vector<pair<int,int>>, PairHash> mp;
    mp.reserve(N*N);
    
    for(int i = 0; i < N; i++){
        for(int j = i+1; j < N; j++){
            ll dx = X[j] - X[i];
            ll dy = Y[j] - Y[i];
            ll g = gcd(dx, dy);
            dx /= g; dy /= g;
            // normalize direction
            if (dx < 0 || (dx == 0 && dy < 0)){
                dx = -dx; dy = -dy;
            }
            mp[{(int)dy, (int)dx}].push_back({i, j});
        }
    }
    
    ll ans = 0;
    vector<int> deg(N);
    for (auto &kv : mp){
        auto &pairs = kv.second;
        int m = pairs.size();
        if (m < 2) continue;
        fill(deg.begin(), deg.end(), 0);
        for (auto &pr : pairs){
            deg[pr.first]++;
            deg[pr.second]++;
        }
        ll total = 1LL * m * (m - 1) / 2;
        ll bad = 0;
        for (int v = 0; v < N; v++){
            if (deg[v] >= 2) bad += 1LL * deg[v] * (deg[v] - 1) / 2;
        }
        ans += total - bad;
    }
    
    cout << ans / 2 << "\n";
}
