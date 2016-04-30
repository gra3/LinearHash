//Runs and times 10 different hash tables and saves the information in output.txt
//Can take a long time with large tables.
//Tested up to 27k entries

#include <iostream>
#include <fstream>
#include "Complexity_Recorder.hpp"
#include "Complexity_Timer.hpp"
#include "LinearHash.h"
#include <vector>

using namespace std;

vector<string> wordList;

//Loads # of words to memory from file words.txt
void loadWords(int numberOfWords)
{
	wordList.clear();

	ifstream file("words.txt");
	if(file.is_open())
	{
		for(int i=0;i<numberOfWords;i++)
		{
			string temp;
			file >> temp;
			wordList.push_back(temp);
		}
		file.close();
	}
}

//Adds the loaded words to the table
void addToTable(LinearHash &hashIn)
{
	for(int i=0;i<wordList.size();i++)
	{
		hashIn.add(wordList[i]);
	}
}

//removes all the loaded words from the table
void rmFromTable(LinearHash &hashIn)
{
	for(int i=0;i<wordList.size();i++)
	{
		hashIn.remove(wordList[i]);
	}
}

//Times the functions add and remove for a given table size and linear probing step size
void test(int tableSize, int stepSize, vector<recorder<timer>> &stats)
{
	LinearHash h(tableSize,stepSize);
	loadWords(tableSize);

	timer timer1;
	recorder<timer> singleStat;
	singleStat.reset();

	//Add
	timer1.restart();
	addToTable(h);
	timer1.stop();
	singleStat.record(timer1);
	stats.push_back(singleStat);
	singleStat.reset();
	//h.print();

	//Remove
	timer1.restart();
	rmFromTable(h);
	timer1.stop();
	singleStat.record(timer1);
	stats.push_back(singleStat);
	singleStat.reset();
	//h.print();

	cout << "HashTable size " << tableSize << " done!!" << endl;
}

//Prints the results into file output.txt
void writeOutput(vector<recorder<timer>> &stats, vector<int> n)
{
	ofstream outFile;
	outFile.open("output.txt", ofstream::out | ofstream::trunc);

	if(stats.size()/2!=n.size()) cout << "Error writeOutput:  stats/n mismatch" << endl;
	else
	{
		outFile << "N\tAdd\tRemove" << endl;
		for(int i=0;i<n.size();i++)
		{
			outFile << n[i] << "\t";
			stats[2*i].report(outFile,n[i]);
			outFile << "\t";
			stats[2*i+1].report(outFile,n[i]);
			outFile << endl;
		}
	}
	outFile.close();
}

int main(int argc, char*argv[])
{
	const int number_of_tests = 20; //10 different N's, 2 operations per

	vector<recorder<timer>> stats;
	//int nArray[] = {13,97,151, 263,509,739,1033,1259,1553,1721};
	int nArray[] = {1049,2111,4049,7177,10093,13337,16033,19403,23297,27743};
	vector<int> n(nArray, nArray + sizeof(nArray)/sizeof(int));

	test(n[0],53,stats);
	test(n[1],101,stats);
	test(n[2],233,stats);
	test(n[3],379,stats);
	test(n[4],563,stats);
	test(n[5],613,stats);
	test(n[6],857,stats);
	test(n[7],1069,stats);
	test(n[8],1399,stats);
	test(n[9],2389,stats);
	writeOutput(stats,n);
	return 0;
}