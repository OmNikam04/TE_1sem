// Round Robbin

#include <bits/stdc++.h>

using namespace std;

struct Process
{
    int p_id, at, bt, ct, wt, tat, rt;
};

void printgantt(const vector<int> &gantt, const vector<int> &et)
{
    int n = gantt.size();
    for (int i = 0; i < n; i++)
    {
        cout << " P" << gantt[i];
        // if p1 is executed from 0-2 and then 2-4 then it should only show once
        if (i < n && gantt[i] != gantt[i + 1])
        {
            cout << " (" << et[i] << ") ";
        }
        cout << " | ";
    }
    cout << endl;
}

void rr(vector<Process> &pro, int n, int tq, int first_pro_ind)
{
    queue<int> rq;
    vector<int> gantt;
    vector<int> et;
    int tbt = 0;
    for (int i = 0; i < n; i++)
    {
        tbt += pro[i].bt;
    }
    rq.push(first_pro_ind);
    int lpet = pro[first_pro_ind].at;
    while (tbt > 0)
    {
        // check to calculate last process execution time
        if (rq.empty())
        {
            int mini = INT_MAX;
            for (int i = 0; i < n; i++)
            {
                if (!pro[i].rt)
                    continue;
                if (pro[i].at > lpet)
                {
                    if (pro[i].at < mini)
                    {
                        mini = pro[i].at;
                        rq.push(i);
                    }
                }
            }
            lpet = mini;
        }
        int cur_pro_ind = rq.front();
        rq.pop();
        Process &cur_pro = pro[cur_pro_ind];
        // if process minimum time is 2 and time quantum is 3 then time allocated should be 2
        int pro_min_rt = min(tq, cur_pro.rt);
        cur_pro.ct = lpet + pro_min_rt;
        cur_pro.rt -= pro_min_rt;
        cur_pro.tat = cur_pro.ct - cur_pro.at;
        cur_pro.wt = cur_pro.tat - cur_pro.bt;
        tbt -= pro_min_rt;

        // if any process has arrived between last process execution while last process is executing
        // then we need to push that process into ready queue
        for (int i = lpet + 1; i <= lpet + pro_min_rt; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (pro[j].at == i)
                {
                    rq.push(j);
                }
            }
        }
        if (cur_pro.rt != 0)
        {
            rq.push(cur_pro_ind);
        }
        // 1st process lpet is 4 then next process should start executing from 5
        // lpet has arrival time
        // if AT is 0 and proMinRt is 4 then next process should start executing at 5
        lpet += pro_min_rt;
        gantt.push_back(cur_pro.p_id);
        et.push_back(cur_pro.ct);
    }
    cout << "GANTT CHART:-" << endl;
    printgantt(gantt, et);
}
int main()
{
    int n, tq;
    cout << "Enter the number of processes: ";
    cin >> n;
    cout << "Enter the time quantum: ";
    cin >> tq;
    vector<Process> pro;
    int first_pro_at = INT_MAX;
    int first_pro_ind;
    cout << "Enter the process details: \n";
    for (int i = 0; i < n; i++)
    {
        Process process;
        process.p_id = i;
        cout << "Process " << i + 1 << endl;
        cout << "Enter the arrival time: ";
        cin >> process.at;
        cout << "Enter the burst time: ";
        cin >> process.bt;
        process.rt = process.bt;
        process.ct = 0;
        process.wt = 0;
        process.tat = 0;
        pro.push_back(process);

        if (process.at < first_pro_at)
        {
            first_pro_at = process.at;
            first_pro_ind = i;
        }
    }

    rr(pro, n, tq, first_pro_ind);
    cout << "Process\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurn-around Time\n";
    for (int i = 0; i < n; i++)
    {
        cout << pro[i].p_id << "\t\t" << pro[i].at << "\t\t" << pro[i].bt << "\t\t" << pro[i].ct << "\t\t" << pro[i].wt << "\t\t" << pro[i].tat << endl;
    }
    cout << endl;
    float awt = 0.0, atat = 0.0;
    for (int i = 0; i < n; i++)
    {
        awt += pro[i].wt;
        atat += pro[i].tat;
    }
    awt = awt / n;
    atat = atat / n;
    cout << "Average Waiting time is: " << awt << endl;
    cout << "Average Turn around time is: " << atat << endl;

    return 0;
}