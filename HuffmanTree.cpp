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

void HuffmanTree::assignLeft(Node * src)
{
	this->root->leftNode = src;
}

void HuffmanTree::assignRight(Node * src)
{
	this->root->rightNode = src;
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

void HuffmanTree::print(const Node * node, const int &level)
{
	/*if (node)
	{
		std::cout << node->data << std::endl;

		if (node->leftNode)
		{
			print(node->leftNode, level + 4);
		}

		if (node->rightNode)
		{
			print(node->rightNode, level + 4);
		}

		if (level)
		{
			std::cout << std::setw(level) << ' ';
		}
		
	}*/
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

std::ostream & operator<<(std::ostream & out, const HuffmanTree & src)
{
	/*if (src.root == NULL)
	{
		return out;
	}
	out << *(src.root);
	
	if (src.root->leftNode != NULL)
	{
		out << " " << *(src.root->leftNode);
	}
		
	if (src.root->rightNode != NULL)
	{
		out << " " << *(src.root->rightNode);
	}*/

	out << *(src.root);
	return out;
}
