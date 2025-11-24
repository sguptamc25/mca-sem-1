#include<bits/stdc++.h>
using namespace std;

void bubbleSort(vector<int>&at,vector<int>&bt,vector<int>&pid){
    int n=at.size();
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-1-i;j++){
            if(at[j]>at[j+1]){
                swap(at[j],at[j+1]);
                swap(pid[j],pid[j+1]);
                swap(bt[j],bt[j+1]);
            }
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
    ct[0]=at[0]+bt[0];
    for(int i=1;i<n;i++){
        if(at[i]<=ct[i-1])
        ct[i]=ct[i-1]+bt[i];
        else 
        ct[i]=at[i]+bt[i];
    }
    for(int i=0;i<n;i++){
        tat[i]=ct[i]-at[i];
        wt[i]=tat[i]-bt[i];
    }
    cout<<"PID\tAT\tBT\tCT\tTAT\tWT"<<endl;
    for(int i=0;i<n;i++){
        cout<<pid[i]<<"\t"<<at[i]<<"\t"<<bt[i]<<"\t"<<ct[i]<<"\t"<<tat[i]<<"\t"<<wt[i]<<endl;
    }
    int sumtat=0,sumwt=0;
    for(int i=0;i<n;i++){
        sumtat+=tat[i];
        sumwt+=wt[i];
    }
    cout<<"Average Turn Around Time:"<<1.0*sumtat/n<<endl;
    cout<<"Average Waiting Time:"<<1.0*sumwt/n<<endl;
}