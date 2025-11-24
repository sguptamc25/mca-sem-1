#include <bits/stdc++.h>
using namespace std;

int findMissing(vector<int>&nums) {
    int n=nums.size();
    int total=(n+1)*(n+2)/2;
    int sum = 0;
    for(int i=0;i<n;i++) sum +=nums[i];
    return total - sum;
}

int main() {
    vector<int>nums={1,2,3,5};
    cout<<findMissing(nums)<<endl;
    return 0;
}
