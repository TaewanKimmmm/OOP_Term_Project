#include "TextEditor.h"
#include "TextCutter.h"


void TextEditor::run() {
	std::vector<Line> Lines = TextCutter::makeLines();
	initialPrint(Lines);

}

void TextEditor::initialPrint(std::vector<Line> Lines) {
	for (int i = 0; i < 20; i++) {
		std::cout << std::setw(2) << std::right << (i + 1) << "| ";
		Lines[i].print();
	}
}