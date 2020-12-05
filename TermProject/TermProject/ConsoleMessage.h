#pragma once
#include <string>
#include <iostream>
#include "OutputView.h"

class ConsoleMessage {
private:
	ConsoleMessage();
	static const std::string defaultMessage;

public:
	static void printMessage();
};