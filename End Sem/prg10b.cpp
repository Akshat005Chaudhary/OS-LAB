// Shortest Job First Scheduling Algo - Preemptive


#include <bits/stdc++.h>
using namespace std;

struct process
{
    int pid, at, bt, mod_bt, ct, tat, wt;
};

vector<process> p;
int n;

void compute_all()
{
    int time = 0;
    int sum_t = 0;
    int shortest = -1;

    for (auto it = p.begin(); it != p.end(); it++)
    {
        sum_t += it->bt;
    }

    while (time < sum_t)
    {
        bool found_process = false;
        int min_bt = INT_MAX;

        for (int i = 0; i < n; i++)
        {
            if (p[i].at <= time && p[i].mod_bt > 0 && p[i].mod_bt < min_bt)
            {
                shortest = i;
                min_bt = p[i].mod_bt;
                found_process = true;
            }
        }

        if (!found_process)
        {
            time++;
            // Idle time also increases total time
            // Therefore its essential to update sum_t
            sum_t++;
            continue;
        }

        p[shortest].ct = time + 1;
        time = p[shortest].ct;
        p[shortest].mod_bt--;

        if (p[shortest].mod_bt == 0)
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
    }

    cout << "Enter Burst time for the processes" << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> p[i].bt;
        p[i].mod_bt = p[i].bt;
    }

    compute_all();
    display_all();
}
