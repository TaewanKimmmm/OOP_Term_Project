#include "TextEditor.h"
#include "TextCutter.h"


void TextEditor::run() {
	std::vector<Line> Lines = TextCutter::makeLines();
	initialPrint(Lines);
	OutputView::printMenu();
	ConsoleMessage::printMessage();
	getUserInput();
}

void TextEditor::initialPrint(std::vector<Line> Lines) {
	for (int i = 0; i < 20; i++) {
		std::cout << std::setw(2) << std::right << (i + 1) << "| ";
		Lines[i].print();
	}
	OutputView::printBorderLine();
}

void TextEditor::setCursorPosition(int x, int y) {
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

void TextEditor::getUserInput() {
	std::string s;
	std::cout << "ют╥б : " << std::endl; 
	OutputView::printBorderLine();
	setCursorPosition(7, 25);
	while (1) {
		std::cin >> s;
		setCursorPosition(7, 25);
	}	
}

