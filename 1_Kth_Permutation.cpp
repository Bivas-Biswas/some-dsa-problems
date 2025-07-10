#include <bits/stdc++.h>

using namespace std;
#define endl "\n";

int n, k;
vector<int> arr;
vector<int> per;

void print(){
    for(auto a: per){
        cout<< a << " ";
    }
    cout << endl;
}

void solve(int k, int fact) {
    int idx = k / fact;
    per.push_back(arr[idx]);
    arr.erase(arr.begin() + idx);
    
    if(arr.size() == 0){
        print();
        return;
    }

    solve(k % fact, fact / arr.size());
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin  >> n >> k;

    if(n <= 13){
        for(int i =1; i<= n; i++){
            arr.push_back(i);
        }
    } else {

        for (int i = 1; i < n - 12; i++)
        {
            cout << i << " ";
        }

        for(int i = n - 12; i<= n; i++){
            arr.push_back(i);
        }
    }

    int fact = 1;
    n = arr.size();
    for(int i = 1; i < n; i++){
        fact *= i;
    }
    solve(k - 1, fact);

    return 0;
}

// Constraints
// 1 ≤ n ≤ 105

// 1 ≤ k ≤ min(n! , 109)

// Sample Input 1
// input:
// 3 4
// output: 
// 2 3 1

// Sample Input 1
// input:
// 10 3
// output:
// 1 2 3 4 5 6 7 9 8 10