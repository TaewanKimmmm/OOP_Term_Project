#include "ConsoleMessage.h"

const std::string ConsoleMessage::defaultMessage = "(콘솔메시지)";

void ConsoleMessage::printMessage() {
	std::cout << defaultMessage << std::endl;
	OutputView::printBorderLine();
}


