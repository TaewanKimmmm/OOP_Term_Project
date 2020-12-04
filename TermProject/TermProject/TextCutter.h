#pragma once
#include <iostream>
#include <fstream>
#include <string>

class TextCutter {
private:
	std::string loadTextFile();

public:
	std::string makeLines();
};