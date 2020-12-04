#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

class TextCutter {
private:
	TextCutter();
	static std::string loadTextFile();
	static std::vector<std::string> split(std::string input, char delimiter);

public:
	static std::string makeLines();
};