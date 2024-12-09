// Priority Scheduling Algo - Non-Preemptive


#include <bits/stdc++.h>
using namespace std;

struct process
{
    int pid, at, bt, priority, mod_bt, ct, tat, wt;
};

vector<process> p;
int n;

void compute_all()
{
    int time = 0;
    int sum_t = 0;
    int current = -1;

    for (auto it = p.begin(); it != p.end(); it++)
    {
        sum_t += it->bt;
    }

    while (time < sum_t)
    {
        bool found_process = false;
        int min_bt = INT_MAX;
        int highest_priority = INT_MAX;
        int earliest_arrival = INT_MAX;

        for (int i = 0; i < n; i++)
        {
            if (p[i].at <= time && p[i].mod_bt > 0)
            {
                // Check for priority and then tie-breaking using arrival time
                if (p[i].priority < highest_priority ||
                    (p[i].priority == highest_priority && p[i].at < earliest_arrival))
                {
                    current = i;
                    min_bt = p[i].mod_bt;
                    found_process = true;
                    highest_priority = p[i].priority;
                    earliest_arrival = p[i].at;
                }
            }
        }

        if (!found_process)
        {
            time++;
            sum_t++; // Idle time also increases total time
            continue;
        }

        p[current].ct = time + 1;
        time = p[current].ct;
        p[current].mod_bt--;

        if (p[current].mod_bt == 0)
            min_bt = INT_MAX;
    }

    for (auto &it : p)
    {
        it.tat = it.ct - it.at;
        it.wt = it.tat - it.bt;
    }
}

void display_all()
{
    cout << "The details of all the processes:" << endl;
    cout << "PID\tAT\tBT\tPriority\tCT\tTAT\tWT" << endl;
    for (auto it : p)
    {
        cout << it.pid << "\t" << it.at << "\t" << it.bt << "\t" << it.priority << "\t\t" << it.ct << "\t" << it.tat << "\t" << it.wt << endl;
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
    }

    cout << "Enter Burst time for the processes" << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> p[i].bt;
        p[i].mod_bt = p[i].bt;
    }
    cout << "Enter Priority for the processes" << endl;
    for (int i = 0; i < n; i++)
        cin >> p[i].priority;

    compute_all();
    display_all();
}
