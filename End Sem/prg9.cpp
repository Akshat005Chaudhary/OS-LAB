// First Come First Served Scheduling Algo

#include <bits/stdc++.h>
using namespace std;

struct process
{
    int pid, at, bt,
        ct, tat, wt;
};

vector<process> p;

bool compare(process a, process b)
{
    if (a.at == b.at)
        return a.bt < b.bt;
    return a.at < b.at;
}

bool cmp(process a, process b)
{
    return a.pid < b.pid;
}

void compute_all()
{
    int time = 0;
    // Passing by reference is necessary otherwises changes
    // will be made to the copies of p and not to p actually
    for (auto &it : p)
    {
        while (time < it.at)
            time++;
        it.ct = time + it.bt;
        time = it.ct;
        it.tat = it.ct - it.at;
        it.wt = it.tat - it.bt;
    }
}

int display_all()
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
    int n;
    cout << "Enter number of processes" << endl;
    cin >> n;
    p.resize(n);
    cout << "Enter Arrival time for the processes" << endl;
    for (int i = 0; i < n; i++)
    {
        p[i].pid = i + 1;
        cin >> p[i].at;
    }
    cout << "Enter Burst time for the processes" << endl;
    for (int i = 0; i < n; i++)
        cin >> p[i].bt;
    sort(p.begin(), p.end(), compare);
    compute_all();
    sort(p.begin(), p.end(), cmp);
    display_all();
    return 0;
}