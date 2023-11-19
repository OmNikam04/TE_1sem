#include<bits/stdc++.h>
using namespace std;

struct Item{
    float profit;
    float weight;
    float pw_ratio;
};


void printKnapsack(Item items[], int n){
    cout<<"--------------printing-----------------"<<endl;
    for(int i = 0; i<n; i++){
        cout<<items[i].profit<<" ";
        cout<<items[i].weight<<" ";
        cout<<items[i].pw_ratio<<endl;
    }
    cout<<endl;
}


void merge(Item items[], int start, int mid, int end){
    int lSize = mid - start + 1;
    int rSize = end - mid;

    Item lArr[lSize];
    Item rArr[rSize];

    // fill up these left and right array
    for(int i = 0; i<lSize; i++) lArr[i] = items[i+start];
    for(int i = 0; i<rSize; i++) rArr[i] = items[i+mid+1];

    int i = 0, j = 0, k = start;

    while(i<lSize && j<rSize){
        if(lArr[i].pw_ratio > rArr[j].pw_ratio)
            items[k++] = lArr[i++];
        else
            items[k++] = rArr[j++];
    }

    while(i<lSize) items[k++] = lArr[i++];
    while(j<rSize) items[k++] = rArr[j++];
}

void merge_sort(Item items[], int low, int high){
    if(low>=high) return;

    int mid = (high+low)/2;

    merge_sort(items, low, mid);
    merge_sort(items, mid+1, high);
    merge(items, low, mid, high);
}

void knapsack(Item items[], int maxWeight, int n){
    float maxProfit = 0;
    
    for(int i = 0; i<n; i++){
        if(maxWeight>0 && items[i].weight <= maxWeight){
            // reduce the maxWeight as we are taking the i'th item
            maxWeight = maxWeight - items[i].weight;
            maxProfit = maxProfit + items[i].profit;
        }
        else if(maxWeight > 0 && items[i].weight > maxWeight){
            // fraction condition
            float fractionalProfit = items[i].pw_ratio * maxWeight;
            maxWeight = 0;
            maxProfit += fractionalProfit;
            break;
        }
    }

    cout<<"Weight of knapsack became: "<<maxWeight<<endl;
    cout<<"Maximum profit obtained: "<<maxProfit<<endl;
}



int main(){
    int n, capacity;
    cout<<"Enter number of Items: ";
    cin>>n;
    cout<<"Enter capacity of knapsack: ";
    cin>>capacity;

    Item items[n];

    cout<<"Enter weight of each items: "<<endl;
    for(int i = 0; i<n; i++){
        float w;
        cin>>w;
        items[i].weight = w;
    }
    cout<<"Enter profit of each items: "<<endl;
    for(int i = 0; i<n; i++){
        float p;cin>>p;
        items[i].profit = p;
        items[i].pw_ratio = (items[i].profit / items[i].weight);
    }

    // sort the knapsack based on profit weight ration
    merge_sort(items, 0, n-1);
    printKnapsack(items, n);
    // compute the max profit
    knapsack(items, capacity, n);

    // for(int i = 0; i<n; i++){
    //     cout<<items[i].profit<<" ";
    //     cout<<items[i].weight<<" ";
    //     cout<<items[i].pw_ratio<<endl;
    // }
    return 0;
}