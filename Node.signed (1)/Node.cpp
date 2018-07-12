#include <iostream>
#include "Node.h"

using namespace std;

// Static member variables, which are global to the class.
// These variables exist independently from any Node objects.
long Node::constructor_count;
long Node::copy_count;
long Node::destructor_count;

/***** Complete this file. *****/
//ctor
Node::Node()
{
	Node::constructor_count++;
}
Node::Node(const Node& other)
{
	m_value = other.m_value;
	Node::copy_count++;
}

Node::Node(const long the_value)
{
	m_value = the_value;
	Node::constructor_count++;
}

//dtor
Node::~Node()
{
	Node::destructor_count++;
}
//getter
long Node::get_value() const
{
	return m_value;
}
long Node::get_constructor_count()
{
	return Node::constructor_count;
}
long Node::get_copy_count()
{
	return Node::copy_count;
}
long Node::get_destructor_count()
{
	return Node::destructor_count;
}
bool Node::operator <(const Node & other_obj) const
{
	return this->m_value < other_obj.m_value;
}

bool Node::operator >(const Node & other_obj) const
{
	return this->m_value > other_obj.m_value;
}
bool Node::operator >=(const Node & other_obj) const
{
	return this->m_value >= other_obj.m_value;
}


void Node::set_value(const long  the_value)
{
	m_value = the_value;
}

bool Node::operator ==(const Node & other_node) const
{
	return m_value == other_node.m_value;
}

void Node::reset()
{
	Node::copy_count = 0;
	Node::destructor_count = 0;
	Node::constructor_count = 0;
}
