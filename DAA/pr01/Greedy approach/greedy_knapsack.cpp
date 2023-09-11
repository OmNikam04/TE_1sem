#include <bits/stdc++.h>
using namespace std;

void knapsack(vector<int> &wt, vector<int> &profit, int n, int maxWeight)
{
    vector<pair<float, pair<int, int>>> v;
    // it.first -> profit weight ration
    // it.second.first -> profit
    // it.second.second -> weight
    for (int i = 0; i < n; i++)
    {
        float pw_ratio = (float)profit[i] / wt[i];
        v.push_back({pw_ratio, {profit[i], wt[i]}});
    }

    sort(v.rbegin(), v.rend());

    cout << "*****************Data in descending order of P/W ratio****************" << endl;
    cout << "Profit:\t\t";
    for (auto it : v)
        cout << it.second.first << "\t";
    cout << endl;
    cout << "Weight:\t\t";
    for (auto it : v)
        cout << it.second.second << "\t";
    cout << endl;
    cout << "P/W ratio:\t";
    for (auto it : v)
        cout << it.first << "\t";
    cout << endl;
    cout << "**********************************************************************" << endl;

    double finalProfit = 0;

    cout << "==============knapsack started=================" << endl;
    for (auto it : v)
    {
        if (maxWeight > 0 && it.second.second <= maxWeight)
        {
            cout << "weight taken: " << it.second.second << endl;
            cout << "Profit added: " << it.second.first << endl;
            cout << "-------------------" << endl;
            maxWeight = maxWeight - it.second.second;
            finalProfit = finalProfit + it.second.first;
        }
        // else if (maxWeight > 0 && it.second.second > maxWeight)
        // {
        //     // fraction condition here
        //     // take the ratio of remainining part and then multiply it to remainiing weight
        //     // that will be your newly added profit
        //     cout << "weight taken: " << it.second.second << endl;
        //     double fractionalProfit = it.first * maxWeight;
        //     cout << "fractionalProfit added: " << fractionalProfit << endl;
        //     cout << "-------------------" << endl;
        //     finalProfit += fractionalProfit;
        //     maxWeight = maxWeight - maxWeight;
        // };
    }

    cout << "weight of knapsack became: " << maxWeight << endl;
    cout << "Maximum profit obtained: " << finalProfit << endl;
}

int main()
{
    cout << "Enter number of items in knapsack: ";
    int n;
    cin >> n;
    cout << "Enter maximum capacity of knapsack: ";
    int W;
    cin >> W;
    vector<int> wt, profit;
    
    cout<<"Enter profits:\t";
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        profit.push_back(x);
    }
    cout<<endl;
    cout<<"Enter weights:\t";
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        wt.push_back(x);
    }
    cout<<endl;
    cout << "*******************Given data*******************" << endl;
    cout << "Profit:\t\t";
    for (auto it : profit)
        cout << it << "\t";
    cout << endl;
    cout << "Weight:\t\t";
    for (auto it : wt)
        cout << it << "\t";
    cout<<endl;
    cout << "***********************************************" << endl;
    cout << endl;

    cout << "Calling knapsack to maximize the profit...." << endl
         << endl;
    knapsack(wt, profit, n, W);

    return 0;
}
