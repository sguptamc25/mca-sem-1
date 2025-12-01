#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n,minRequest,maxRequest;
    cout<<"--------------------C-SCAN DISK SCHEDULING-------------------------"<<endl;
    cout<<"Enter range of requests.\nMinimum request:"<<endl;
    cin>>minRequest;
    cout<<"Maximum request:"<<endl;
    cin>>maxRequest;
    int head;
    cout<<"Enter head position:"<<endl;
    cin>>head;
    cout<<"Enter number of disk requests:"<<endl;
    cin>>n;
    vector<int>diskRequests(n);
    int justbeforeHead=minRequest,justAfterHead=maxRequest;
    for(int i=0;i<n;i++){
        cout<<"Enter request number "<<i+1<<":"<<endl;
        cin>>diskRequests[i];
        if(diskRequests[i]<=head && diskRequests[i]>justbeforeHead)justbeforeHead=diskRequests[i];
        if(diskRequests[i]>=head && diskRequests[i]<justAfterHead)justAfterHead=diskRequests[i];
    }
    bool isHigher;
    cout<<"Enter where the head moves first.\nPress 0-Towards lower value\nPress 1-Towards higher value"<<endl;
    cin>>isHigher;
    int totalSeekTime;
    if(isHigher)totalSeekTime=(maxRequest-head)+(maxRequest-minRequest)+(justbeforeHead-minRequest);
    else totalSeekTime=(head-minRequest)+(maxRequest-minRequest)+(maxRequest-justAfterHead);
    cout<<"Total seek time using C-SCAN disk scheduling:"<<totalSeekTime<<endl;
    cout<<"Average seek time using C-SCAN disk scheduling:"<<totalSeekTime*1.0/n<<endl;
    return 0;
}