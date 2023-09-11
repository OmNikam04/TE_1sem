#include<bits/stdc++.h>
using namespace std;

struct Edge{
  int src, dest, weight;
};

struct Graph{
  int V, E;
  struct Edge edge[];
};

struct *createGraph(int v, int e){
  struct Graph* mygraph = new Graph;

  mygraph->V = v;
  mygraph->E = e;
  mygraph->edge = new Edge[e];

  return mygraph;
}

void BellmanFord(struct Graph* graph, int src){
  // complete function to get bellman ford
}

int main(){
  cout<<"Enter number of vertices of graph: ";
  int v; cin>>v;
  cout<<"Enter number of edges of graph: ";
  int e; cin>>e;

  struct Graph* graph = createGraph(v, e);
  cout<<"Enter input in below format: "<<endl;
  cout<<"Src\tDest\tWeight"<<endl;
  for(int i = 0; i<e; i++){
    cin>>graph->edge[i].src;
    cin>>graph->edge[i].dest;
    cin>>graph->edge[i].weight;
  }

  cout<<"Which vertex is source? : ";
  int srcVertex; cin>>srcVertex;

  BellmanFord(graph, srcVertex);
  return 0;
}
