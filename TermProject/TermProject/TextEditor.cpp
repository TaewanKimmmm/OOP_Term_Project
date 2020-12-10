#include "TextEditor.h"
#include "TextCutter.h"


void TextEditor::run() {
	setLines(TextCutter::makeLines());
	this->consoleMessage = new ConsoleMessage();
	getUserInput();
	delete consoleMessage;
}

void TextEditor::setLines(std::vector<Line> lines) {
	this->lines = lines;
}

void TextEditor::updateText() {
	for (int i = this->startLine; i < this->endLine; i++) {
		std::cout << std::setw(2) << std::right << (i + 1) << "| ";
		this->lines[i].print();
	}
	OutputView::printBorderLine();
	OutputView::printMenu();
	consoleMessage->printMessage();
	consoleMessage->setMessage("(콘솔 메시지)");
}

void TextEditor::getUserInput() { 
	std::string userInput;

	do {
		updateText();
		std::cout << "입력 : " << std::endl;
		OutputView::printBorderLine();
		setCursorPosition(7, 25);
		std::cin >> userInput;
		processUserInput(userInput);
		system("cls");

	} while (!(userInput.length() == 1 && userInput[0] == 't'));
	
	// 이후 파일 저장 후 종료
}

void TextEditor::processUserInput(std::string userInput) {
	
	try {
		validateUserInputFormat(userInput); 
		std::string trimmedInput;
		
		if (!(userInput[0] == 'n' || userInput[0] == 'p')) {
			trimParenthesisFromUserInput(userInput);
		}

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
			case 'p':
				showPreviousPage();
				break;
			case 'n':
				showNextPage();
				break;
		}

	} catch (std::string exception) {
		this->consoleMessage->setMessage(exception + "은 잘못된 형식입니다.");
	}
	catch (std::exception e) {
		std::string errorMessage = e.what();
		this->consoleMessage->setMessage("재입력 요망! " + errorMessage);
	}
}

void TextEditor::validateUserInputFormat(std::string userInput) {
	std::regex textAction("^[cdis]\\(([^)]+)\\)$");
	std::regex pageMove("^[np]");

	if (std::regex_match(userInput, textAction) == 0 && std::regex_match(userInput, pageMove) == 0) {
		throw userInput;
	}
}

void TextEditor::insert(std::string trimmedInput) { 
	std::vector<std::string> result = TextCutter::split(trimmedInput, ',');
	if (result.size() != 3) {
		throw std::exception("파라미터는 3개 입력해주세요");
	}
	if (result[2].length() > 75) {
		throw std::out_of_range("추가하려는 단어가 너무 깁니다.");
	}
	int lineNumber = 0;
	int wordNumber = 0;

	std::stringstream lineInt(result[0]);
	std::stringstream wordInt(result[1]);

	lineInt >> lineNumber;
	wordInt >> wordNumber;

	validateInsert(lineNumber, wordNumber);

	Line& selectedLine = lines[lineNumber-1];
	selectedLine.insertWord(wordNumber, result[2]);
	AdjustAfterInsertionOfLine(lineNumber);
}

void TextEditor::validateInsert(int lineNumber, int wordNumber) {
	if (lineNumber <= 0 || lineNumber > 20) {
		throw std::out_of_range("줄 번호는 1과 20 사이여야 합니다.");
	}
	if (wordNumber <= 0 || wordNumber > lines[lineNumber-1].size()) {
		throw std::out_of_range("해당 위치에 단어가 존재하지 않습니다.");
	}
}

void TextEditor::AdjustAfterInsertionOfLine(int lineNumber) {
	if (this->lines[lineNumber - 1].getByteLength() <= 75) {
		return;
	} else {
		if (lineNumber == this->lines.size()) {
			Line* newLine = new Line();
			this->lines.push_back(*newLine);
			delete newLine;
		}

		Line& presentLine = lines[lineNumber - 1];
		Line& nextLine = lines[lineNumber];

		if (lineNumber + 1 <= this->lines.size()) {
			while (presentLine.getByteLength() > 75) {
				nextLine.insertWord(0, presentLine.get(presentLine.size() - 1));
				presentLine.removeWord(presentLine.size() - 1); // 마지막 단어 제거
			}
			AdjustAfterInsertionOfLine(lineNumber + 1);
		}
	}	
}

void TextEditor::showPreviousPage() {
	if (this->startLine == 0) {
		throw std::out_of_range("현재 페이지가 첫 페이지입니다.");
	}
	else if (this->startLine - 20 < 0) {
		this->startLine = 0;
		this->endLine = 20;
	}
	else {
		this->startLine -= 20;
		this->endLine -= 20;
	}

}

void TextEditor::showNextPage() {
	if (this->endLine == this->lines.size()) {
		throw std::out_of_range("현재 페이지가 마지막 페이지입니다.");
	}
	else if (this->endLine + 20 > lines.size()) {
		this->endLine = lines.size();
		this->startLine = this->endLine - 20;
	}
	else {
		this->startLine += 20;
		this->endLine += 20;
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

