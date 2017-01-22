#include "stdafx.h"
#include "HuffmanTree.h"

void HuffmanTree::copy(const Node * sourceRoot, Node *& destinyRoot)
{
	if (!sourceRoot)
	{
		return;
	}

	destinyRoot = new Node(sourceRoot->data, sourceRoot->leftNode, sourceRoot->rightNode);

	this->copy(sourceRoot->leftNode, destinyRoot->leftNode);
	this->copy(sourceRoot->rightNode, destinyRoot->rightNode);
}

void HuffmanTree::destroy(Node *& root)
{
	if (!root)
	{
		return;
	}

	this->destroy(root->leftNode);
	this->destroy(root->rightNode);

	delete root;

	root = NULL;
}

void HuffmanTree::loadTreeFromFile(Node *& root, std::ifstream & fi)
{
	Pair<char, std::size_t> pair;
	bool isPair = false;

	if (this->getElement(fi, pair, isPair))
	{
		root = new Node(pair, NULL, NULL);

		this->loadTreeFromFile(root->leftNode, fi);
		this->loadTreeFromFile(root->rightNode, fi);
	}
	else
	{
		return;
	}
	
}

bool HuffmanTree::getElement(std::ifstream & fi, Pair<char, std::size_t> &pair, bool &isPair)
{
	bool isNode = false;

	char symbol = fi.peek();

	// if reach end of file
	if (fi.eof())
	{
		return isNode;
	}

	// skip spaces
	while ((symbol = fi.get()) == char(247)) 
	{
		if (fi.eof())
		{
			return isNode;
		}
	}

	std::size_t number = 0;

	if (symbol != char(248))
	{
		pair.firstArgument = symbol;

		std::string str = "";
		while ((str = fi.get()) == std::to_string(char(247))) { }
		while ((symbol = fi.get()) != char(247))
		{
			str += symbol;
		}

		pair.secondArgument = std::stoi(str);
	
		isPair = true;
		isNode = true;
	}
	else
	{
		fi.ignore();
	}
	 
	return isNode;
}

HuffmanTree::HuffmanTree()
{
	this->root = NULL;
}

HuffmanTree::HuffmanTree(Node *& src)
{
	this->copy(src, this->root);
}

HuffmanTree::HuffmanTree(const HuffmanTree & src)
{
	this->copy(src.root, this->root);
}

HuffmanTree::~HuffmanTree()
{
	this->destroy(this->root);
}

HuffmanTree & HuffmanTree::operator=(const HuffmanTree & src)
{
	// DO: operator=
	if (this != &src)
	{
		this->destroy(this->root);
		
		this->copy(src.root, this->root);
	}

	return *this;
}

bool HuffmanTree::isLeaf(const Node *node) const
{
	return (node->leftNode == NULL && node->rightNode == NULL);
}

Node * HuffmanTree::getRoot() const
{
	return this->root;
}

bool HuffmanTree::containSymbol(const Node *root, const char &symbol) const
{
	if (!root)
	{
		return false;
	}

	if (isLeaf(root) && (root->data.firstArgument == symbol))
	{
		return true;
	}
	else
	{
		if (this->containSymbol(root->leftNode, symbol))
		{
			return true;
		}
		else
		{
			return this->containSymbol(root->rightNode, symbol);
		}
	}
}

void HuffmanTree::print(const Node * node, const std::size_t &level)
{
	if (node)
	{
		if (node->rightNode)
		{
			print(node->rightNode, level + 4);
		}

		if (level)
		{
			std::cout << std::setw(level) << ' ';
		}

		if (node->rightNode)
		{
			std::cout << " /\n" << std::setw(level) << ' ';
		}

		std::cout << node->data << std::endl;
		
		if (node->leftNode)
		{
			std::cout << std::setw(level) << ' ' << " \\\n";
			print(node->leftNode, level + 4);
		}

	}
}

void HuffmanTree::saveInFile(Node * root, std::ostream & fo)
{
	if (!root)
	{
		fo << char(248) << char(247);
	}
	else
	{
		fo << root->data << char(247);

		this->saveInFile(root->leftNode, fo);
		this->saveInFile(root->rightNode, fo);
	}
}

void HuffmanTree::loadTreeFromFile(std::ifstream & fi)
{
	this->loadTreeFromFile(this->root, fi);
}

std::ostream & operator<<(std::ostream & out, const HuffmanTree & src)
{
	out << *(src.root);
	return out;
}
