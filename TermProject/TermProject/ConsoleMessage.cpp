#include "ConsoleMessage.h"

const std::string ConsoleMessage::defaultMessage = "(�ָܼ޽���)";

void ConsoleMessage::printMessage() {
	std::cout << defaultMessage << std::endl;
	OutputView::printBorderLine();
}


