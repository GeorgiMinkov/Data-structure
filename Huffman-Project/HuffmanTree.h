#pragma once
#include <iomanip>
#include <fstream>
#include <string>
#include "Node.h"
#include "DynamicTable.hpp"

class HuffmanTree
{
	Node *root;

	void copy(const Node *sourceRoot, Node *& destinyRoot);
	void destroy(Node *& root);

	void loadTreeFromFile(Node *&root, std::ifstream &fi);
	bool getElement(std::ifstream &fi, Pair<char, std::size_t> &pair, bool &isPair);
public:
	HuffmanTree();
	HuffmanTree(Node *&src);
	HuffmanTree(const HuffmanTree &src);
	~HuffmanTree();

	HuffmanTree &operator=(const HuffmanTree &src);

	bool isLeaf(const Node *node) const;
	Node *getRoot() const;
	
	bool containSymbol(const Node *root, const char &symbol) const;

	friend std::ostream &operator<<(std::ostream &out, const HuffmanTree &src);

	void print(const Node *node, const std::size_t &level);

	void saveInFile(Node *root, std::ostream &fo);
	void loadTreeFromFile(std::ifstream &fi);
};