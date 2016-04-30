#pragma once
#include <string>
#include <list>
#include <iostream>

using namespace std;

class LinearHash
{
public:
	
	string * hashTable;
	int tableSize;
	int stepSize; //for linear probing

	LinearHash(int sizeIn, int stepSizeIn);
	~LinearHash(void);

	int hash(string value);

	int linProbe(string value, int probeSequenceNum);

	int strToInt(string value);

	void add(string value);

	int retrieve(string value);

	bool remove(string value);

	void print();

	bool isFull();
	bool isEmpty();
};

