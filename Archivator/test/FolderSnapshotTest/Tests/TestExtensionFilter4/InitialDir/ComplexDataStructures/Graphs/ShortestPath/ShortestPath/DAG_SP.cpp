#include "DAG_SP.h"
#include "TopologicalSort.h"
#include <limits>

using namespace TpgSort;

DAG_SP::DAG_SP(const EWDiGraph& graph, int source) : distances(graph.getVertexCount(), std::numeric_limits<double>::max()),
edges(graph.getVertexCount(), Edge(0, 0, 0.0))
{
	distances[source] = 0.0;
	TopologicalSort tpgSort(graph);
	TopologicalSort::PostOrderContainer revPostOrder = tpgSort.getPostOrder();
	while (!revPostOrder.empty())
	{
		EWDiGraph::EdgesList adjacent = graph.getAdjacentVertex(revPostOrder.top());
		for (auto i = adjacent.begin(); i != adjacent.end(); ++i)
		{
			relax(*i);
		}
		revPostOrder.pop();
	}
}

void DAG_SP::relax(const Edge& e)
{
	int v = e.from();
	int w = e.to();
	if (distances[w] > distances[v] + e.getWeight())
	{
		distances[w] = distances[v] + e.getWeight();
		edges[w] = e;
	}
}

double DAG_SP::distTo(int v) const
{
	if (!hasPathTo(v))
		return std::numeric_limits<double>::max();
	return distances[v];
}

DAG_SP::PathToStack DAG_SP::pathTo(int v) const
{
	DAG_SP::PathToStack retStack;
	if (!hasPathTo(v))
		return retStack;
	int i = v;
	for (; edges[i].getWeight() != 0.0; i = edges[i].from())
	{
		retStack.push(i);
	}
	retStack.push(i);
	return retStack;
}

bool DAG_SP::hasPathTo(int v) const
{
	return distances[v] < std::numeric_limits<double>::max();
}