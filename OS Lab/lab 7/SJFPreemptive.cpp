#include<bits/stdc++.h>
using namespace std;
int getPID(vector<int>&bt,vector<int>&at,vector<int>&remProcess,int currTime){
    int n=remProcess.size();
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>pq;
    for(int i=0;i<n;i++){
        int pid=remProcess[i];
        if(at[pid-1]<=currTime)pq.push({bt[pid-1],at[pid-1]*1000+pid});
    }
    if(pq.empty())return -1;
    int encoded=pq.top().second;
    return encoded%1000;
}

int main(){
    int n;
    cout<<"Enter number of processes:"<<endl;
    cin>>n;
    vector<int>pid(n);
    vector<int>at(n);
    vector<int>bt(n);
    vector<int>ct(n);
    vector<int>tat(n);
    vector<int>wt(n);
    vector<int>remProcess(n);
    vector<int>remTime(n);
    for(int i=0;i<n;i++){
        cout<<"Enter Arrival time of P"<<i+1<<endl;
        int num;
        cin>>num;
        at[i]=num;
        pid[i]=i+1;
        remProcess[i]=i+1;
    }
    for(int i=0;i<n;i++){
        cout<<"Enter Burst time of P"<<i+1<<endl;
        int num;
        cin>>num;
        bt[i]=num;
        remTime[i]=num;
    }
    int currTime=*min_element(at.begin(),at.end());
    while(!remProcess.empty()){
        int getID=getPID(bt,at,remProcess,currTime);
        if(getID==-1){
            currTime++;
            continue;
        }
        remTime[getID-1]--;
        if(remTime[getID-1]==0){
            for(int i=0;i<remProcess.size();i++){
            if(remProcess[i]==getID){
                remProcess.erase(remProcess.begin()+i);
                break;
            }
            }
            ct[getID-1]=currTime+1;
        }
        currTime++;
    }
    for(int i=0;i<n;i++){
        tat[i]=ct[i]-at[i];
        wt[i]=tat[i]-bt[i];
    }
    cout<<"PID\tAT\tBT\tCT\tTAT\tWT"<<endl;
    for(int i=0;i<n;i++){
        cout<<pid[i]<<"\t"<<at[i]<<"\t"<<bt[i]<<"\t"<<ct[i]<<"\t"<<tat[i]<<"\t"<<wt[i]<<"\t"<<endl;
    }
    int sumtat=0,sumwt=0;
    for(int i=0;i<n;i++){
        sumtat+=tat[i];
        sumwt+=wt[i];
    }
    cout<<"Average Turn Around Time:"<<1.0*sumtat/n<<endl;
    cout<<"Average Waiting Time:"<<1.0*sumwt/n<<endl;
}