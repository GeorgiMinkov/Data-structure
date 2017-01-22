#include "stdafx.h"
#include "Algorythm.h"

void menu()
{
	std::cout << "Huffman algorythm project\n\n";

	char symbol = ' ';

	do
	{
		std::cout << "Choose program:\n";
		std::cout << "1) Input text from command line\n";
		std::cout << "2) Input text from file\n";
		std::cout << "3) Decode from file with encoded data and saved tree\n";
		std::cout << "4) Exit\n";

		std::cout << "\nEnter symbol: ";
		std::cin >> symbol;
	} while (symbol != '1' && symbol != '2' && symbol != '3' && symbol != '4');

	switch (symbol)
	{
	case '1':
	{
		system("CLS");

		std::string str = "";

		std::cout << "Enter text for encode: ";
		std::cin.ignore();
		getline(std::cin, str);

		startArchive(str);
	} break;
	case '2':
	{
		std::string fileName = "", str = "";

		std::cout << "Enter file name: ";
		std::cin >> fileName;
		
		readFileInputData(fileName, str);

		startArchive(str);
	} break;
	case '3':
	{
		std::string fileName = "", decodedInfoFile = "", res = "";;
		std::cout << "Enter file name: ";
		std::cin >> fileName;

		decodeSymbolsFromFile(fileName, decodedInfoFile);
		std::cout << "Binary code is : " << decodedInfoFile << std::endl;

		HuffmanTree tree;

		std::cout << "Enter tree file name: ";
		std::cin >> fileName;

		std::ifstream fi(fileName.c_str(), std::ios::in);

		if (!fi.is_open())
		{
			std::cout << "Error loading file\n";
			return; 
		}

		tree.loadTreeFromFile(fi);

		decodeSymbols(decodedInfoFile, tree.getRoot(), res, tree.getRoot()); // In binStr are loaded bits, result is saved to res

		std::cout << "Original text:\n" << res << std::endl;

		std::cout << "Compression rate: " << 100 * decodedInfoFile.length() / (res.length() * 8) << '%' << std::endl;

		// Print tree
		do
		{
			std::cout << "\n\nDo you want to see graphical tree? (y/n) : ";
			std::cin >> symbol;
		} while (symbol != 'y' && symbol != 'n');

		if (symbol == 'y')
		{
			tree.print(tree.getRoot(), 0);
		}
	} break;
	default:
		break;
	}
}

void mainProgram()
{
	menu();
}

void startArchive(const std::string & src)
{
	DynamicTable<char, std::size_t> table;
	makeTable(src, table);

	// make minimum heap
	MinHeap<Node *> heap;
	makeMinimumHeap(heap, table);


	// make huffman tree
	HuffmanTree tree;
	makeHuffmanTree(heap, tree);

	// Write to each symbol what code is to it Напиши на всяка буква каква кодировка и принадлежи
	DynamicTable<char, std::string> encodeTable;
	encodeTable.putCharsAndBlank();

	std::string strTmp = "";

	encodeSymbols(tree.getRoot(), encodeTable, strTmp);

	// Show binary code of input text
	std::string binStr = "", res = binStr, fileName = ""; // binStr will hold binary code, res will be use for convert bin to dec

	for (std::size_t index = 0; index < src.length(); ++index)
	{
		binStr += encodeTable[(int)src[index]].secondArgument; // write every converted symbol in needed order
	}

	std::cout << "\nCode: " << binStr << std::endl;

	std::size_t lastSizeNumber = 0; // to save how big is last binary number after whipping into 8-bits
	transferBitsToDec(binStr, res, lastSizeNumber);

	std::cout << "DEC CODE: " << res << std::endl;

	archive(lastSizeNumber, res, fileName); // archive decimal in file a.k.a make file arhive

	res = "";

	// Decode information binary + huffman tree = readeble text Декодирай информацията
	decodeSymbols(binStr, tree.getRoot(), res, tree.getRoot()); // In binStr are loaded bits, result is saved to res

	std::cout << "\nOriginal text:\n" << res << std::endl;

	std::cout << "\nCompression rate: " << 100 * binStr.length() / (res.length() * 8) << '%' << std::endl;


	char symbol = ' ';
	do
	{
		std::cout << "\n\nDo you want to save tree in file? (y/n) : ";
		std::cin >> symbol;
	} while (symbol != 'y' && symbol != 'n');

	if (symbol == 'y')
	{
		std::string fileTreeName = "huffmanTree.txt";

		std::ofstream fo(fileTreeName.c_str(), std::ios::out | std::ios::trunc);

		if (!fo.is_open())
		{
			std::cout << "Error open file\n";
		}
		else
		{
			tree.saveInFile(tree.getRoot(), fo);
		}

		fo.close();
	}
	

	// Print tree
	do
	{
		std::cout << "\n\nDo you want to see graphical tree? (y/n) : ";
		std::cin >> symbol;
	} while (symbol != 'y' && symbol != 'n');

	if (symbol == 'y')
	{
		tree.print(tree.getRoot(), 0);
	}

}

