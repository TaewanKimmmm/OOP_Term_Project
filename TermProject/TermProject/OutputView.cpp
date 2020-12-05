#include "OutputView.h"

const std::string OutputView::menu = "n: ����������, p:����������, i:����, d:����, c:����, s:ã��, t:����������";

void OutputView::printMenu() {
	std::cout << menu << std::endl;
	printBorderLine();
}

void OutputView::printBorderLine() {
	for (int i = 0; i < 80; i++) {
		std::cout << "-";
	}
	std::cout << std::endl;
}