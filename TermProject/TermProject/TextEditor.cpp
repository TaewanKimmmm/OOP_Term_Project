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
	consoleMessage->setMessage("(�ܼ� �޽���)");
}

void TextEditor::getUserInput() { 
	std::string userInput;

	do {
		updateText();
		std::cout << "�Է� : " << std::endl;
		OutputView::printBorderLine();
		setCursorPosition(7, 25);
		std::cin >> userInput;
		processUserInput(userInput);
		system("cls");

	} while (!(userInput.length() == 1 && userInput[0] == 't'));
	
	// ���� ���� ���� �� ����
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
		this->consoleMessage->setMessage(exception + "�� �߸��� �����Դϴ�.");
	}
	catch (std::exception e) {
		std::string errorMessage = e.what();
		this->consoleMessage->setMessage("���Է� ���! " + errorMessage);
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
		throw std::exception("�Ķ���ʹ� 3�� �Է����ּ���");
	}
	if (result[2].length() > 75) {
		throw std::out_of_range("�߰��Ϸ��� �ܾ �ʹ� ��ϴ�.");
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
		throw std::out_of_range("�� ��ȣ�� 1�� 20 ���̿��� �մϴ�.");
	}
	if (wordNumber <= 0 || wordNumber > lines[lineNumber-1].size()) {
		throw std::out_of_range("�ش� ��ġ�� �ܾ �������� �ʽ��ϴ�.");
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
				presentLine.removeWord(presentLine.size() - 1); // ������ �ܾ� ����
			}
			AdjustAfterInsertionOfLine(lineNumber + 1);
		}
	}	
}

void TextEditor::showPreviousPage() {
	if (this->startLine == 0) {
		throw std::out_of_range("���� �������� ù �������Դϴ�.");
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
		throw std::out_of_range("���� �������� ������ �������Դϴ�.");
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

