#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
#include <sstream> // seems too easy to be allowed
#include "pgm2.h"

const int MEW_WORD_MAX = 21541; // just see how many lines are in the text file

// dont really know where else to put this 



// So you dont forget tomorrow 
// el progama de "stl sort" es muy jodido 
// Mi corazón anhela la muerte
//
// - de kaj del pasado

int main() {
	std::vector<Word> canterburyWords(0); // i mean, there are zero words in the vector when its created. it makes sense i guess.
	std::vector<Word> mewWords(MEW_WORD_MAX + 1); // this however idfk,,
	std::vector<Word> midEnglishWords(0);
	std::vector<Word> DistinctCanterBury(0);
	
	int totalWords = 0;
	
	
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

	// fill midEnglish words with words not appearing in the Mew Dictionary
	midEnglishWords = fillMid(canterburyWords, mewWords, midEnglishWords, DistinctCanterBury);
	DistinctCanterBury = fillDistinct(canterburyWords, midEnglishWords, DistinctCanterBury);

	// init our count of words
	canterburyWords = getCount(canterburyWords);
	midEnglishWords = getCount(midEnglishWords);
	DistinctCanterBury = getCount(DistinctCanterBury);
	

	std::sort(midEnglishWords.begin(), midEnglishWords.end(), compareByCount);
	std::sort(canterburyWords.begin(), canterburyWords.end(), compareByCount);
	std::sort(DistinctCanterBury.begin(), DistinctCanterBury.end(), compareByCount);
	std::reverse(midEnglishWords.begin(), midEnglishWords.end());
	std::reverse(canterburyWords.begin(), canterburyWords.end());
	std::reverse(DistinctCanterBury.begin(), DistinctCanterBury.end());

	

	  printResults(canterburyWords, mewWords, midEnglishWords, DistinctCanterBury);

	return 0;
}