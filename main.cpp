#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
#include <sstream> // seems too easy to be allowed
#include "pgm2.h"

// dont really know where else to put this 
bool compareByCount(const Word& a, const Word& b)
{
	return a.wCount < b.wCount;
}

bool compareStringLength(const Word& a, const Word& b) {
	return a.aWord.length() < b.aWord.length();
}

const int MEW_WORD_MAX = 21541; // just see how many lines are in the text file

// So you dont forget tomorrow 
// el progama de "stl sort" es muy jodido
// Mi corazón anhela la muerte
//
// - de kaj del pasado

int main() {
	std::vector<Word> canterburyWords(0); // i mean, there are zero words in the vector when its created. it makes sense i guess.
	std::vector<Word> mewWords(MEW_WORD_MAX + 1); // this however idfk,,
	std::vector<Word> midEnglishWords(0);
	
	int totalWords = 0;
	std::string temp = "";
	int i = 0;
	
	// open the files
	std::ifstream canterbury("canterbury.txt");
	std::ifstream mew("mew.txt");
	
	// check if files are open.
	checkfiles(canterbury, mew);
	
	// read the mew dictionary and store the words in the vector.
	fillMew(mewWords, mew);
	
	// read the canterbury.txt file and store the words in the vector.
	fillCanterbury(canterburyWords, canterbury, totalWords);
	// remove punctuation from strings in the vector.
	removePuncs(canterburyWords);
	
	// as to be memory efficient
	canterbury.close();
	mew.close();

	// sort by length of string, compareStringLength is a pointer to the function
	std::sort(mewWords.begin(), mewWords.end(), compareStringLength);
	std::sort(canterburyWords.begin(), canterburyWords.end(), compareStringLength);
	
	fillMid(canterburyWords, mewWords, midEnglishWords);
	
	std::cout << midEnglishWords[0].aWord;

	return 0;
}