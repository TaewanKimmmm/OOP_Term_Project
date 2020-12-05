#pragma once
#include <vector>
#include <iostream>
#include <iomanip>
#include <windows.h>
#include <string>
#include <regex>

#include "Line.h"
#include "OutputView.h"
#include "ConsoleMessage.h"
#include "TextCutter.h"



class TextEditor {

private:
	std::vector<Line> Lines;
	void setLines(std::vector<Line> Lines);
	void getUserInput();
	void setCursorPosition(int x, int y);
	void initialPrint();
	void processUserInput(std::string userInput);
	void validateUserInput(std::string userInput);

public:
	void run();
};