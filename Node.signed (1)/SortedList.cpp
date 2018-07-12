#include <iostream>
#include <iterator>
#include "SortedList.h"

using namespace std;

/**
 * Defaut constructor.
 * Reset the global Node counters.
 */
SortedList::SortedList()
{
    Node::reset();
}

/**
 * Destructor.
 * Reset the global Node counters.
 */
SortedList::~SortedList()
{
    Node::reset();
}

/**
 * @return the size of the data list.
 */
int SortedList::size() const { return data.size(); }

/**
 * Check that the data is sorted.
 * @return true if sorted, false if not.
 */
bool SortedList::check()
{
    if (data.size() == 0) return true;

    list<Node>::iterator it = data.begin();
    list<Node>::iterator prev = it;

    it++;

    // Ensure that each node is greater than the previous node.
    while ((it != data.end()) && (*it >= *prev))
    {
        prev = it;
        it++;
    }

    return it == data.end();  // Good if reached the end.
}

/**
 * Insert a new node at the beginning of the data list.
 * @param value the new node's value.
 */
void SortedList::prepend(const long value)
{
    /***** Complete this function. *****/
	data.push_back(Node(value));
}

/**
 * Append a new node at the end of the data list.
 * @param value the new node's value.
 */
void SortedList::append(const long value)
{
    /***** Complete this function. *****/
	data.push_back(Node(value));
}

/**
 * Remove a node.
 * @param index the index of the node to remove.
 */
void SortedList::remove(const int index)
{
    /***** Complete this function. *****/
	list<Node>::iterator it = data.begin();
	for(int i =0; i< index && it != data.end(); i++)
	{
		it++;
	}
	if(it!= data.end())
	data.erase(it);
}

/**
 * Insert a new node into the data list at the
 * appropriate position to keep the list sorted.
 */
void SortedList::insert(const long value)
{
    /***** Complete this function. *****/
	Node cur_node(value);
		if (data.empty())
		{
			data.push_back(cur_node);
			return;
		}
		list<Node>::iterator it; //iterator for the node class
		it = data.begin(); //iterator for the data , present instant
		while(it!= data.end() && cur_node > *it)
		{
			it++;
		}
		if(it == data.end())
		{
			data.push_back(cur_node);
		}
		else
		{
			data.insert(it, cur_node);
		}
}

/**
 * Return the data node at the indexed position.
 * @param the index of the node.
 * @return a copy of the data node.
 */
Node SortedList::at(const int index)
{
    /***** Complete this function. *****/
	//Node n;
	if (index < data.size()/2)
	{
		list<Node>::iterator it = data.begin();
		for(int i =0; i< index && it!= data.end(); i++)
		{
			it++;
		}
		if (it!= data.end())
			return *it;
	}
	else
	{
		list<Node>::reverse_iterator itr = data.rbegin();
		for(int i =0; i < (data.size()-index-1) && itr!= data.rend(); i++)
		{
			itr++;
		}
		if (itr!= data.rend())
			return *itr;
	}

}


