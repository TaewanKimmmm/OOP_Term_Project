#include "TextEditor.h"
#include "TextCutter.h"
#include <iostream>

void TextEditor::run() {
	std::cout << "TextEditor" << std::endl;
	TextCutter *myTextCutter = new TextCutter;
	myTextCutter->makeLines();
}