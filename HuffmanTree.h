#pragma once
#include <iomanip>
#include "Node.h"
#include "DynamicTable.hpp"

class HuffmanTree
{
	Node *root;

	void copy(const Node *sourceRoot, Node *& destinyRoot);
	void destroy(Node *& root);
public:
	HuffmanTree();
	HuffmanTree(Node *&src);
	HuffmanTree(const HuffmanTree &src);
	~HuffmanTree();

	HuffmanTree &operator=(const HuffmanTree &src);

	void assignLeft(Node *src);
	void assignRight(Node *src);

	bool isLeaf(const Node *node) const;
	Node *getRoot() const;
	
	bool containSymbol(const Node *root, const char &symbol) const;

	friend std::ostream &operator<<(std::ostream &out, const HuffmanTree &src);

	void print(const Node *node, const int &level);
};