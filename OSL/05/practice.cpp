#include <bits/stdc++.h>
using namespace std;

#define res_ct 3
int main()
{
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
    int A, B, C;
    cout << "Enter Total number of resources of each type: (A, B, C): ";
    cin >> A >> B >> C;

    vector<vector<int>> allocation(n, vector<int>(3, 0));
    cout << "Enter allocated resources: " << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "P" << i + 1 << " ";
        for (int j = 0; j < res_ct; j++)
        {
            cin >> allocation[i][j];
        }
    }

    vector<vector<int>> max_avail(n, vector<int>(3, 0));
    cout << "Enter max available resources for each process: " << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "P" << i + 1 << " ";
        for (int j = 0; j < res_ct; j++)
        {
            cin >> max_avail[i][j];
        }
    }

    int ava, avb, avc;
    cout << "Enter available resources for each type: (A, B, C): ";
    cin >> ava >> avb >> avc;

    vector<vector<int>> needed(n, vector<int>(3, 0));
    // calculating the needed matrix
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < res_ct; j++)
        {
            needed[i][j] = max_avail[i][j] - allocation[i][j];
        }
    }

    // todo: Priting the needed matrix
    cout << "Sr.no\tA B C\n";
    for (int i = 0; i < n; i++)
    {
        cout << "P" << i + 1 << "\t";
        for (int j = 0; j < res_ct; j++)
        {
            cout << needed[i][j] << " ";
        }
        cout << endl;
    }

    // todo: Create safe sequence
    vector<int> safe_sequence;
    int completed = 0;
    while (completed!=n)
    {
        for (int i = 0; i < n; i++)
        {
            if ((needed[i][0] <= ava && needed[i][0]!=-1) && (needed[i][1] <= avb && needed[i][1]!=-1) && (needed[i][2] <= avc && needed[i][2]!=-1))
            {
                completed++;
                safe_sequence.push_back(i+1);
                ava += allocation[i][0];
                avb += allocation[i][1];
                avc += allocation[i][2];
                needed[i][0] = -1;
                needed[i][1] = -1;
                needed[i][2] = -1;
            }
        }
    }

    //todo: Priting safe sequence
    cout<<"\nSafe sequece: \n";
    for(auto it: safe_sequence){
        cout<<"P"<<it<<" ";
    }cout<<endl;

    cout<<"Currently available resources: (A, B, C)"<<endl;
    cout<<ava<<" "<<avb<<" "<<avc<<" ";
    cout<<endl;
    return 0;
}