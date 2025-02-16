#pragma once
#ifndef PGM2_H
#define PGM2_H
#include <iostream>
#include <string>
#include <vector>

struct Word {
	std::string aWord;
	int wCount;
	Word() { aWord = std::string::npos; wCount = 0; };
	bool operator==(const std::string& str) { return aWord == str; };

};

void checkfiles(std::ifstream& x, std::ifstream& y);

std::vector<Word> fillMew(std::vector<Word>& mewWords, std::ifstream& mew);

std::vector<Word> fillCanterbury(std::vector<Word>& canterburyWords, std::ifstream& canterbury, int totalWords);

void removePuncs(std::vector<Word>& inputVec);

std::vector<Word> fillMid(std::vector<Word> canterBuryVec, std::vector<Word> mewVec, std::vector<Word> middleVec, std::vector<Word> distinctCanterBury);

void printResults(std::vector<Word> canterBuryVec, std::vector<Word> mewVec, std::vector<Word> middleVec, std::vector<Word> DistinctCanterbury);

std::vector<Word>  getCount(std::vector<Word> inputVec);

int moreThanfive(std::vector<Word> inputVec);

std::vector<Word> fillDistinct(std::vector<Word> canterBuryVec, std::vector<Word> middleVec, std::vector<Word> DistinctCanterbury);

std::vector<Word> removeDupes(std::vector<Word> inputVec);

bool compareStringLength(const Word& a, const Word& b);

bool compareByCount(const Word& a, const Word& b);

#endif // PGM2_H