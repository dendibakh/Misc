#include "ListAndIter.h"

ListAndIter::ListAndIter()
{
    getList().push_front(0);
    iter = getList().begin();
}

ListAndIter::ListAndIter(ListAndIter& rhs)
{
	this->iter = rhs.iter;
	rhs.iter = getList().end();
}

std::list<int> & ListAndIter::getList()
{
	static std::list<int> MyList;
	return MyList;
}

ListAndIter::~ListAndIter()
{
	if (iter != getList().end())
       getList().erase(iter);
}

void ListAndIter::foo()
{

}