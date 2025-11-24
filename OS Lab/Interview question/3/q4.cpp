#include <bits/stdc++.h>
using namespace std;
int maximumTotalProfit(vector<int>&prices){
    int n=prices.size();
    if(n<=1)return 0;
    int totalProfit=0;
    for(int i=1;i<n;i++){
        if(prices[i]>prices[i-1])
        totalProfit+=prices[i]-prices[i-1];
    }
    return totalProfit;
}
int main()
{
    vector<int>prices{100, 180, 260, 310, 40, 535, 695};
    cout<<maximumTotalProfit(prices);
    return 0;
}