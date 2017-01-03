#include "stdafx.h"
#include "Algorythm.h"

void lego(std::string src)
{
	// TODO: make from string table !!!!
	DynamicTable<char, std::size_t> table;
	makeTable(src, table);

	// make pr queue
	std::priority_queue<Node *, std::vector<Node*>, great> queue;
	makePriorityQueue(queue, table);

	// make tree
	HuffmanTree tree;
	makeHuffmanTree(queue, tree);

	std::cout << "TREE: ";
	std::cout << tree << std::endl;

	DynamicTable<char, std::string> encodeTable;
	encodeTable.putCharsAndBlank();
	std::string str = "";

	encodeSymbols(tree.getRoot(), encodeTable, str);

	// encodeTable.deleteNullStr();
	std::cout << "CODE: ";
	std::string tmp = "", res = tmp;
	for (std::size_t index = 0; index < src.length(); ++index)
	{
		tmp += encodeTable[(int)src[index]].secondArgument;
	}

	std::cout << std::endl << tmp << std::endl;

	transferBitsToDec(tmp, res);

	std::cout << "DEC CODE: " << res << std::endl;

	std::cout << "\nCHAR CODE: \n";
	encodeTable.deleteNullStr();
	for (std::size_t index = 0; index < encodeTable.getSize(); ++index)
	{
		std::cout << encodeTable[index] << std::endl;
	}

	res = "";

	decodeSymbols(tmp, tree.getRoot(), res, tree.getRoot());

	std::cout << res << std::endl;

	tree.print(tree.getRoot(), 0);
}

void makeTable(std::string src, DynamicTable<char, std::size_t> &table)
{
	table.putCharsAndZeros();

	for (std::size_t index = 0; index < src.length(); ++index)
	{
		table[(int)src[index]].secondArgument++;
	}
}

void makePriorityQueue(std::priority_queue<Node *, std::vector<Node*>, great> &queue, DynamicTable<char, std::size_t> table)
{
	table.deleteZeros();

	for (std::size_t index = 0; index < table.getSize(); ++index)
	{
		Node *tmp = new Node(table[index], NULL, NULL);

		queue.push(tmp);
	}
}

void makeHuffmanTree(std::priority_queue<Node *, std::vector<Node*>, great> queue, HuffmanTree &tree)
{
	Node *root;

	while (queue.size() != 1)
	{
		Node *firstSmall, *secondSmall;

		firstSmall = queue.top();
		queue.pop();

		secondSmall = queue.top();
		queue.pop();

		Node *newElement = new Node(Pair<char, std::size_t>('+', (firstSmall->data.secondArgument + secondSmall->data.secondArgument)), 
			firstSmall, secondSmall);

		queue.push(newElement);
	}

	root = queue.top();
	queue.pop();

	tree = HuffmanTree(root);
}

void encodeSymbols(Node *node, DynamicTable<char, std::string>& table, std::string code)
{
	if (!node->leftNode && !node->rightNode)
	{
		table[(int)(node->data.firstArgument)].secondArgument = code;
	}
	else
	{
		if (node->leftNode)
		{
			std::string str = code + '0';

			encodeSymbols(node->leftNode, table, str);
		}

		if (node->rightNode)
		{
			std::string str = code + '1';

			encodeSymbols(node->rightNode, table, str);
		}
	}
}

int binToDec(std::string str)
{
	const int TWO = 2, SIZE = str.length();
	int res = 0;

	for (std::size_t index = 0; index < SIZE; ++index)
	{
		res += (str[index] == '1' ? pow(TWO, SIZE - index - 1) : 0);
	}

	return res;
}

void transferBitsToDec(std::string code, std::string &res)
{
	if (code.length() < 8)
	{
		res += std::to_string(binToDec(code));
	}
	else
	{
		res += std::to_string(binToDec(code.substr(0, 8)));
		res += " ";

		transferBitsToDec(code.substr(8), res);
	}
}

void decodeSymbols(std::string code, const Node * node, std::string & res, const Node *startNode)
{
	if (!node->leftNode && !node->rightNode )
	{
		if (code == "")
		{
			res += node->data.firstArgument;
			return;
		}
		else
		{
			res += node->data.firstArgument;
			decodeSymbols(code, startNode, res, startNode);
			return;
		}
	}

	if (code == "")
	{
		return;
	}
	else
	{
		if (code[0] == '0')
		{
			decodeSymbols(code.substr(1), node->leftNode, res, startNode);
			return;
		}
		else
		{
			decodeSymbols(code.substr(1), node->rightNode, res, startNode);
			return;
		}
	}
}