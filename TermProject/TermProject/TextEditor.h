#pragma once
#include <vector>

#include "Line.h"
#include <iostream>
#include <iomanip>

class TextEditor {

private:
	void initialPrint(std::vector<Line> Lines);

public:
	void run();
};