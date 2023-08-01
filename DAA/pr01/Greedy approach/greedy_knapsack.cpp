#include<bits/stdc++.h>
using namespace std;

int knapsack(vector<int>&wt, vector<int>&val, int n, int maxWeight){
    vector<pair<float, pair<int ,int> >> v;
    for(int i =0; i<n; i++){
        float pw_ratio = (float)val[i] / wt[i];
        v.push_back({pw_ratio, {wt[i], val[i]}});
    }
    sort(v.rbegin(), v.rend());
    cout<<endl;

    int maxProfit = 0;
    vector<int>temp;
    for(auto it: v){
        if(it.second.first <= maxWeight){
            maxProfit += it.second.second;
            maxWeight -= it.second.first;
            temp.push_back(it.second.second);
        }
        // else if(it.second.first > maxWeight){
        //     maxProfit = maxProfit + (it.first * (it.second.first - maxWeight));
        //     maxWeight = it.second.first - maxWeight;
        // }
    }
    cout<<"Selected profits: "<<endl;
    for(auto it: temp){
        cout<<it<<" ";
    }
    cout<<endl;

    return maxProfit;

}

int main(){
    int n;cin>>n;
    int W; cin>>W;
    vector<int>wt, val;
    for(int i =0; i<n; i++){
        int x; cin>>x;
        wt.push_back(x);
    }
    for(int i =0;i<n; i++){
        int x; cin>>x;
        val.push_back(x);
    }

    cout<<knapsack(wt, val, n, W);

    return 0;
}
