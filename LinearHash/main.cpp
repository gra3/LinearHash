//Runs and times 10 different hash tables and saves the information in output.txt
//Can take a long time with large tables.
//Tested up to 27k entries

#include <iostream>
#include <fstream>
#include "Complexity_Recorder.hpp"
#include "Complexity_Timer.hpp"
#include "LinearHash.h"
#include "Hashtable.hpp"
#include "H1Hash.h"
#include <vector>

using namespace std;

vector<string> wordList;
vector<int> convertedWordList;

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

void convertWordListToInt()
{
	convertedWordList.clear();
	for(int i=0;i<wordList.size();i++)
	{
		int strValue = 0;
		for(int j=0;j<wordList[i].length();j++)
		{
			strValue += wordList[i][j];
		}
		convertedWordList.push_back(strValue);
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

void addH2(Hashtable<int> &hashIn)
{
	for(int i=0;i<wordList.size();i++)
	{
		hashIn.insert(convertedWordList[i]);
	}
}

void rmH2(Hashtable<int> &hashIn)
{
	for(int i=0;i<wordList.size();i++)
	{
		hashIn.remove(convertedWordList[i]);
	}
}

void addH1(HashMap &hashIn)
{
	for(int i=0;i<wordList.size();i++)
	{
		hashIn.insert(convertedWordList[i]);
	}
}

void rmH1(HashMap &hashIn)
{
	for(int i=0;i<wordList.size();i++)
	{
		hashIn.remove(convertedWordList[i]);
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

	cout << "Linear HashTable size " << tableSize << " done!!" << endl;
}

void testH2(int numberOfWords, int numBuckets, vector<recorder<timer>> &stats)
{
	Hashtable<int> h(numBuckets);
	loadWords(numberOfWords);
	convertWordListToInt();

	timer timer1;
	recorder<timer> singleStat;
	singleStat.reset();

	//Add
	timer1.restart();
	addH2(h);
	timer1.stop();
	singleStat.record(timer1);
	stats.push_back(singleStat);
	singleStat.reset();

	//RM
	timer1.restart();
	rmH2(h);
	timer1.stop();
	singleStat.record(timer1);
	stats.push_back(singleStat);
	singleStat.reset();

	cout << "H2 size " << numberOfWords << " and " << numBuckets << " buckets done!! " << endl;
}

void testH1(int numberOfWords, int numLists, vector<recorder<timer>> &stats)
{
	HashMap h(numLists);
	loadWords(numberOfWords);
	convertWordListToInt();

	timer timer1;
	recorder<timer> singleStat;
	singleStat.reset();

	//Add
	timer1.restart();
	addH1(h);
	timer1.stop();
	singleStat.record(timer1);
	stats.push_back(singleStat);
	singleStat.reset();

	//RM
	timer1.restart();
	rmH1(h);
	timer1.stop();
	singleStat.record(timer1);
	stats.push_back(singleStat);
	singleStat.reset();

	cout << "H1 size " << numberOfWords << " and " << numLists << " lists done!! " << endl;
}

//Prints the results into file output.txt
void writeOutput(vector<recorder<timer>> &stats, vector<int> n, string outputFileName)
{
	ofstream outFile;
	outFile.open(outputFileName, ofstream::out | ofstream::trunc);

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
	vector<recorder<timer>> linearStats;
	//int nArray[] = {13,97,151, 263,509,739,1033,1259,1553,1721};
	int nArray[] = {1049,2111,4049,7177,10093,13337,16033,19403,23297,27743};
	vector<int> n(nArray, nArray + sizeof(nArray)/sizeof(int));

	test(n[0],53,linearStats);
	test(n[1],101,linearStats);
	test(n[2],233,linearStats);
	test(n[3],379,linearStats);
	test(n[4],563,linearStats);
	test(n[5],613,linearStats);
	test(n[6],857,linearStats);
	test(n[7],1069,linearStats);
	test(n[8],1399,linearStats);
	test(n[9],2389,linearStats);
	writeOutput(linearStats,n,"linearHashOutput.txt");

	vector<recorder<timer>> H2stats;

	int h2nArray[] = {1049,2111,4049,7177,10093,13337,16033,19403,23297,27743};
	vector<int> h2n(h2nArray, h2nArray + sizeof(h2nArray)/sizeof(int));

	testH2(h2n[0],101,H2stats);
	testH2(h2n[1],101,H2stats);
	testH2(h2n[2],101,H2stats);
	testH2(h2n[3],101,H2stats);
	testH2(h2n[4],101,H2stats);
	testH2(h2n[5],101,H2stats);
	testH2(h2n[6],101,H2stats);
	testH2(h2n[7],101,H2stats);
	testH2(h2n[8],101,H2stats);
	testH2(h2n[9],101,H2stats);
	writeOutput(H2stats,h2n, "H2Output.txt");

	vector<recorder<timer>> H1stats;

	int h1nArray[] = {1049,2111,4049,7177,10093,13337,16033,19403,23297,27743};
	vector<int> h1n(h1nArray, h1nArray + sizeof(h1nArray)/sizeof(int));

	testH1(h1n[0],10,H1stats);
	testH1(h1n[1],10,H1stats);
	testH1(h1n[2],10,H1stats);
	testH1(h1n[3],10,H1stats);
	testH1(h1n[4],10,H1stats);
	testH1(h1n[5],10,H1stats);
	testH1(h1n[6],10,H1stats);
	testH1(h1n[7],10,H1stats);
	testH1(h1n[8],10,H1stats);
	testH1(h1n[9],10,H1stats);
	writeOutput(H1stats,h1n, "H1Output.txt");


	return 0;
}