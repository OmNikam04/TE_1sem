#include<bits/stdc++.h>
using namespace std;

int knapsack(vector<int>& wt, vector<int>& val, int n, int maxWeight) 
{
	// Write your code here
    int profit = 0;
    for(int i=0; i<n; i++){
        if(wt[i] <= maxWeight){
            profit = profit + val[i];
        }
    }
}

int main()
{
    int n;cin>>n;
    int w; cin>>w;

    vector<int>wt, val;
    for (int i = 0; i < n; i++)
    {
        int x;cin>>x;
        wt.push_back(x);
    }

    for (int i = 0; i < n; i++)
    {
        int x;cin>>x;
        val.push_back(x);
    }
    
    knapsack(wt,val,n,w);
         
    return 0;
}