#include "TextEditor.h"
#include "TextCutter.h"


void TextEditor::run() {
	setLines(TextCutter::makeLines());
	initialPrint();
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
		/*system("cls");*/
		/*std::cout << "�Է� : " << std::endl;
		OutputView::printBorderLine();
		setCursorPosition(7, 25);*/
		std::cin >> userInput;
		processUserInput(userInput);

	} while (!(userInput.length() == 1 && userInput[0] == 't'));
	
	// ���� ���� ���� �� ����
}

void TextEditor::processUserInput(std::string userInput) {

	try {
		validateUserInput(userInput); // ����
		switch (userInput[0]) {
		case 'i':
			break;
		case 'd':
			break;
		case 'c':
			break;
		case 's':
			break;
		}

	} catch (std::string exception) {
		std::cout << exception << "�� �ùٸ��� ���� �Է��Դϴ�." << std::endl;
	}

	//if (userInput[0] == 'i') {
	//	//userInput.substr(1);
	//	std::cout << userInput.substr(2, userInput.length()-3) << std::endl;
	//}
}

void TextEditor::validateUserInput(std::string userInput) {
	std::regex textAction("^[cdis]\\(([^)]+)\\)$");
	std::regex pageMove("^[np]");

	if (std::regex_match(userInput, textAction) == 0 && std::regex_match(userInput, pageMove) == 0) {
		throw userInput;
	}
	
}

void TextEditor::setCursorPosition(int x, int y) {
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

