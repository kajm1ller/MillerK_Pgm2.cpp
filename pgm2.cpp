#include "pgm2.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <cctype>


void checkfiles(std::ifstream& x, std::ifstream& y) {
	if (!x.is_open()) {
		std::cerr << "Error: First file could not be opened." << std::endl;
	}
	if (!y.is_open()) {
		std::cerr << "Error: Second file could not be opened." << std::endl;
	}
}

// I could in theory use a template here, but 
// they use different file streams and it looks complicated.

std::vector<Word> fillMew(std::vector<Word>& mewWords, std::ifstream& mew) {
	int i = 0;
	std::string temp;

	while (std::getline(mew, temp)) {
		mewWords[i].aWord = temp;
		i++;
	}
	return mewWords;
}

std::vector<Word> fillCanterbury(std::vector<Word>& canterburyWords, std::ifstream& canterbury, int totalWords) {
	std::string temp = "";
	int i = 0;

	while (std::getline(canterbury, temp)) {
		std::stringstream split(temp);
		// splits line into words. convienent! i'm sure this'll
		// come back to bite me in the ass later.
		
		while (split >> temp) {
			std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
			// total hack 

			canterburyWords.resize(canterburyWords.size() + 1);
			canterburyWords[i].wCount++;
			canterburyWords[i].aWord = temp;
			
;			i++;
		}
	}
	return canterburyWords;
}


void removePuncs(std::vector<Word>& inputVec) {
		for (int i = 0; i < inputVec.size(); ++i) {
			// ugly expression but what else am I to do
			inputVec[i].aWord.erase(std::remove_if(inputVec[i].aWord.begin(), inputVec[i].aWord.end(), ::ispunct), inputVec[i].aWord.end());
		}
	
}


	
// im going to have binary search return -1 if false, or the value if true. 

int binarySearch(std::vector<Word> &arr, const std::string& target, int low, int high) {
	if (low <= high) {
		int mid = low + (high - low) / 2;

		if (arr[mid].aWord == target) {
			// as of right now we are literally never returning mid. Something is wrong
			return mid;
		}
		else if (arr[mid].aWord < target) {
			return binarySearch(arr, target, mid + 1, high);
		}
		else {
			return binarySearch(arr, target, low, mid - 1);
		}
	}
	return -1;
}




std::vector<Word> fillMid(std::vector<Word> canterBuryVec, std::vector<Word> mewVec, std::vector<Word> middleVec) {
	
	// Sort the mewVec vector. for some reason I have to sort this vector twice? I dont know
	std::sort(mewVec.begin(), mewVec.end(), [](const Word& a, const Word& b) {
		return a.aWord < b.aWord;
		});

	int middleIndex = -1; // set to -1 to not get out of bounds
	for (int i = 0; i < canterBuryVec.size(); ++i) {
		if (binarySearch(mewVec, canterBuryVec[i].aWord, 0, mewVec.size() - 1) != -1) {
			middleIndex++;
			std::string temp = canterBuryVec[i].aWord;
			middleVec.resize(middleVec.size() + 1); // resize the vector to accommodate the new word
			middleVec[middleIndex].aWord = temp;
		}
		else {
			continue;
		}
	}
	return middleVec;
}

void printResults(std::vector<Word> canterBuryVec, std::vector<Word> mewVec, std::vector<Word> middleVec)
{
	std::cout << "Count of all words used in Canterbury Tales: " << canterBuryVec.size() << "\n\n";
	std::cout << "Distinct Middle English Words = " << middleVec.size() << std::endl;
	std::cout << "Distinct Modern English Words = " << canterBuryVec.size() - middleVec.size() << std::endl;
	// have to sort by count for the rest of this shit
	
}
