#pragma once
#include <vector>
#include <iostream>
#include <iomanip>
#include <windows.h>
#include <string>

#include "Line.h"
#include "Menu.h"


class TextEditor {

private:
	void getUserInput();
	void printBoundary();
	void setCursorPosition(int x, int y);
	void initialPrint(std::vector<Line> Lines);

public:
	void run();
};