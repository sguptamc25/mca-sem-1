#include <bits/stdc++.h>
using namespace std;
void convertToWave(vector<int>&nums){
    int n=nums.size();
    for (int i=0;i<n -1;i+=2) {
        swap(nums[i], nums[i + 1]);
    }
}
int main()
{
    vector<int>nums{2, 4, 7, 8, 9, 10};
    convertToWave(nums);
    for(auto it:nums){
        cout<<it<<" ";
    }
    return 0;
}