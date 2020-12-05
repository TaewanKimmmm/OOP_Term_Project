#pragma once

#include <string>
#include <iostream>

class OutputView {

private:
	static const std::string menu;
	OutputView();

public:
	static void printMenu();
	static void printBorderLine();
};