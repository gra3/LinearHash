#include "LinearHash.h"

LinearHash::LinearHash(int sizeIn, int stepSizeIn)
{
	hashTable = new string[sizeIn];
	tableSize = sizeIn;
	stepSize = stepSizeIn;
}


LinearHash::~LinearHash(void)
{
	delete[] hashTable;
}

int LinearHash::hash(string value)
{
	return strToInt(value) % tableSize;
}

int LinearHash::linProbe(string value, int probeSequenceNum)
{
	return ((hash(value) + probeSequenceNum*stepSize) % tableSize);
}

int LinearHash::strToInt(string value)
{
	int strValue = 0;
	for(int i=0;i<value.length();i++) strValue += value[i];
	return strValue;
}

void LinearHash::add(string value)
{
	int key = hash(value);

	//hash() is successful
	if(hashTable[key].empty())
	{
		hashTable[key] = value;
		//cout << "Hash Successful - " << value << " added to slot " << key << endl;
	}
	else
	{
		if(!isFull())
		{
			bool foundHome = false;
			int probeSeqNum = 1;
			while(!foundHome)
			{
				//cout << "Probing " << probeSeqNum << " - " << value << endl;
				int probeIdx = linProbe(value,probeSeqNum);
				if(hashTable[probeIdx].empty()||hashTable[probeIdx] == "tombStone")
				{
					hashTable[probeIdx] = value;
					//cout << "---Probe Successful - " << value << " added to slot " << probeIdx << endl;
					foundHome = true;
				}
				else
				{
					//cout << "---Probe Failed - " << "probe idx: " << probeIdx << endl;
					probeSeqNum++;
				}
			}
		}
		else
		{
			//cout << "Cannot add: " << value << ". Table is Full!!" << endl;
		}
	}
}

int LinearHash::retrieve(string value)
{
	int idx = hash(value);
	if(hashTable[idx].empty())
	{
		cout << "FAILED TO FIND " << value << "!!!" << endl;
	}
	else
	{
		if(hashTable[idx] == value)
		{
			return idx;
		}
		else
		{
			bool found = false;
			int probeSeqNum = 1;
			while(!found)
			{
				int probeIdx = linProbe(value,probeSeqNum);
				if(!hashTable[probeIdx].empty())
				{
					if(hashTable[probeIdx] == value)
					{
						return probeIdx;
						found = true;
					}
					else
					{
						probeSeqNum++;
					}
				}
				else
				{
					cout << "FAILED TO FIND " << value << "!!!" << endl;
				}
			}
		}
	}
}

bool LinearHash::remove(string value)
{
	int idx = hash(value);
	if(hashTable[idx].empty())
	{
		//cout << "FAILED TO FIND " << value << "!!!" << endl;
		return false;
	}
	else
	{
		if(hashTable[idx] == value)
		{
			hashTable[idx] = "tombStone";
			return true;
		}
		else
		{
			bool found = false;
			int probeSeqNum = 1;
			while(!found)
			{
				int probeIdx = linProbe(value,probeSeqNum);
				if(!hashTable[probeIdx].empty())
				{
					if(hashTable[probeIdx] == value)
					{
						hashTable[probeIdx] = "tombStone";
						return true;
						found = true;
					}
					else
					{
						probeSeqNum++;
					}
				}
				else
				{
					//cout << "FAILED TO FIND " << value << "!!!" << endl;
					return false;
				}
			}
		}
	}
}

void LinearHash::print()
{
	cout << endl << "Printing Hash Table - Size " << tableSize << endl;
	for(int i=0;i<tableSize;i++)
	{
		cout << i << ". " << hashTable[i] << endl;
	}
	cout << endl;
}

bool LinearHash::isFull()
{
	bool isFull = true;
	for(int i=0;i<tableSize;i++)
	{
		if(hashTable[i].empty()||hashTable[i] == "tombStone") return false;
	}
	return isFull;
}

bool LinearHash::isEmpty()
{
	bool isEmpty = true;
	for(int i=0;i<tableSize;i++) if(!hashTable[i].empty()) isEmpty = false;
	return isEmpty;
}
