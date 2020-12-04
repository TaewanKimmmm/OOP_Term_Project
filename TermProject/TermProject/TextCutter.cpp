#include "TextCutter.h"

std::string TextCutter::makeLines() {
	std::string wholeText = loadTextFile();
	std::vector<std::string> result = split(wholeText, ' ');
	for (int i = 0; i < result.size(); i++) {
		std::cout << result[i] << " " << std::endl;
	}

	return wholeText;
}

std::string TextCutter::loadTextFile() {
	std::ifstream in("test.txt");;
	std::string wholeText;

	if (in.is_open()) {
		in.seekg(0, std::ios::end);
		int size = in.tellg();
		wholeText.resize(size);
		in.seekg(0, std::ios::beg);
		in.read(&wholeText[0], size);
	}
	else {
		std::cout << "파일을 찾을 수 없습니다!" << std::endl;
	}
	return wholeText;
}

std::vector<std::string> TextCutter::split(std::string input, char delimiter) {
	std::vector<std::string> answer;
	std::stringstream ss(input);
	std::string temp;

	while (getline(ss, temp, delimiter)) {
		answer.push_back(temp);
	}

	return answer;
}

