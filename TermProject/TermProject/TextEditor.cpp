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
	for (int i = this->startLine; i < this->endLine; i++) { // 0 ~ 19
		std::cout << std::setw(2) << std::right << i + 1 << "| ";
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
			trimmedInput = trimParenthesisFromUserInput(userInput);
		}

		switch (userInput[0]) {
			case 'i':
				insert(trimmedInput);
				break;
			case 'd':
				remove(trimmedInput);
				break;
			case 'c':
				change(trimmedInput);
				break;
			case 's':
				search(trimmedInput);
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

void TextEditor::search(std::string trimmedInput) {

	bool isExist = false;
	
	for (int i = 0; i < lines.size(); i++) {
		if (lines[i].size() != lines[i].searchWord(trimmedInput)) {
			isExist = true;
			startLine = i;
			if (this->startLine + 20 > lines.size()) {
				this->endLine = lines.size();
			}
			else {
				this->endLine = this->startLine + 20;
			}
			break;
		}
	}

	if (isExist == false) {
		throw std::exception("존재하지 않는 단어입니다.");
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

	validateLineWord(lineNumber, wordNumber);

	Line& selectedLine = lines[lineNumber-1];
	selectedLine.insertWord(wordNumber, result[2]);
	adjustAfterInsertionOfWord(lineNumber);
}

void TextEditor::remove(std::string trimmedInput) {
	std::vector<std::string> result = TextCutter::split(trimmedInput, ',');
	if (result.size() != 2) {
		throw std::exception("파라미터는 2개 입력해주세요");
	}

	int lineNumber = 0;
	int wordNumber = 0;

	std::stringstream lineInt(result[0]);
	std::stringstream wordInt(result[1]);

	lineInt >> lineNumber;
	wordInt >> wordNumber;

	validateLineWord(lineNumber, wordNumber);

	Line& selectedLine = lines[lineNumber - 1];
	selectedLine.removeWord(wordNumber - 1); //현재 라인에서 단어 지웠음
	adjustAfterDeletionOfWord(lineNumber); // 다음 라인부터 조정 시작..
}

void TextEditor::change(std::string trimmedInput) {
	std::vector<std::string> result = TextCutter::split(trimmedInput, ',');
	if (result.size() != 2) {
		throw std::exception("파라미터는 2개 입력해주세요");
	}

	std::string target = result[0];
	std::string manufactured = result[1];

	bool isExist = false;

	for (int i = 0; i < lines.size(); i++) {
		int targetIndex = lines[i].searchWord(target);
		if (lines[i].size() != targetIndex) {
			isExist = true;
			Line& presentLine = lines[i];

			presentLine.removeWord(targetIndex);
			presentLine.insertWord(targetIndex, manufactured);

			if (target.length() > manufactured.length()) {
				adjustAfterDeletionOfWord(i+1);
			}
			else if (target.length() < manufactured.length()) {
				adjustAfterInsertionOfWord(i+1);
			}
		}
	}

	if (isExist == false) {
		throw std::exception("존재하지 않는 단어입니다.");
	}
}

void TextEditor::adjustAfterDeletionOfWord(int lineNumber) { //lineNumber - 1이 현재 라인임.. 
	if (lineNumber < lines.size()) { // 다음 라인이 존재한다면
		Line& presentLine = lines[lineNumber - 1]; //현재 라인
		Line& nextLine = lines[lineNumber]; // 다음 라인

		while (presentLine.getByteLength() + nextLine.get(0).length() + 1 <= 75) {
			std::string fuck = nextLine.get(0);
			presentLine.insertWord(presentLine.size(), fuck);
			nextLine.removeWord(0);
			if (nextLine.size() == 0) {
				this->lines.erase(lines.begin() + lineNumber);
				if (this->endLine == this->lines.size() + 1) {
					this->startLine -= 1;
					this->endLine -= 1;
				}
				break;
			}
		}
		adjustAfterDeletionOfWord(lineNumber + 1);
	}
	else if (lineNumber == lines.size()){
		Line& presentLine = lines[lineNumber - 1];
		if (presentLine.size() == 0) {
			this->lines.erase(lines.begin() + lineNumber-1);
			this->startLine -= 1;
			this->endLine -= 1;
		}
	}
}

void TextEditor::validateLineWord(int lineNumber, int wordNumber) {
	if (lineNumber <= startLine || lineNumber > endLine) {
		throw std::out_of_range("현재 출력창에 존재하지 않는 줄 번호입니다.");
	}
	if (wordNumber <= 0 || wordNumber > lines[lineNumber-1].size()) {
		throw std::out_of_range("해당 위치에 단어가 존재하지 않습니다.");
	}
}

void TextEditor::adjustAfterInsertionOfWord(int lineNumber) {
	if (this->lines[lineNumber - 1].getByteLength() <= 75) {
		return;
	} else {
		if (lineNumber == this->lines.size()) {
			Line* newLine = new Line();
			this->lines.push_back(*newLine);
			if (this->endLine == this->lines.size()-1) {
				this->startLine += 1;
				this->endLine += 1;
			}
			delete newLine;
		}

		Line& presentLine = lines[lineNumber - 1];
		Line& nextLine = lines[lineNumber];

		if (lineNumber + 1 <= this->lines.size()) {
			while (presentLine.getByteLength() > 75) {
				nextLine.insertWord(0, presentLine.get(presentLine.size() - 1));
				presentLine.removeWord(presentLine.size() - 1); // 마지막 단어 제거
			}
			adjustAfterInsertionOfWord(lineNumber + 1);
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

