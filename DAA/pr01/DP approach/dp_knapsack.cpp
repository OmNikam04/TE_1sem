#include<bits/stdc++.h>
using namespace std;
int f(int ind, int W, vector<int>&wt, vector<int>&val){
    if(ind == 0){
        if(wt[0] <= W) return val[0];
        else return 0;
    }
    int not_take = 0 + f(ind-1, W, wt, val);
    int take = INT_MIN;
    if(wt[ind] <= W){
        take =val[ind] + f(ind-1, W-wt[ind], wt, val);
    }
    return max(not_take, take);
}
int knapsack(vector<int> weight, vector<int> value, int n, int maxWeight) 
{
	// Write your code here
    return f(n-1, maxWeight, weight, value);
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
    
    cout<<knapsack(wt,val,n,w);
    return 0;
}