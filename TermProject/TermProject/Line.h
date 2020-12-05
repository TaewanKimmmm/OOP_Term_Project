#pragma once
#include <string>
#include <vector>
#include <iostream>

class Line {

private:
	static const int MAXIMUM_LENGTH= 75;
	std::vector<std::string> words;
	int length;

public:
	Line(std::vector<std::string> words);
	int size();
	std::string get(int index);
	void print();

};