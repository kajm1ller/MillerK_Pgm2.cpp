#include "pgm2.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <cctype>
#include <unordered_map>


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

std::vector<Word> getCount(std::vector<Word> inputVec) {
	std::unordered_map<std::string, int> wordCountMap;
	for (const auto& word : inputVec) {
		wordCountMap[word.aWord]++;
	}
	for (auto& word : inputVec) {
		word.wCount = wordCountMap[word.aWord];
	}
	return inputVec;
}


std::vector<Word> fillMid(std::vector<Word> canterBuryVec, std::vector<Word> mewVec, std::vector<Word> middleVec, std::vector<Word> distinctCanterBury) {
	// Sort the mewVec vector
	std::sort(mewVec.begin(), mewVec.end(), [](const Word& a, const Word& b) {
		return a.aWord < b.aWord;
	});

	// Remove duplicates from mewVec
	mewVec = removeDupes(mewVec);

	for (const auto& word : canterBuryVec) {
		if (binarySearch(mewVec, word.aWord, 0, static_cast<int>(mewVec.size()) - 1) == -1) {
			std::string temp = word.aWord;
			middleVec.resize(middleVec.size() + 1);
			middleVec[middleVec.size() - 1].aWord = temp;
		}
	}
	return middleVec;
}
	

std::vector<Word> fillDistinct(std::vector<Word> canterBuryVec, std::vector<Word> middleVec, std::vector<Word> DistinctCanterbury) {
	
	int distinctIndex = -1;
	for (int i = 0; i < canterBuryVec.size(); ++i) {
		std::string temp = canterBuryVec[i].aWord;
		if (binarySearch(middleVec, canterBuryVec[i].aWord, 0, middleVec.size() - 1) == -1) {
			distinctIndex++;
			DistinctCanterbury.resize(DistinctCanterbury.size() + 1);
			DistinctCanterbury[distinctIndex].aWord = temp;
		}
		else {
			continue;
		}
	}
	return DistinctCanterbury;

}


int moreThanfive(std::vector<Word> inputVec) {
	int count = 0;

	for (int i = 0; i < inputVec.size(); ++i) {
		if (inputVec[i].aWord.length() >= 5) {
			count++;
		}
	}
	return count;
}

void printResults(std::vector<Word> canterBuryVec, std::vector<Word> mewVec, std::vector<Word> middleVec, std::vector<Word> DistinctCanterbury)
{
	std::cout << "Count of all words used in Canterbury Tales: " << canterBuryVec.size() << "\n\n";
	std::cout << "Distinct Middle English Words = " << middleVec.size() << "\n\n";
	std::cout << "Distinct Modern English Words = " << canterBuryVec.size() - middleVec.size() << "\n\n";
	int ModernmoreThanFive = moreThanfive(DistinctCanterbury);
	int MiddlemoreThanFive = moreThanfive(middleVec);
	std::cout << "Count of Modern English Words (>=5 Letters): " << ModernmoreThanFive << "\n\n";
	std::cout << "Count of Middle English Words (>=5 Letters): " << MiddlemoreThanFive << "\n\n";

	canterBuryVec = removeDupes(canterBuryVec);
	middleVec = removeDupes(middleVec);
	DistinctCanterbury = removeDupes(DistinctCanterbury);
	std::sort(canterBuryVec.begin(), canterBuryVec.end(), compareByCount);
	std::sort(middleVec.begin(), middleVec.end(), compareByCount);
	std::sort(DistinctCanterbury.begin(), DistinctCanterbury.end(), compareByCount);
	std::reverse(middleVec.begin(), middleVec.end());
	std::reverse(canterBuryVec.begin(),canterBuryVec.end());
	std::reverse(DistinctCanterbury.begin(), DistinctCanterbury.end());

	std::cout << "Freq of Modern English Words" << std::endl;
	std::cout << "Word" << std::setw(20) << "Frequency" << std::endl;
	for (int i = 0; i < 5; ++i) {
		std::cout << DistinctCanterbury[i].aWord << std::setw(20) << DistinctCanterbury[i].wCount << std::endl;
		
	}
	std::cout << std::endl;
	std::cout << "Freq of Middle English Words" << std::endl;
	std::cout << "Word" << std::setw(20) << "Frequency" << std::endl;
	for (int i = 0; i < 5; ++i) {
		std::cout << middleVec[i].aWord << std::setw(20) << middleVec[i].wCount << std::endl;
	}

}

std::vector<Word> removeDupes(std::vector<Word> inputVec) {
	std::sort(inputVec.begin(), inputVec.end(), [](const Word& a, const Word& b) {
		return a.aWord < b.aWord;
		});
	inputVec.erase(std::unique(inputVec.begin(), inputVec.end(), [](const Word& a, const Word& b) {
		return a.aWord == b.aWord;
		}), inputVec.end());
	return inputVec;
}

bool compareByCount(const Word& a, const Word& b)
{
	return a.wCount < b.wCount;
}

bool compareStringLength(const Word& a, const Word& b) {
	return a.aWord.length() < b.aWord.length();
}
