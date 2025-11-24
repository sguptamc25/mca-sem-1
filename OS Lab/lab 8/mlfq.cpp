#include<bits/stdc++.h>
using namespace std;

void bubbleSort(vector<int>&at, vector<int>&bt, vector<int>&pid){
    int n=at.size();
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-1;j++){
            if(at[j]>at[j+1] || (at[j]==at[j+1] && pid[j]>pid[j+1])){
                swap(at[j],at[j+1]); swap(pid[j],pid[j+1]); swap(bt[j],bt[j+1]);
            }
        }
    }
}

// SRTF Logic checks if process is in Q2 (Level 2)
int getPID(vector<int>&bt, vector<int>&at, vector<int>&remProcess, int currTime, vector<int>&remTime, vector<int>&level){
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>pq;
    for(int pid : remProcess){
        int i = pid - 1; 
        if(at[i]<=currTime && remTime[i]>0 && level[i] == 2){
             pq.push({remTime[i], at[i]*1000 + pid});
        }
    }
    if(pq.empty()) return -1;
    return pq.top().second % 1000;
}

int main(){
    cout<<"--- MLFQ SCHEDULER ---"<<endl;
    int n; cout<<"Enter number of processes: "; cin>>n;
    vector<int>pid(n), at(n), bt(n), ct(n), tat(n), wt(n);
    vector<float>pr(n);
    for(int i=0;i<n;i++){ cout<<"AT P"<<i+1<<": "; cin>>at[i]; pid[i]=i+1; }
    for(int i=0;i<n;i++){ cout<<"BT P"<<i+1<<": "; cin>>bt[i]; }

    bubbleSort(at, bt, pid);

    vector<int>remTime(bt);
    vector<int>remProcess; for(int x:pid) remProcess.push_back(x);
    vector<int>slice(n,0);
    vector<int>level(n,0); // 0=Q0, 1=Q1, 2=Q2
    vector<bool>in_q(n, false);
    
    queue<int> q0, q1; 
    int completed=0, currTime=at[0];

    // Initial load (All go to Q0)
    for(int i=0; i<n; i++){
        if(at[i]<=currTime){ q0.push(i); in_q[i]=true; }
    }

    while(completed<n){
        int idx = -1, type = 0; 

        if(!q0.empty()){ idx=q0.front(); type=0; }
        else if(!q1.empty()){ idx=q1.front(); type=1; }
        else {
            int id = getPID(bt, at, remProcess, currTime, remTime, level);
            if(id!=-1) { for(int i=0;i<n;i++) if(pid[i]==id) idx=i; type=2; }
        }

        if(idx != -1){
            remTime[idx]--;
            currTime++;
            if(type==0 || type==1) slice[idx]++;

            // ADD NEW ARRIVALS to Q0
            for(int i=0; i<n; i++){
                if(at[i] == currTime && remTime[i]>0 && !in_q[i]){
                    q0.push(i); in_q[i]=true; 
                }
            }

            if(remTime[idx] == 0){
                completed++;
                ct[idx] = currTime;
                if(type==0) q0.pop();
                else if(type==1) q1.pop();
            }
            else {
                // Logic: Pop, Demote, Push
                bool demote = false;
                if(type==0 && slice[idx]==4) { 
                    q0.pop(); 
                    level[idx]=1; slice[idx]=0; 
                    q1.push(idx); // Move to Q1
                }
                else if(type==1 && slice[idx]==8) {
                    q1.pop();
                    level[idx]=2; // Move to Q2 (SRTF)
                    // No push needed, getPID checks 'level' vector
                }
                else if(type==1 && !q0.empty()){
                    // Preemption: Q1 running, new Q0 process arrived
                    q1.pop();
                    q1.push(idx); // Put back in Q1
                    // Note: In strict MLFQ, we might keep slice or reset. Keeping usage is fair.
                }
            }
        } else {
            currTime++;
            for(int i=0; i<n; i++){
                if(at[i] == currTime && remTime[i]>0 && !in_q[i]){
                    q0.push(i); in_q[i]=true; 
                }
            }
        }
    }

    cout<<"PID\tAT\tBT\tCT\tTAT\tWT\tPR"<<endl;
    int sumtat=0, sumwt=0; float sumpr=0;
    for(int i=0;i<n;i++){
        tat[i]=ct[i]-at[i]; wt[i]=tat[i]-bt[i]; pr[i]=(float)tat[i]/bt[i];
        cout<<pid[i]<<"\t"<<at[i]<<"\t"<<bt[i]<<"\t"<<ct[i]<<"\t"<<tat[i]<<"\t"<<wt[i]<<"\t"<<pr[i]<<endl;
        sumtat+=tat[i]; sumwt+=wt[i]; sumpr+=pr[i];
    }
    cout<<"Avg TAT: "<<(float)sumtat/n<<endl;
    cout<<"Avg WT: "<<(float)sumwt/n<<endl;
    cout<<"Avg PR: "<<sumpr/n<<endl;
}