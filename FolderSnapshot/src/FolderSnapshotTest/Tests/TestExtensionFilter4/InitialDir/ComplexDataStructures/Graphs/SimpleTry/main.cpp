#include "EWGraph.h"

static const int A = 1;
static const int B = 2;
static const int C = 3;
static const int D = 4;

int main()
{
   EWGraph graph;
   graph.insertVertex(A);
   graph.insertVertex(B);
   graph.insertVertex(C);
   graph.insertVertex(D);
   graph.insertEdge(A, B, 7);
   graph.insertEdge(B, C, 2);
   graph.insertEdge(A, D, 3);
   graph.insertEdge(B, D, 5);
   graph.insertEdge(D, C, 9);
   graph.dfs(A);
}