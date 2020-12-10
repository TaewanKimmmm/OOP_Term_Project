#pragma once
#include <string>
#include <iostream>
#include "OutputView.h"

class ConsoleMessage {
private:
	std::string message;

public:
	ConsoleMessage();
	void printMessage();
	void setMessage(std::string inputMessage);
};