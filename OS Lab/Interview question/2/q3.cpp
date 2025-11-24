#include <bits/stdc++.h>
using namespace std;

int secondLargest(vector<int>& nums) {
    int n=nums.size();
    int maxi=nums[0], secMaxi=INT_MIN;
    for(int i=1;i<n;i++){
        if(nums[i]>maxi){
            secMaxi=maxi;
            maxi=nums[i];
        }else if(nums[i]<maxi && nums[i]>secMaxi){
            secMaxi=nums[i];
        }
    }
    return secMaxi==INT_MIN?-1:secMaxi;
}

int main() {
    vector<int>nums{12,35,1,10,34,1};
    cout<<secondLargest(nums)<<endl;
    return 0;
}
