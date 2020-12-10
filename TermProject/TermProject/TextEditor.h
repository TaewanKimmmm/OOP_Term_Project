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
	int startLine = 0;
	int endLine = 20;

	ConsoleMessage* consoleMessage;

	std::vector<Line> lines;
	void setLines(std::vector<Line> Lines);
	void getUserInput();
	void setCursorPosition(int x, int y);
	void updateText();
	void processUserInput(std::string userInput);
	void validateUserInputFormat(std::string userInput);
	void validateInsert(int lineNumber, int wordNumber);
	std::string trimParenthesisFromUserInput(std::string userInput);
	
	void insert(std::string trimmedInput);
	void AdjustAfterInsertionOfLine(int lineNumber);
	void showPreviousPage();
	void showNextPage();

public:
	void run();
};