#include <bits/stdc++.h>
using namespace std;
struct edge
{
    int s, d, w;
};

int bellmanFord(int n, int e, int src, vector<edge> &edges, vector<int> &dist, vector<int> &parent)
{
    int i, j;
    int s, d, w;
    i = src;
    dist[i - 1] = 0;
    parent[i - 1] = -1;
    for (i = 1; i < n; i++)
    {
        for (j = 0; j < e; j++)
        {
            s = edges[j].s;
            d = edges[j].d;
            w = edges[j].w;
            if (dist[s] != INT_MAX && dist[s] + w < dist[d])
            {
                dist[d] = dist[s] + w;
                parent[d] = s;
            }
        }
    }
    // This loop is to detect a negative loop
    for (j = 0; j < e; j++)
    {
        s = edges[j].s;
        d = edges[j].d;
        w = edges[j].w;
        if (dist[s] != INT_MAX && dist[s] + w < dist[d])
        {
            return 0;
        }
    }
    return 1;
}
void printPath(int v, vector<int> &parent)
{
    if (v == -1)
        return;
    printPath(parent[v], parent);
    if (parent[v] != -1)
        cout << " -> ";
    cout << v + 1;
}
int main()
{
    int i;
    int n, e;
    int s, d, w;
    int src;
    cout << "Enter the number of vertices ";
    cin >> n;
    cout << "Enter the number of edges ";
    cin >> e;
    vector<edge> edges(e);
    cout << "Enter the src, dest, and weight of each edge" << endl;
    for (i = 0; i < e; i++)
    {
        cin >> s >> d >> edges[i].w;
        edges[i].s = s - 1; // to adjust 0 based indexing
        edges[i].d = d - 1;
    }
    cout << "Enter the source vertex ";
    cin >> src;
    vector<int> dist(n, INT_MAX);
    vector<int> parent(n, -1);
    i = bellmanFord(n, e, src, edges, dist, parent);
    cout << endl;
    if (i)
    {
        cout << "Vertex Min. Distance Path" << endl;

        for (i = 0; i < n; i++)
        {
            cout << i + 1 << "\t" << dist[i] << "\t";
            printPath(i, parent);
            cout << endl;
        }
    }
    else
    {
        // Negative loop
        cout << "There is a negative weight loop in the graph " << endl;
    }
    return 0;
}