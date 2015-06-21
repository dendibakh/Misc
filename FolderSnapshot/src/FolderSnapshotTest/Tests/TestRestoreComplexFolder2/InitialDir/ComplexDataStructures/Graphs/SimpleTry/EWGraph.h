#pragma once

#include <vector>
#include <list>
#include <map>

class EWGraph
{
   /*struct Vertex
   {
      int ID;
   };*/

   struct Edge
   {
      int from;
      int to;
      int weight;
   };

   void dfs(int src, std::vector<bool>& marked);
public:
   EWGraph();
   ~EWGraph();

   void insertVertex(int ID);
   void insertEdge(int from, int to, int weight);
   void dfs(int src);
private:
   typedef std::map<int, std::list<Edge>> Storage;
   typedef Storage::iterator StorageIter;
   Storage storage;
};