#include <bits/stdc++.h>
using namespace std;
vector<int> subarraySum(vector<int>&nums,int target) {
    int n=nums.size();
    for(int i=0;i<n;i++){
        int sum=0;
        for(int j=i;j<n;j++){
            sum+=nums[j];
            if(sum==target)return {i+1,j+1};
        }
    }
    return {-1};
}
int main() {
    vector<int> arr1={1,2,3,7,5};
    int target1=12;
    vector<int>result1=subarraySum(arr1, target1);
    if(result1.size()==2)cout<<"["<<result1[0]<<","<<result1[1]<<"]\n";
    else cout<<"["<<result1[0]<<"]\n";
    return 0;
}