#pragma once
#include <vector>
#include <iostream>
#include <iomanip>
#include <windows.h>
#include <string>
#include <regex>
#include <sstream>

#include "Line.h"
#include "OutputView.h"
#include "ConsoleMessage.h"
#include "TextCutter.h"



class TextEditor {

private:
	int startLine = 1;
	int endLine = 20;

	std::vector<Line> Lines;
	Line getLine(int lineNumber);
	void setLines(std::vector<Line> Lines);
	void getUserInput();
	void setCursorPosition(int x, int y);
	void initialPrint();
	void processUserInput(std::string userInput);
	void validateUserInputFormat(std::string userInput);
	void validateInsert(int lineNumber, int wordNumber);
	std::string trimParenthesisFromUserInput(std::string userInput);
	
	void insert(std::string trimmedInput);

public:
	void run();
};