#include <bits/stdc++.h>

using namespace std;
#define endl "\n"
#define ll long long int

ll totalLen = 0;
ll ans = 0;

bool is_prime(ll n){
    for(ll i = 2; i * i <= n; i++){
        if(n % i == 0) return false;
    }
    return true;
}

void rec(ll curr, ll totalLen, ll currLen, ll a, ll b){
    if(currLen > totalLen) return;

    if(currLen == (totalLen + 1) / 2){
        vector<int> d;
        ll temp = curr;
        
        while(temp){
            d.push_back(temp % 10);
            temp /= 10;
        }

        temp = curr;
        for(ll i= (totalLen % 2); i < d.size(); i++){
            temp *= 10;
            temp += d[i];
        }

        if(temp >= a && temp <= b && is_prime(temp)){
            ans++;
            // cout << temp << endl;
        }
        return;
    }

    // cout << curr << endl;
    for(ll i = 0; i < 10; i++){
        curr *= 10;
        curr += i;
        rec(curr, totalLen, currLen + 1, a, b);
        curr /= 10;
    }

    return;
}

void solve() {
    // Your code goes here
    ll a, b;
    cin >> a >> b;

    // find the total len
    ll len = 0, temp = b;
    while(temp){
        len++;
        temp /= 10;
    }

    for(ll i = 1; i <= len; i++) {
    	for(ll j = 1; j < 10; j++) {
    		rec(j, i, 1, a, b);
    	}
    }

    // why this is not working? 
    // because the len is fixed so it always generate the number
    // equl to the lenght which i don't want.
    // that why above two loop work
    // becasue i am considering every lenght
    // if i don't use the optimization to generate the prime then 
    // it will work fine.
    // for(ll curr = 1; curr < 10; curr++){
    //     rec(curr, len, 1, a, b);
    // }

    cout << ans;

}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    // Call your solve function or write code here
    solve();
    return 0;
}

// A number which is both a prime number as well as palindrome is called a Prime Palindrome. 
// 151 is a prime as well as a palindrome, hence 151 is a prime palindrome.
// Your task is to find the count of Prime Palindromes belonging to the given range [a, b].
// 5 500
// 12