#pragma once
#include <list>

using namespace std;

class ListAndIter
{
   private:
      std::list<int>::iterator iter;
      static std::list<int> &getList();
   public:
      void foo();
      ListAndIter();
      ListAndIter(ListAndIter& rhs);
      ~ListAndIter();      
};