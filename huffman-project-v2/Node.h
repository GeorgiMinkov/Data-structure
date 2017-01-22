#pragma once
#include "Pair.hpp"

struct Node
{
	Pair<char, std::size_t> data;
	Node *leftNode;
	Node *rightNode;

	Node();
	Node(const Pair<char, std::size_t> data, Node *leftNode, Node *rightNode);

	friend bool operator<(const Node &lhs, const Node &rhs);
	friend bool operator<=(const Node &lhs, const Node &rhs);
	friend bool operator>(const Node &lhs, const Node &rhs);
	friend bool operator>=(const Node &lhs, const Node &rhs);
	friend bool operator==(const Node &lhs, const Node &rhs);
	friend bool operator!=(const Node &lhs, const Node &rhs);

	friend std::ostream &operator<<(std::ostream &out, const Node &src);
};