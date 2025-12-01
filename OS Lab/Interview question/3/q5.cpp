#include <bits/stdc++.h>
using namespace std;
void rearrange(vector<int>&nums){
    int n=nums.size();
    vector<int>pos,neg;
    for(int i=0;i<n;i++){
        if(nums[i]>=0)pos.push_back(nums[i]);
        else neg.push_back(nums[i]);
    }
    int posIndex=0,negIndex=0,numIndex=0;
    while(posIndex<pos.size() && negIndex<neg.size()){
        nums[numIndex++]=pos[posIndex++];
        nums[numIndex++]=neg[negIndex++];
    }
    while(posIndex<pos.size())nums[numIndex++]=pos[posIndex++];
    while(negIndex<neg.size())nums[numIndex++]=pos[negIndex++];
}
int main()
{
    vector<int>nums{-5, -2, 5, 2, 4, 7, 1, 8, 0, -8};
    rearrange(nums);
    for(auto num:nums){
        cout<<num<<" ";
    }
    return 0;
}