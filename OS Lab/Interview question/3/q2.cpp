#include <bits/stdc++.h>
using namespace std;
int longestSequence(vector<int>&nums){
    int n=nums.size();
    if(n==0)return 0;
    int maxlen=1,currlen=1;
    for(int i=1;i<n;i++){
        if(nums[i-1]==nums[i])currlen++;
        else currlen=1;
        maxlen=max(maxlen,currlen);
    }
    return maxlen;
}
int main()
{
    vector<int>nums={0, 1, 0, 1, 1, 1, 1};
    cout<<longestSequence(nums)<<endl;
    return 0;
}