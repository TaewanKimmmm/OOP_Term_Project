#include "ConsoleMessage.h"

const std::string ConsoleMessage::defaultMessage = "(�ָܼ޽���)";

void ConsoleMessage::printDefaultMessage() {
	std::cout << defaultMessage << std::endl;
	OutputView::printBorderLine();
}


