#include <bits/stdc++.h>
using namespace std;

struct process{
    int pid;
    int max_req;
    int allocated;
    int future_needs;
};

struct cmp{
    bool operator()(const process& a, const process& b){
        if(a.future_needs==b.future_needs) return a.allocated<b.allocated;
        return a.future_needs>b.future_needs;
    }
};


int main(){
    int n;
    cout<<"Enter number of processes"<<endl;
    cin>>n;
    int resources;
    cout<<"Enter total resources"<<endl;
    cin>>resources;
    vector<process> p(n);
    cout<<"Enter Max Requirements and Allocated Resources of each process"<<endl;
    int occupied = 0;
    for(int i=0;i<n;i++){
        cin>>p[i].max_req;
        cin>>p[i].allocated;
        p[i].future_needs = p[i].max_req-p[i].allocated;
        occupied += p[i].allocated;
        p[i].pid = i+1;
    }
    int avaliable = resources - occupied;
    priority_queue<process, vector<process>, cmp> pq; 
    for(auto it: p){
        pq.push(it);
    }
    vector<int> safe_state;
    while(!pq.empty()){
        auto it = pq.top();
        if(it.future_needs>avaliable){
            cout<<"No Safe Start"<<endl;
            return 0;
        }
        avaliable += it.allocated;
        safe_state.push_back(it.pid);
        pq.pop();
    }
    cout<<"Safe State Sequence: ";
    for(auto it: safe_state){
        cout<<"P"<<it<<"    ";
    }
    return 0;
}