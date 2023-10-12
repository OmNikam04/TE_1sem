#include <bits/stdc++.h>
using namespace std;

void findSubsetsWithSum(vector<int>& nums, int k, vector<int>& currentSubset, int index) {
    if (k == 0) {
        cout<<endl;
        cout<<"-------------------------------------"<<endl;
        cout<<"Found the subset with k sum: "<<endl;
        cout<<"-------------------------------------"<<endl;
        for (int num : currentSubset) {
            cout << num << " ";
        }
        cout << endl;
        cout<<endl;
        return;
    }

    if (index == nums.size() || k < 0) {
        return;
    }

    cout<<"Adding "<<nums[index]<<" in current subset"<<endl;
    currentSubset.push_back(nums[index]);
    findSubsetsWithSum(nums, k - nums[index], currentSubset, index + 1);

    cout<<"Removing "<<nums.back()<<" from current subset"<<endl;
    currentSubset.pop_back();

    cout<<endl;
    cout<<"Started to backtrack"<<endl;
    findSubsetsWithSum(nums, k, currentSubset, index + 1);
}

void findSubsetsWithSum(vector<int>& nums, int k) {
    vector<int> currentSubset;
    findSubsetsWithSum(nums, k, currentSubset, 0);
}

int main() {
    cout<<"Enter size of array: ";
    int n; cin>>n;
    cout<<"Enter elements of array: ";
    vector<int> nums(n);
    for(auto &it: nums)cin>>it;
    cout<<"What is target: ";
    int k; cin>>k;

    findSubsetsWithSum(nums, k);

    return 0;
}
