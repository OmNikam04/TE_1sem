#include<bits/stdc++.h>
using namespace std;

#define inf INT_MAX

class Node{
public:
    int vertex;
    int cost;
    vector<vector<int>> graph;

    Node(){}

    Node(int v, vector<vector<int>> g){
        this->vertex = v;
        this->graph = g;
    }

    int calCost(int row, int col){
        int n = this->graph.size();
        
        //1: Making entire row and columns of matrix as INF
        for(int i = 0; i<n; i++){
            for(int j = 0; j<n; j++){
                if(row == i || col == j)
                    graph[i][j] = inf;
            }
        }
        // also make the current row and column as inf
        graph[row][col] = inf;

        // Calculating the cost
        int cost = 0;

        // for maintaining the rowArr and colArr
        vector<int> rowArr(n, 0);
        vector<int> colArr(n, 0);

        cout<<"Calculation for vertex: "<<col<<endl;
        cout<<"Minimum row wise: "<<endl;

        // Finding minimum values row wise reduction
        for(int i = 0; i<n; i++){
            int mini = INT_MAX;
            //a. Find the minimum value from graph
            for(int j =0 ;j<n; j++)mini = min(mini, graph[i][j]);

            //If minimum value is infinity then update to 0
            if(mini == inf) mini = 0;

            //b. As we are doing row wise reduction update the rowArr with minimum value found
            rowArr[i] = mini;
            cout<<"Minimum value: "<<mini<<endl;
            
            // Update the cost
            cost += mini;

            //c. Reduce the row based on minimum value found
            for(int j = 0; j<n; j++) 
                if(graph[i][j] != inf && graph[i][j] != 0)
                    graph[i][j] -= mini;

        }

        // Finding minimum values column wise
        cout<<"\nMinimum column wise: ";
        for(int i = 0; i<n; i++){
            int mini = INT_MAX;
            for(int j = 0; j<n; j++){
                mini = min(graph[i][j], mini);
            }

            if(mini == inf) mini = 0;
            cout<<mini<<" ";
            colArr[i] = mini;

            cost += mini;

            for(int j = 0; j<n; j++)
                if(graph[i][j]!=0 && graph[i][j] != inf)
                    graph[i][j] -= mini;
        }


        return cost;
    }
};


int main()
{
     vector<vector<int>> graph =  {
        { inf, 20, 30, 10,11 },
        { 15, inf, 16, 4, 2 },
        { 3, 5, inf, 2, 4 },
        { 19, 6, 18, inf, 3 },
        { 16, 4, 7, 16, inf }
    };


    int n = graph.size();

    // Initialize root node
    Node root(0, graph);

    // calculating the cost for root node
    int totalCost = root.calCost(-1, -1);
    cout<<"Root node cost: "<<totalCost<<endl;

    vector<int>visited(n, 0);
    visited[0] = 1;

    int ct = 1;
    Node last = root;
    vector<int>seq;
    while(ct<n){
        // Find the minimum node which can be exapanded
        int mini = INT_MAX;
        Node miniNode; 
        int Index;
        for(int i = 0; i<n; i++){
            if(visited[i] == 1) continue;

            // Create a node with vertex number and pass parent graph to it
            Node newNode(i, last.graph);

            // Cost calculation= row, col cost + the edge cost from parent to current node
            int cost = newNode.calCost(last.vertex, i) + last.graph[last.vertex][i];

            if(mini > cost){
                mini = cost;
                miniNode = newNode;
                Index = i;
            }

            cout<<"Cost: "<<totalCost+cost;
        }

        // updating the total cost
        totalCost += mini;
        last = miniNode;
        seq.push_back(last.vertex);
        visited[last.vertex] = 1;
        cout<<"Minimum found: "<<totalCost<<endl;
        ct++;
    }

    cout<<"\nThe sequence is: 0 ";
    for(auto it: seq){
        cout<<" -> "<<it;
    }

    cout<<"\n The total cost is: "<<totalCost;
    return 0;
}