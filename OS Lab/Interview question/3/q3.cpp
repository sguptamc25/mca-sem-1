#include <bits/stdc++.h>
using namespace std;
int maximumProfit(vector<int>&prices){
    int n=prices.size();
    if(n<=1)return 0;
    int maxProfit=0;
    int minPrice=prices[0];
    for(int i=1;i<n;i++){
        minPrice=min(minPrice,prices[i]);
        maxProfit=max(maxProfit,prices[i]-minPrice);
    }
    return maxProfit;
}
int main()
{
    vector<int>prices{7, 10, 1, 3, 6, 9, 2};
    cout<<maximumProfit(prices);
    return 0;
}