#include "Bellman-FordSP.h"
#include <limits>
#include <algorithm>

BellmanFordSP::BellmanFordSP(const EWDiGraph& graph, int source) : distances(graph.getVertexCount(), std::numeric_limits<double>::max()),
edges(graph.getVertexCount(), Edge(0, 0, 0.0))
{
	std::queue<int> considerVertecies;
	for (int i = 0; i < graph.getVertexCount(); i++)
	{
		considerVertecies.push(i);
	}
	distances[source] = 0.0;
	for (int i = 0; i < graph.getVertexCount(); i++)
	{
		std::queue<int> nextPassVertecies;
		while (!considerVertecies.empty())
		{
			if (i == graph.getVertexCount() - 1)
				findNegativeCycle(considerVertecies.front());
			EWDiGraph::EdgesList adjacent = graph.getAdjacentVertex(considerVertecies.front());
			for (auto k = adjacent.begin(); k != adjacent.end(); ++k)
			{
				relax(*k, nextPassVertecies);
			}
			considerVertecies.pop();
		}
		considerVertecies = nextPassVertecies;
	}
}

void BellmanFordSP::relax(const Edge& e, std::queue<int>& nextPassVertecies)
{
	int v = e.from();
	int w = e.to();
	if (distances[w] > distances[v] + e.getWeight())
	{
		distances[w] = distances[v] + e.getWeight();
		edges[w] = e;
		nextPassVertecies.push(w);
	}
}

double BellmanFordSP::distTo(int v) const
{
	if (!hasPathTo(v))
		return std::numeric_limits<double>::max();
	return distances[v];
}

BellmanFordSP::PathToStack BellmanFordSP::pathTo(int v) const
{
	BellmanFordSP::PathToStack retStack;
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

bool BellmanFordSP::hasPathTo(int v) const
{
	return distances[v] < std::numeric_limits<double>::max();
}

void BellmanFordSP::findNegativeCycle(int v)
{
	if (!hasNegativeCycle())
	{
		std::vector<int> cycleVertecies;
		for (int i = v;; i = edges[i].from())
		{
			auto j = std::find(cycleVertecies.begin(), cycleVertecies.end(), i);
			if (j != cycleVertecies.end())
			{
				for (auto k = j; k != cycleVertecies.end(); ++k)
				{
					negativeCycle.push(*k);
				}
				break;
			}
			cycleVertecies.push_back(i);
		}
	}
}

bool BellmanFordSP::hasNegativeCycle() const
{
	return !negativeCycle.empty();
}

BellmanFordSP::PathToStack BellmanFordSP::getNegativeCycle() const
{
	return negativeCycle;
}