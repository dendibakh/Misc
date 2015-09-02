#pragma once
#include "EWDiGraph.h"
#include <stack>
#include <queue>

class BellmanFordSP
{
        void relax(const Edge& e, std::queue<int>& nextPassVertecies);
        void findNegativeCycle(int v);
public:
        typedef std::stack<int> PathToStack;
        BellmanFordSP(const EWDiGraph& graph, int source);
        int distTo(int v) const;
        PathToStack pathTo(int v) const;
        bool hasPathTo(int v) const;
        bool hasNegativeCycle() const;
        PathToStack getNegativeCycle() const;
private:
        std::vector<int> distances;
        std::vector<Edge> edges;
        PathToStack negativeCycle;
};