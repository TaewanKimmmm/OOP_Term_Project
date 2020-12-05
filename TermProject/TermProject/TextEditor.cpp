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
	ConsoleMessage::printDefaultMessage();
}

void TextEditor::getUserInput() { 
	std::string userInput;

	do {
		/*system("cls");*/
		/*std::cout << "입력 : " << std::endl;
		OutputView::printBorderLine();
		setCursorPosition(7, 25);*/
		std::cin >> userInput;
		processUserInput(userInput);

	} while (!(userInput.length() == 1 && userInput[0] == 't'));
	
	// 이후 파일 저장 후 종료
}

void TextEditor::processUserInput(std::string userInput) {

	try {
		validateUserInputFormat(userInput); // 형식 예외처리
		std::string trimmedInput = trimParenthesisFromUserInput(userInput);

		switch (userInput[0]) {
			case 'i':
				insert(trimmedInput);
				break;
			case 'd':
				break;
			case 'c':
				break;
			case 's':
				break;
		}

	} catch (std::string exception) {
		std::cout << exception << "은 잘못된 형식입니다." << std::endl;
	}
	catch (std::exception) {
		std::cout << "재입력 요망" << std::endl;
	}
}

void TextEditor::validateUserInputFormat(std::string userInput) {
	std::regex textAction("^[cdis]\\(([^)]+)\\)$");
	std::regex pageMove("^[np]");

	if (std::regex_match(userInput, textAction) == 0 && std::regex_match(userInput, pageMove) == 0) {
		throw userInput;
	}
}

Line TextEditor::getLine(int lineNumber) {
	return Lines.at(lineNumber - 1);
}

void TextEditor::insert(std::string trimmedInput) { // 삽입 시에.. 3개의 파라미터가 있어야 하고..숫자 숫자 문자열..
	std::vector<std::string> result = TextCutter::split(trimmedInput, ',');
	if (result.size() != 3) {
		throw std::out_of_range("파라미터는 3개 입력해주세요");
	}
	int lineNumber = 0;
	int wordNumber = 0;

	std::stringstream lineInt(result[0]);
	std::stringstream wordInt(result[1]);

	lineInt >> lineNumber;
	wordInt >> wordNumber;

	validateInsert(lineNumber, wordNumber);
}

void TextEditor::validateInsert(int lineNumber, int wordNumber) {
	if (lineNumber <= 0 || lineNumber > 20) {
		throw std::out_of_range("줄 번호는 1과 20 사이여야 합니다.");
	}
	if (wordNumber <= 0 || wordNumber > getLine(lineNumber).size()) {
		throw std::out_of_range("단어가 존재하지 않습니다.");
	}
}

std::string TextEditor::trimParenthesisFromUserInput(std::string userInput) {
	return userInput.substr(2, userInput.length() - 3);
}

void TextEditor::setCursorPosition(int x, int y) {
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

