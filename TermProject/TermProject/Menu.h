#pragma once

#include <string>
#include <iostream>

class Menu {

private:
	static const std::string menu;
	Menu();

public:
	static void printMenu();
};