#include "EWGraph.h"

EWGraph::EWGraph()
{

}

EWGraph::~EWGraph()
{

}

void EWGraph::insertVertex(int ID)
{
   StorageIter iter = storage.find(ID);
   if (iter == storage.end())
   {
      std::list<Edge> edges;
      storage.insert(std::make_pair(ID, edges));
   }
}

void EWGraph::insertEdge(int from, int to, int weight)
{
   StorageIter iter = storage.find(from);
   if (iter == storage.end())
      throw 0;
   Edge e;
   e.from = from;
   e.to = to;
   e.weight = weight;
   iter->second.push_back(e);
   insertEdge(to, from, weight);
}

void EWGraph::dfs(int src, std::vector<bool>& marked)
{
   marked[src] = true;
   
   StorageIter iter = storage.find(src);
   if (iter == storage.end())
      throw 0;

   for (std::list<Edge>::iterator listIter = iter->second.begin(); listIter != iter->second.begin(); ++listIter)
   {
      if (!marked[listIter->to])
         dfs(src, marked);
   }
}

void EWGraph::dfs(int src)
{
   std::vector<bool> marked(storage.size(), false);
   dfs(src, marked);
}