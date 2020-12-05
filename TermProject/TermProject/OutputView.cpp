#include "OutputView.h"

const std::string OutputView::menu = "n: 다음페이지, p:이전페이지, i:삽입, d:삭제, c:변경, s:찾기, t:저장후종료";

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