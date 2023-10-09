#include<bits/stdc++.h>
using namespace std;

int main()
{
    // resources A,B,C
    int n;
    cout<<"Enter Number of proceses: ";
    cin>>n;
    cout<<"Enter the total Number of resources of each type (A,B,C): ";
    int A,B,C;
    cin>>A>>B>>C;

    vector<vector<int>>allocate(n, vector<int>(3,0));
    cout<<"Enter Allocated resources: \n";
    for(int i=0; i<n; i++)
    {
        cout<<"Enter the allocated resources for P"<<i+1<<endl;
        for(int j=0; j<3; j++)
        {
            cin>>allocate[i][j];
        }
    }

    vector<vector<int>>maxreq(n, vector<int>(3,0));
    cout<<"Enter Maximum Required resources: \n";
    for(int i=0; i<n; i++)
    {
        cout<<"Enter the required resources for P"<<i+1<<endl;
        for(int j=0; j<3; j++)
        {
            cin>>maxreq[i][j];
        }
    }
    // vector<vector<int>>availres;
    cout<<"Enter Currently Available resources of each type(A,B,C)\n";
    int ava,avb,avc;
    cin>>ava>>avb>>avc;

    vector<vector<int>>needed(n, vector<int>(3,0));
    for(int i=0; i<n; i++){
        for(int j=0; j<3; j++){
            needed[i][j] = maxreq[i][j]-allocate[i][j];
        }
    }

    //needed matrix
    cout<<"\n\n\nSr.NO\tA\tB\tC"<<endl;
    cout<<endl;
    for(int i=0; i<n; i++){
        cout<<"P"<<i+1<<"\t";
        for(int j=0; j<3; j++){
            cout<<needed[i][j]<<"\t";
        }
        cout<<endl;
    }

    vector<int>processes;
    int completed=0;
    while(completed!=n)
    {
        for(int i=0; i<n; i++){
            if((needed[i][0]<=ava && needed[i][0] != -1) && (needed[i][1]<=avb && needed[i][1] != -1) && (needed[i][2]<=avc && needed[i][2] != -1)){
                completed++;
                processes.push_back(i+1);
                ava+=allocate[i][0];
                avb+=allocate[i][1];
                avc+=allocate[i][2];
                needed[i][0] = -1;
                needed[i][1] = -1;
                needed[i][2] = -1;
            }
        }
    }

    cout<<"\n\n\nCurrenty Available Resources: "<<endl;
    cout<<ava<<" "<<avb<<" "<<avc<<endl;
    cout<<"\n\nThe Order Of Completion of processes is: "<<endl;
    for(int i=0; i<n; i++){
        cout<<"P"<<processes[i]<<"\t";
    }
    return 0;
}