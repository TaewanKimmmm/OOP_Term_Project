#include "TextCutter.h"

std::string TextCutter::loadTextFile() {
	std::ifstream in("test.txt");;
	std::string wholeText;

	if (in.is_open()) {
		in.seekg(0, std::ios::end);
		int size = in.tellg();
		wholeText.resize(size);
		in.seekg(0, std::ios::beg);
		in.read(&wholeText[0], size);
		//std::cout << s << std::endl;
	}
	else {
		std::cout << "파일을 찾을 수 없습니다!" << std::endl;
	}
	return wholeText;
}

std::string TextCutter::makeLines() {
	std::cout << this->loadTextFile() << std::endl;
	
}