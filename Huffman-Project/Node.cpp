#include "stdafx.h"
#include "Node.h"

Node::Node()
{
	this->data = Pair<char, std::size_t>();
	this->leftNode = NULL;
	this->rightNode = NULL;
}

Node::Node(const Pair<char, std::size_t> & data, Node * leftNode, Node * rightNode)
{
	this->data = data;
	this->leftNode = leftNode;
	this->rightNode = rightNode;
}

bool operator<(const Node & lhs, const Node & rhs)
{
	if (lhs.data.secondArgument < rhs.data.secondArgument)
	{
		return true;
	}
	else if (lhs.data.secondArgument == rhs.data.secondArgument)
	{
		return lhs.data.firstArgument < rhs.data.firstArgument;
	}
	else
	{
		return false;
	}
}

bool operator<=(const Node & lhs, const Node & rhs)
{
	if (lhs.data.secondArgument < rhs.data.secondArgument)
	{
		return true;
	}
	else if (lhs.data.secondArgument == rhs.data.secondArgument)
	{
		return lhs.data.firstArgument <= rhs.data.firstArgument;
	}
	else
	{
		return false;
	}
}

bool operator>(const Node & lhs, const Node & rhs)
{
	return !(lhs <= rhs);
}

bool operator>=(const Node & lhs, const Node & rhs)
{
	return !(lhs < rhs);
}

bool operator==(const Node & lhs, const Node & rhs)
{
	return lhs.data.secondArgument == rhs.data.secondArgument && lhs.data.firstArgument == rhs.data.firstArgument;
}

bool operator!=(const Node & lhs, const Node & rhs)
{
	return !(lhs == rhs);
}

std::ostream & operator<<(std::ostream & out, const Node & src)
{
	if (&src == NULL)
	{
		return out;
	}
	out << src.data << *(src.leftNode) << *(src.rightNode);

	return out;
}
