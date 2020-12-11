#pragma once
#include <string>
#include <vector>
#include <iostream>

class Line {

private:
	static const int MAXIMUM_LENGTH= 75;

	std::vector<std::string> words;
	int byteLength;

public:
	Line();
	Line(std::vector<std::string> words);
	std::string get(int index);
	int size();
	void print();
	void insertWord(int idx, std::string word);
	void removeWord(int idx);
	int searchWord(std::string word);
	int getByteLength();

};