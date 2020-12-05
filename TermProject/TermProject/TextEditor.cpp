#include "TextEditor.h"
#include "TextCutter.h"


void TextEditor::run() {
	setLines(TextCutter::makeLines());
	getUserInput();
}

void TextEditor::setLines(std::vector<Line> Lines) {
	this->Lines = Lines;
}

void TextEditor::initialPrint() {
	for (int i = 0; i < 20; i++) {
		std::cout << std::setw(2) << std::right << (i + 1) << "| ";
		this->Lines[i].print();
	}
	OutputView::printBorderLine();
	OutputView::printMenu();
	ConsoleMessage::printMessage();
}

void TextEditor::getUserInput() { 
	std::string userInput;

	do {
		system("cls");
		initialPrint();
		std::cout << "입력 : " << std::endl;
		OutputView::printBorderLine();
		setCursorPosition(7, 25);
		std::cin >> userInput;
		processUserInput(userInput);
	} while (!(userInput.length() == 1 && userInput[0] == 't'));
	
	// 이후 파일 저장 후 종료
}

void TextEditor::processUserInput(std::string userInput) {

}

void TextEditor::setCursorPosition(int x, int y) {
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