void makeTable(std::string src, DynamicTable<char, std::size_t> &table)
{
	table.putCharsAndZeros();

	for (std::size_t index = 0; index < src.length(); ++index)
	{
		table[(int)src[index]].secondArgument++;
	}
}

void makeMinimumHeap(MinHeap<Node*>& heap, DynamicTable<char, std::size_t> table)
{
	table.deleteZeros();

	for (std::size_t index = 0; index < table.getSize(); ++index)
	{
		Node *tmp = new Node(table[index], NULL, NULL);

		heap.push(tmp);
	}
}

void makeHuffmanTree(MinHeap<Node*> heap, HuffmanTree & tree)
{
	Node *root;

	while (heap.size() != 1)
	{
		Node *firstSmall, *secondSmall;

		firstSmall = heap.top();
		heap.pop();

		secondSmall = heap.top();
		heap.pop();

		Node *newElement = new Node(Pair<char, std::size_t>(char(254), (firstSmall->data.secondArgument + secondSmall->data.secondArgument)),
			firstSmall, secondSmall);

		heap.push(*&newElement);
	}

	root = heap.top();
	heap.pop();

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

void readFileInputData(const std::string & fileName, std::string &str)
{
	std::ifstream fi(fileName.c_str(), std::ios::in);

	if (!fi.is_open())
	{
		std::cout << "Cannot open file\n";
	}
	else
	{
		std::string line = "";
		bool firtsInput = true;

		while (getline(fi, line))
		{
			if (firtsInput)
			{
				str += line;
				firtsInput = false;
			}
			else
			{
				str += '\n' + line;
			}
		}
	}

	fi.close();
}

void archive(const std::size_t &lastNumberSize, std::string decStr, std::string &fileName)
{
	fileName = __FUNCTION__;
	fileName += ".txt";

	std::ofstream fo(fileName.c_str(), std::ios::out | std::ios::trunc);

	if (fo.is_open())
	{
		fo << decStr << ' ' << char(253) << ' ' << lastNumberSize;
	}
	else
	{
		std::cout << "Cannot open file\n";
	}

	fo.close();
}

std::string decToBin(int number)
{
	std::string res = "";

	if (number)
	{
		while (number != 1)
		{
			res += std::to_string(number % 2);
			number /= 2;
		}
	}

	res += std::to_string(number);

	std::reverse(res.begin(), res.end());
	
	return res;
}

void transferBitsToDec(std::string code, std::string &res, std::size_t &lastSizeNumber)
{
	if (code.length() <= 8)
	{
		lastSizeNumber = (code.length() == 8) ? 0 : code.length();

		res += std::to_string(binToDec(code));

		return;
	}
	else 
	{
		res += std::to_string(binToDec(code.substr(0, 8)));
		res += " ";

		transferBitsToDec(code.substr(8), res, lastSizeNumber);
	}
}

void decodeSymbols(std::string code, const Node * node, std::string & res, const Node *startNode)
{
	for (std::size_t index = 0; index < code.length(); ++index)
	{
		if (code[index] == '0')
		{
			node = node->leftNode;
		}
		else
		{
			node = node->rightNode;
		}

		if (!node->leftNode && !node->rightNode)
		{
			res += node->data.firstArgument;
			node = startNode;
		}
	}
}

void decodeSymbolsFromFile(const std::string & fileName, std::string &res) // convert dec to bin
{
	std::ifstream fi(fileName.c_str(), std::ios::in);

	if (!fi.is_open())
	{
		std::cout << "Cannot open file\n";

		return;
	}

	int lastNumber = 0, numInt = 0;
	std::string line = "", all = "", number, binStr = "";

	while (getline(fi, line))
	{
		all += line;
	}

	for (int index = 0; index < all.length(); ++index)
	{
		if (all[index] != ' ' && all[index] >= '0' && all[index] <= '9')
		{
			while (all[index] != ' ' && all[index] >= '0' && all[index] <= '9')
			{
				number += all[index];
				++index;
			}

			numInt = std::stoi(number);

			if (all[index + 1] == char(253))
			{
				index += 3; // find special symbol on position [index + 1] and you need to skip one position to go to the number;
				lastNumber = all[index] - '0';

				std::string tmp = decToBin(numInt);
				std::string zeros((lastNumber - tmp.length()), '0');
				res += zeros + tmp;
			}
			else
			{
				// convert decimal to binary and put needed leading zeros
				std::string tmp = decToBin(numInt);
				std::string zeros((8 - tmp.length()), '0');
				res += zeros + tmp;
			}
			

			number = "";
		}
	}


	fi.close();
}