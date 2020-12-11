#include "ConsoleMessage.h"

//const std::string ConsoleMessage::defaultMessage = "(�ָܼ޽���)";

ConsoleMessage::ConsoleMessage() {
	this->message = "(�ܼ� �޽���)";
}

void ConsoleMessage::printMessage() {
	std::cout << this->message << std::endl;
	OutputView::printBorderLine();
}

void ConsoleMessage::setMessage(std::string inputMessage)
{
	this->message = inputMessage;
}


