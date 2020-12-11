#include "ConsoleMessage.h"

//const std::string ConsoleMessage::defaultMessage = "(콘솔메시지)";

ConsoleMessage::ConsoleMessage() {
	this->message = "(콘솔 메시지)";
}

void ConsoleMessage::printMessage() {
	std::cout << this->message << std::endl;
	OutputView::printBorderLine();
}

void ConsoleMessage::setMessage(std::string inputMessage)
{
	this->message = inputMessage;
}


