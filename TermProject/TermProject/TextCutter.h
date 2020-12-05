#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "Line.h"

class TextCutter {

private:
	static const int MAXIMUM_LENGTH = 75;
	static const int SPACE = 1;
	TextCutter();
	static std::string loadTextFile();
	static std::vector<std::string> split(std::string input, char delimiter);
	static std::vector<std::string> makeWords();
	static void makeLine();

public:
	static std::vector<Line> makeLines();
};