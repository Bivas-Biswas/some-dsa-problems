#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> generateSubsets(const vector<int>& nums) {
    vector<vector<int>> subsets = {{}};

    for (int num : nums) {
        int n = subsets.size();
        for (int i = 0; i < n; ++i) {
            vector<int> newSubset = subsets[i];
            newSubset.push_back(num);
            subsets.push_back(newSubset);
        }
    }

    return subsets;
}

int main() {
    vector<int> arr = {1, 2, 3};
    vector<vector<int>> allSubsets = generateSubsets(arr);

    cout << "All subsets:\n";
    for (const auto& subset : allSubsets) {
        cout << "{ ";
        for (int val : subset) {
            cout << val << " ";
        }
        cout << "}\n";
    }

    return 0;
}
