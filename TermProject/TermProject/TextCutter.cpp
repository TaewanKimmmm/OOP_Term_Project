#include "TextCutter.h"

std::vector<Line> TextCutter::makeLines() {
	std::vector<std::string> words = makeWords();
	std::vector<Line> lines;
	
	int wordLength = 0;
	int wordCount = 0;
	int start = 0;
	int end = 0;

	for (int i = 0; i < words.size(); i++) {
		wordLength += words[i].length();
		wordCount += 1;

		if (wordLength + wordCount - 1 > 75) {
			end = i-1;
			lines.push_back(Line(std::vector<std::string>(words.begin() + start, words.begin() + end + 1)));
			start = i;
			wordLength = words[i].length();
			wordCount = 1;
		}
		else if (wordLength + wordCount - 1 == 75) {
			end = i;
			lines.push_back(Line(std::vector<std::string>(words.begin() + start, words.begin() + end + 1)));
			start = i+1;
			wordLength = 0;
			wordCount = 0;
		}
		
	}

	return lines;
}

std::vector<std::string> TextCutter::makeWords() {
	std::string wholeText = loadTextFile();
	std::vector<std::string> result = split(wholeText, ' ');

	return result;
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
	} else {
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

