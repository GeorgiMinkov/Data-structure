#pragma once
#include "HuffmanTree.h"
#include <string>
#include <queue> // make priority_queue
#include <functional>
#include <algorithm>

struct great;

void lego(std::string src);
void makeTable(std::string src, DynamicTable<char, std::size_t> &table);
void makePriorityQueue(std::priority_queue<Node *, std::vector<Node *>, great> &queue, DynamicTable<char, std::size_t> table);
void makeHuffmanTree(std::priority_queue<Node *, std::vector<Node *>, great> queue, HuffmanTree &tree);
// ENCODING FUNCTION
void encodeSymbols(Node *node, DynamicTable<char, std::string> &table, std::string code);
int binToDec(std::string str);
void transferBitsToDec(std::string code, std::string &res);
void decodeSymbols(std::string code, const Node *node, std::string &res, const Node *startNode);

struct great
{
	bool operator()(const Node *lhs, const Node *rhs)
	{
		return *lhs > *rhs;
	}
};