#include<bits/stdc++.h>
using namespace std;

struct Process{
        int p_id, at, ct, bt, tat, wt, rt;
};


void printGantt(vector<int>&gantt, vector<int>& et){
    int n = gantt.size();

    for(int i = 0; i<n; i++){
        cout<<"P"<<gantt[i]<<" ";
        cout<<"("<<et[i]<<") ";
        cout<<" | ";
    }
    cout<<endl;
}
void round_robin(vector<Process>& proc, int n, int tq, int first_pro_ind){
    // todo: ready queue and insert 1st element index in it
    // todo: get last process execution time as arrival time of 1st process
    // todo: calculate total burst time
    // Creating a ready queue
    queue<int>rq;
    //push the first process index into ready queue
    rq.push(first_pro_ind);
    // get last process execution time as arrival time of the process
    int lpet = proc[first_pro_ind].at;

    // Creating gantt vector and execution time vector
    vector<int> gantt, et;


    // Calculate total burst time 
    int tbt = 0;
    for(int i = 0; i<n ;i++){
        tbt += proc[i].bt;
    }

    while(tbt > 0){

        //! If my ready queue is empty but there are some process which is still remaining to execute fully then we need to push those processed to ready queue as well
        if(rq.empty()){
            int mini = INT_MAX;
            for(int i = 0; i<n; i++){
                if(!proc[i].rt)
                    continue;
                if(proc[i].at > lpet){
                    if(proc[i].at < mini){
                        mini = proc[i].at;
                        rq.push(i);
                    }
                }
            }
            lpet = mini;
        }

        // get the currect process
        int curr_pro_ind = rq.front();
        rq.pop();

        Process &curr_pro = proc[curr_pro_ind];
        // todo: Perform calculation for rr
        // remaining time will be minimum of remainting time and time quantum
        int pro_min_rt = min(tq, curr_pro.rt);
        curr_pro.ct = lpet + pro_min_rt;
        curr_pro.rt -= pro_min_rt;
        curr_pro.tat = curr_pro.ct - curr_pro.at;
        curr_pro.wt = curr_pro.tat - curr_pro.bt;

        tbt -= pro_min_rt;

        //Todo: If any process is arrived while curr_proc is executing then we need to push that process to ready queue
        for(int i = lpet+1; i<= lpet + pro_min_rt; i++){
            for(int j = 0; j<n; j++){
                if(proc[j].at == i){
                    rq.push(j);
                }
            }
        }

        //* If current process is remaining to execute then push it into ready queue again
        if(curr_pro.rt != 0){
            rq.push(curr_pro_ind);
        }
        //* Update the process execution time to the time its has been executed 
        lpet += pro_min_rt;
        gantt.push_back(curr_pro.p_id);
        et.push_back(curr_pro.ct);
    }

    cout<<"Gantt Chart: "<<endl;
    printGantt(gantt, et);
}

void printAnswer(vector<Process>&pro, int n){
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
}
int main()
{
    int n, tq;
    cout<<"Enter number of process: ";
    cin>>n;

    cout<<"\nEnter time quantum: ";
    cin>>tq;

    vector<Process> proc;

    //Todo: Find the process with minimum arrival time
    int first_proc_ind;
    int first_proc_at = INT_MAX;
    cout<<"Enter arrival time and burst time for each process: "<<endl;
    for(int i = 0; i<n; i++){
        cout<<"p"<<i<<" ";
        Process curr_proc;
        curr_proc.p_id = i;
        cin>>curr_proc.at;
        cin>>curr_proc.bt;

        curr_proc.rt = curr_proc.bt;
        curr_proc.wt = 0;
        curr_proc.tat = 0;
        curr_proc.ct = 0;

        proc.push_back(curr_proc);

        if(curr_proc.at < first_proc_at){
            first_proc_at = curr_proc.at;
            first_proc_ind = i;
        }
    }

    round_robin(proc, n, tq, first_proc_ind);
    printAnswer(proc, n);
    return 0;
}