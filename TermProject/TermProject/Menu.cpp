#include "Menu.h"

const std::string Menu::menu = "n: ����������, p:����������, i:����, d:����, c:����, s:ã��, t:����������";

void Menu::printMenu() {
	std::cout << menu << std::endl;
}