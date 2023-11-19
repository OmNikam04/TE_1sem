#include <bits/stdc++.h>
using namespace std;

struct Edge
{
    int s, d, w;
};

int bellman_ford(int V, int E, int src, vector<Edge>& edges, vector<int> &parent, vector<int> &dist)
{
    // make sorce parent -1 and dist 0
    dist[src - 1] = 0;
    parent[src - 1] = -1;

    int curr_src;
    int curr_dest;
    int curr_w;

    // relax v-1 times each edge
    for (int i = 1; i < V; i++)
    {
        for (int j = 0; j < E; j++)
        {
            curr_src = edges[j].s;
            curr_dest = edges[j].d;
            curr_w = edges[j].w;
            if (dist[curr_src] != INT_MAX && (dist[curr_src] + curr_w) < dist[curr_dest])
            {
                // then update the dist of source
                dist[curr_dest] = dist[curr_src] + curr_w;
                parent[curr_dest] = curr_src;
            }
        }
    }

    // To detect negative cycle in graph
    for (int j = 0; j < E; j++)
    {
        curr_src = edges[j].s;
        curr_dest = edges[j].d;
        curr_w = edges[j].w;
        if (dist[curr_src] != INT_MAX && (dist[curr_src] + curr_w ) < dist[curr_dest])
        {
            return 0;
        }
    }

    return 1;
}

void printPath(int v, vector<int>&parent){
    if(v == -1)
        return;
    
    printPath(parent[v], parent);

    if(parent[v] != -1)
        cout<<" -> ";
    cout<<v+1;
}
int main()
{
    int v, e;
    cout << "Enter number of vertexes: ";
    cin >> v;
    cout << "Enter number of edges: ";
    cin >> e;

    int s, d;
    vector<Edge>edges(e);
    cout << "Enter src, destination, and weight: " << endl;
    for (int i = 0; i < e; i++)
    {
        cin >> s >> d >> edges[i].w;
        edges[i].s = s - 1;
        edges[i].d = d - 1;
    }

    int src;
    cout << "Enter the source of traversal: ";
    cin >> src;

    // creating dist vector to store the distance with INT_MAX
    vector<int> dist(v, INT_MAX);
    // parent vector to store parents to each vertex
    vector<int> parent(v, -1);
    int ans = bellman_ford(v, e, src, edges, dist, parent);
    cout<<endl;
    if(ans){
        cout<<"Vertex\tMin. Distance\tPath"<<endl;
        for(int i = 0; i<v; i++){
            cout<<i+1<<"\t"<<dist[i]<<"\t";
            printPath(i, parent);
            cout<<endl;
        }
    }
    else{
        cout<<"Negative cycle detected in graph"<<endl;
    }
    return 0;
}