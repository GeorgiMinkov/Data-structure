#pragma once
#include "HuffmanTree.h"
#include "MinHeap.hpp"
//#include <string>
//#include <iostream>
// #include <fstream>

void menu();
void mainProgram();
void startArchive(const std::string &src);

void lego(std::string src);
void makeTable(std::string src, DynamicTable<char, std::size_t> &table);
void makeMinimumHeap(MinHeap<Node *> &heap, DynamicTable<char, std::size_t> table);
void makeHuffmanTree(MinHeap<Node *> heap, HuffmanTree &tree);

// ENCODING FUNCTION
void encodeSymbols(Node *node, DynamicTable<char, std::string> &table, std::string code);
int binToDec(std::string str);
void readFileInputData(const std::string &fileName, std::string &str);
// WRITE ENCODED DATA TO FILE
void archive(const std::size_t &lastNumberSize, std::string decStr, std::string &fileName);

// DECODING FUNCTIONS
std::string decToBin(int number); // измисли как ще изглежда
void transferBitsToDec(std::string code, std::string &res, std::size_t &lastSizeNumber);
void decodeSymbols(std::string code, const Node *node, std::string &res, const Node *startNode);
void decodeSymbolsFromFile(const std::string &fileName, std::string &res); // from file with dec code convert to bin code