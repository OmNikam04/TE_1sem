#include <bits/stdc++.h> 
using namespace std;

int temp[102][1002];

void showSelectedItems(int items, int capacity, vector<int>& wt){
    int i = items;
    int j = capacity;
    while(i>0 && j>0){
        if(temp[i][j]==temp[i-1][j]){
            cout<<i<<" = 0"<<endl;
            i--;
        }
        else{
            cout<<i<<" = 1"<<endl;
            j = j-wt[i];
            i--;
        }
    }
}

void knapsack(vector<int> weight, vector<int> value, int n, int maxWeight) 
{
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= maxWeight; j++) {
            if (i == 0 || j == 0) {
                temp[i][j] = 0;
            }
        }
    }

    for (int i = 1; i < n + 1; i++) {
        for (int j = 1; j < maxWeight + 1; j++) {
            if (weight[i - 1] <= j) {
                temp[i][j] = max(value[i - 1] + temp[i - 1][j - weight[i - 1]], temp[i - 1][j]);
            }
            else {
                temp[i][j] = temp[i - 1][j];
            }
        }
    }

    for(int i =0 ;i <= n; i++){
        for(int w= 0; w<= maxWeight; w++){
            cout<<temp[i][w]<<" ";
        }cout<<endl;
    }
    cout<<endl;

    showSelectedItems(n, maxWeight, weight);
}

int main() {
    int n;
    cout << "Enter the number of items: ";
    cin >> n;

    vector<int> weight(n);
    vector<int> value(n);

    cout << "Enter the weight of each item:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> weight[i] ;
    }
    cout << "Enter the value of each item:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> value[i] ;
    }
    int maxWeight;
    cout << "Enter the maximum weight the knapsack can hold: ";
    cin >> maxWeight;

    knapsack(weight, value, n, maxWeight);

    // cout << "The maximum value that can be obtained is: " << maxVal << endl;

    return 0;
}
