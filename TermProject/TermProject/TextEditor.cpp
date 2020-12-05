#include "TextEditor.h"
#include "TextCutter.h"
#include <iostream>

void TextEditor::run() {
	std::cout << "TextEditor" << std::endl;
	std::vector<Line> Lines = TextCutter::makeLines();

	for (int i = 0; i < Lines.size(); i++) {
		Lines[i].print();
	}

}