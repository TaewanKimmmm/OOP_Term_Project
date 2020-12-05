#include "Menu.h"

const std::string Menu::menu = "n: 다음페이지, p:이전페이지, i:삽입, d:삭제, c:변경, s:찾기, t:저장후종료";

void Menu::printMenu() {
	std::cout << menu << std::endl;
}