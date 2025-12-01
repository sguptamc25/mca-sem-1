#include <bits/stdc++.h>
using namespace std;

int maxSubarraySum(vector<int>& arr) {
    int n=arr.size();
    int maxSum=INT_MIN;
    for(int i=0;i<n;i++){
        int currSum=0;
        for(int j=i;j<n;j++){
            currSum+=arr[j];
            maxSum=max(maxSum,currSum);
        }
    }
    return maxSum;
}

int main() {
    vector<int>nums{2,3,-8,7,-1,2,3};
    cout<<maxSubarraySum(nums)<<endl;
    return 0;
}
