#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cout<<"--------------------FCFS DISK SCHEDULING-------------------------"<<endl;
    int head;
    cout<<"Enter head position:"<<endl;
    cin>>head;
    cout<<"Enter number of disk requests:"<<endl;
    cin>>n;
    vector<int>diskRequests(n);
    for(int i=0;i<n;i++){
        cout<<"Enter request number "<<i+1<<":"<<endl;
        cin>>diskRequests[i];
    }
    int totalSeekTime=0;
    int currPos=head;
    for(int i=0;i<diskRequests.size();i++){
        totalSeekTime+=max(diskRequests[i],currPos)-min(diskRequests[i],currPos);
        currPos=diskRequests[i];
    }
    cout<<"Total seek time using FCFS disk scheduling:"<<totalSeekTime<<endl;
    cout<<"Average seek time using FCFS disk scheduling:"<<totalSeekTime*1.0/n<<endl;
    return 0;
}