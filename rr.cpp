#include <bits/stdc++.h>
using namespace std;

struct process
{
    int pid, at, bt, mod_bt, visited, ct, tat, wt;
};

vector<process> p;
int n;
int tq;

bool compare(process a, process b)
{
    return a.at < b.at;
}

bool cmp(process a, process b)
{
    return a.pid < b.pid;
}

void compute_all()
{
    int time = 0;
    // rq must have the reference to the original objects of p
    // and not the copies of them, therefore we use pointers
    queue<process *> rq;
    int count = 0;

    while (count < n)
    {
        for (auto &it : p)
        {
            if (it.at <= time && it.visited == 0)
            {
                rq.push(&it);
                it.visited = 1;
            }
        }

        if (rq.empty())
        {
            time++;
            continue;
        }
        else
        {
            process *current = rq.front();
            rq.pop();

            if (current->mod_bt > tq)
            {
                time += tq;
                current->mod_bt -= tq;

                for (auto &it : p)
                {
                    if (it.at <= time && it.visited == 0)
                    {
                        rq.push(&it);
                        it.visited = 1;
                    }
                }
                rq.push(current);
            }
            else
            {
                time += current->mod_bt;
                current->ct = time;
                current->mod_bt = 0;
                count++;
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
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

    cout << "Enter Time Quantum" << endl;
    cin >> tq;

    cout << "Enter Arrival time for the processes" << endl;
    for (int i = 0; i < n; i++)
    {
        p[i].pid = i + 1;
        cin >> p[i].at;
        p[i].visited = 0;
    }

    cout << "Enter Burst time for the processes" << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> p[i].bt;
        p[i].mod_bt = p[i].bt;
    }

    sort(p.begin(), p.end(), compare);

    compute_all();

    sort(p.begin(), p.end(), cmp);

    display_all();

    return 0;
}
