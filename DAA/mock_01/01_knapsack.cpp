#include<bits/stdc++.h>
using namespace std;

int temp[102][1002];

void showSelectedItems(int items, int capacity, vector<int> &wt)
{
    int i = items;
    int j = capacity;
    cout << "Items selected: ";
    while (i > 0 && j > 0)
    {
        if (temp[i][j] == temp[i - 1][j])
        {
            i--;
        }
        else
        {
            cout << i << " ";
            j = j - wt[i - 1];
            i--;
        }
    }
    cout<<endl;
}

void knapsack(vector<int> weight, vector<int> profit, int n, int capacity)
{
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= capacity; j++)
        {
            if (i == 0 || j == 0)
            {
                temp[i][j] = 0;
            }
        }
    }

    for (int i = 1; i < n + 1; i++)
    {
        for (int j = 1; j < capacity + 1; j++)
        {
            if (weight[i - 1] <= j)
            {
                temp[i][j] = max(profit[i - 1] + temp[i - 1][j - weight[i - 1]], temp[i - 1][j]);
            }
            else
            {
                temp[i][j] = temp[i - 1][j];
            }
        }
    }

    cout << "Do you want to see tabulation: y/n\t";
    char ch;
    cin >> ch;
    if (ch == 'y' || ch == 'Y')
    {
        for (int i = 0; i <= n; i++)
        {
            for (int w = 0; w <= capacity; w++)
            {
                cout << temp[i][w] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    cout << "Do you want to see selected items: y/n\t";
    char ch2;
    cin >> ch2;
    if (ch2 == 'y' || ch2 == 'Y')
        showSelectedItems(n, capacity, weight);
    cout << "Maximum profit obtained using 0/1 knapsack is : " << temp[n][capacity] << endl;
}

int main(){
    int n; 
    cout<<"Enter the number of items"<<endl;
    cin>>n;

    vector<int>weight(n);
    vector<int>profit(n);

    cout<<"Enter weight for each items"<<endl;
    for(int i = 0; i<n; i++)
    {
        cin>>weight[i];
    }
    cout<<"Enter profit for each item"<<endl;
    for (int i = 0; i < n; i++)
    {
        cin>>profit[i];
    }
    cout<<"Enter capacity for knapsack"<<endl;
    int capacity;
    cin>>capacity;
    knapsack(weight, profit, n, capacity);
    return 0;
}
