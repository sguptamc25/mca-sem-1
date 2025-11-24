#include <bits/stdc++.h>
using namespace std;
int minimizeHeightDiff(vector<int>& arr, int k) {
    int n = arr.size();
    int minDiff = INT_MAX;
    int totalComb = 1<<n;
    for(int mask=0; mask<totalComb; mask++) {
        vector<int> temp(n);
        bool valid = true;
        for(int i=0;i<n;i++){
            if(mask & (1<<i)) temp[i] = arr[i] + k;
            else temp[i] = arr[i] - k;
            if(temp[i] < 0) valid = false;
        }
        if(valid){
            int currMax = *max_element(temp.begin(), temp.end());
            int currMin = *min_element(temp.begin(), temp.end());
            minDiff = min(minDiff, currMax - currMin);
        }
    }
    return minDiff;
}
int main() {
    vector<int> arr{1,5,8,10};
    int k=2;
    cout<<minimizeHeightDiff(arr, k)<<endl;
    return 0;
}
