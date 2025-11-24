#include<bits/stdc++.h>
using namespace std;
void bubbleSort(vector<int>&at,vector<int>&bt,vector<int>&pid){
    int n=at.size();
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-1;j++){
            if(at[j]>at[j+1]){
                swap(at[j],at[j+1]);
                swap(pid[j],pid[j+1]);
                swap(bt[j],bt[j+1]);
            }
        }
    }
}
void readyQueue(queue<pair<int,int>>&rq,vector<bool>&remProcess,vector<int>&at,vector<int>&pid,int currTime){
    for(int i=0;i<at.size();i++){
        if(at[i]<=currTime && !remProcess[i]){
            rq.push({pid[i],i});
            remProcess[i]=1;
        }
    }
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
    vector<float>pr(n);
    vector<bool>remProcess(n,0);
    queue<pair<int,int>>rq;
    int tq;
    cout<<"Enter Time quantum for round robin:";
    cin>>tq;
    cout<<endl;
    for(int i=0;i<n;i++){
        cout<<"Enter Arrival time of P"<<i+1<<endl;
        int num;
        cin>>num;
        at[i]=num;
        pid[i]=i+1;
    }
    for(int i=0;i<n;i++){
        cout<<"Enter Burst time of P"<<i+1<<endl;
        int num;
        cin>>num;
        bt[i]=num;
    }
    bubbleSort(at,bt,pid);
    vector<int>remTime(bt);
    int currTime=at[0];
    int completed=0;
    readyQueue(rq,remProcess,at,pid,currTime);
    while(completed<n){
        if(rq.empty()){
            int nextArrival=INT_MAX;
            for(int i=0;i<n;i++){
                if(!remProcess[i])nextArrival=min(nextArrival,at[i]);
            }
            if(nextArrival==INT_MAX)break;
            currTime=nextArrival;
            readyQueue(rq,remProcess,at,pid,currTime);
        }
        int getID=rq.front().first;
        int index=rq.front().second;
        rq.pop();
        if(remTime[index]>tq){
            remTime[index]-=tq;
            currTime+=tq;
            readyQueue(rq,remProcess,at,pid,currTime);
            rq.push({getID,index});
        }
        else{
            currTime+=remTime[index];
            readyQueue(rq,remProcess,at,pid,currTime);
            remTime[index]=0;
            ct[index]=currTime;
            completed++;
        }
        
    }
    for(int i=0;i<n;i++){
        tat[i]=ct[i]-at[i];
        wt[i]=tat[i]-bt[i];
        pr[i]=tat[i]*1.0/bt[i];
    }
    cout<<"PID\tAT\tBT\tCT\tTAT\tWT\tPR"<<endl;
    for(int i=0;i<n;i++){
        cout<<pid[i]<<"\t"<<at[i]<<"\t"<<bt[i]<<"\t"<<ct[i]<<"\t"<<tat[i]<<"\t"<<wt[i]<<"\t"<<pr[i]<<endl;
    }
    int sumtat=0,sumwt=0;
    float sumpr=0;
    for(int i=0;i<n;i++){
        sumtat+=tat[i];
        sumwt+=wt[i];
        sumpr+=pr[i];
    }
    cout<<"Average Turn Around Time:"<<1.0*sumtat/n<<endl;
    cout<<"Average Waiting Time:"<<1.0*sumwt/n<<endl;
    cout<<"Average Penalty Ratio:"<<sumpr/n<<endl;
}