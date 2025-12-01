#include<bits/stdc++.h>
using namespace std;

void bubbleSort(vector<int>&at, vector<int>&bt, vector<int>&pid, vector<int>&prio){
    int n=at.size();
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-1;j++){
            if(at[j]>at[j+1] || (at[j]==at[j+1] && pid[j]>pid[j+1])){
                swap(at[j],at[j+1]); swap(pid[j],pid[j+1]);
                swap(bt[j],bt[j+1]); swap(prio[j],prio[j+1]);
            }
        }
    }
}

int getPID(vector<int>&bt, vector<int>&at, vector<int>&remProcess, int currTime, vector<int>&remTime, vector<int>&prio){
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>pq;
    for(int pid : remProcess){
        int i = pid - 1; 
        // Process must be Priority 3 (Batch), Arrived, and Not Completed
        if(at[i]<=currTime && remTime[i]>0 && prio[i] == 3){
             pq.push({remTime[i], at[i]*1000 + pid});
        }
    }
    if(pq.empty()) return -1;
    return pq.top().second % 1000;
}

int main(){
    cout<<"--- MLQ SCHEDULER ---"<<endl;
    int n; cout<<"Enter number of processes: "; cin>>n;
    vector<int>pid(n), at(n), bt(n), prio(n), ct(n), tat(n), wt(n);
    vector<float>pr(n);
    for(int i=0;i<n;i++){ cout<<"AT P"<<i+1<<": "; cin>>at[i]; pid[i]=i+1; }
    for(int i=0;i<n;i++){ cout<<"BT P"<<i+1<<": "; cin>>bt[i]; }
    for(int i=0;i<n;i++){ cout<<"Prio P"<<i+1<<" (1=Sys, 2=Int, 3=Bat): "; cin>>prio[i]; }

    bubbleSort(at, bt, pid, prio);

    vector<int>remTime(bt);
    vector<int>remProcess; for(int x:pid) remProcess.push_back(x);
    vector<int>slice(n,0);
    vector<bool>in_q(n, false);
    
    queue<int> q0, q1; // Store Indices directly
    int completed=0, currTime=at[0];

    // Initial load
    for(int i=0; i<n; i++){
        if(at[i]<=currTime){
            if(prio[i]==1) { q0.push(i); in_q[i]=true; }
            else if(prio[i]==2) { q1.push(i); in_q[i]=true; }
        }
    }

    while(completed<n){
        int idx = -1, type = 0; // 1=Q0, 2=Q1, 3=Q2

        // Priority Check
        if(!q0.empty()){ idx=q0.front(); type=1; }
        else if(!q1.empty()){ idx=q1.front(); type=2; }
        else {
            int id = getPID(bt, at, remProcess, currTime, remTime, prio);
            if(id!=-1) { 
                for(int i=0;i<n;i++) if(pid[i]==id) idx=i; 
                type=3; 
            }
        }

        if(idx != -1){
            // Execution
            remTime[idx]--;
            currTime++;
            if(type==1 || type==2) slice[idx]++;

            // ADD NEW ARRIVALS (Critical for P2 before P1 logic)
            for(int i=0; i<n; i++){
                if(at[i] == currTime && remTime[i]>0 && prio[i]!=3 && !in_q[i]){
                    if(prio[i]==1) { q0.push(i); in_q[i]=true; }
                    else if(prio[i]==2) { q1.push(i); in_q[i]=true; }
                }
            }

            if(remTime[idx] == 0){
                completed++;
                ct[idx] = currTime;
                if(type==1) q0.pop();
                else if(type==2) q1.pop();
                // Q2 handled by getPID
            }
            else {
                // Check Quantum or Preemption
                bool drop = false;
                if(type==1 && slice[idx]==4) drop=true;
                if(type==2 && slice[idx]==8) drop=true;
                
                // Preemption Logic: If I am Q1, and Q0 has something now
                if(type==2 && !q0.empty()) drop=true; 
                // Note: If preempted, slice is NOT reset in strict RR, but simplified here we often push back. 
                // If preempted, we should reset slice if we want "fresh" quantum next time, or keep it. 
                // Standard MLQ: Preemption puts you back at tail.
                
                if(drop){
                    if(type==1) { q0.pop(); q0.push(idx); slice[idx]=0; }
                    else if(type==2) { q1.pop(); q1.push(idx); slice[idx]=0; }
                }
            }
        } else {
            currTime++;
            for(int i=0; i<n; i++){
                if(at[i] == currTime && remTime[i]>0 && prio[i]!=3 && !in_q[i]){
                    if(prio[i]==1) { q0.push(i); in_q[i]=true; }
                    else if(prio[i]==2) { q1.push(i); in_q[i]=true; }
                }
            }
        }
    }

    // Output
    cout<<"PID\tPrio\tAT\tBT\tCT\tTAT\tWT\tPR"<<endl;
    int sumtat=0, sumwt=0; float sumpr=0;
    for(int i=0;i<n;i++){
        tat[i]=ct[i]-at[i]; wt[i]=tat[i]-bt[i]; pr[i]=(float)tat[i]/bt[i];
        cout<<pid[i]<<"\t"<<prio[i]<<"\t"<<at[i]<<"\t"<<bt[i]<<"\t"<<ct[i]<<"\t"<<tat[i]<<"\t"<<wt[i]<<"\t"<<pr[i]<<endl;
        sumtat+=tat[i]; sumwt+=wt[i]; sumpr+=pr[i];
    }
    cout<<"Avg TAT: "<<(float)sumtat/n<<endl;
    cout<<"Avg WT: "<<(float)sumwt/n<<endl;
    cout<<"Avg PR: "<<sumpr/n<<endl;
}