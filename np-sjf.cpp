/*

WAP to implement 'Non-Preemptive Shortes Job First' algorithm.
Given are Process IDs, Arrival Time and Burst Time

Find and Display Wait time and Turnaround Time for each processes

*/

/*

Sort the processes as per their arrival time

Pick a new process with the shortest burst time

Apply formula for CT, TAT and WT

In case for idle time, keep incrementing the time counter

Mark the process as visited and repeat till all
processes are computed for

*/

#include <bits/stdc++.h>
using namespace std;

struct process
{
    int pid, at, bt,
        ct, tat, wt;
    bool visited;
};

vector<process> p;
int n;

static bool compare_at(process a, process b)
{
    if (a.at == b.at)
        return a.bt < b.bt;
    return a.at < b.at;
}

static bool compare_bt(const process *a, const process *b)
{
    return a->bt < b->bt;
}

bool cmp(process a, process b)
{
    return a.pid < b.pid;
}

void compute_all()
{
    // Ready Queue
    vector<process *> rq;
    int time = 0;
    sort(p.begin(), p.end(), compare_at);
    int count = 0;
    while (count < n)
    {

        for (auto &it : p)
        {
            if (it.at <= time && it.visited != 1)
                rq.push_back(&it);
        }

        sort(rq.begin(), rq.end(), compare_bt);

        if (!rq.empty())
        {
            process *tmp = rq.front();
            rq.erase(rq.begin());
            tmp->ct = time + tmp->bt;
            tmp->tat = tmp->ct - tmp->at;
            tmp->wt = tmp->tat - tmp->bt;
            time = tmp->ct;
            tmp->visited = 1;
            count++;
        }
        else
            time++;
        rq.clear();
    }
}

void display_all()
{
    cout << "The details of all the processes:" << endl;
    cout << "PID\tAT\tBT\tCT\tTAT\tWT" << endl;
    for (auto it : p)
    {
        cout << it.pid << "\t" << it.at << "\t" << it.bt << "\t" << it.ct << "\t" << it.tat << "\t" << it.wt << endl;
    }
}

int main()
{
    cout << "Enter number of processes" << endl;
    cin >> n;
    p.resize(n);
    cout << "Enter Arrival time for the processes" << endl;
    for (int i = 0; i < n; i++)
    {
        p[i].pid = i + 1;
        cin >> p[i].at;
        p[i].visited = 0;
    }
    cout << "Enter Burst time for the processes" << endl;
    for (int i = 0; i < n; i++)
        cin >> p[i].bt;
    compute_all();
    sort(p.begin(), p.end(), cmp);
    display_all();
    return 0;
}