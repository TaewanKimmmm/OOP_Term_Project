#include "Line.h"

Line::Line(std::vector<std::string> words) {
	this->words = words;
	this->byteLength = words.size() - 1;
	for (int i = 0; i < words.size(); i++) {
		this->byteLength += words[i].length();
	}
}

void Line::insertWord(int idx, std::string word) {
	std::vector<std::string>::iterator it = this->words.begin();
	this->words.insert(it +idx, word);
}

int Line::size() {
	return this->words.size();
}

std::string Line::get(int index) {
	return this->words[index];
}

void Line::print() {
	for (int i = 0; i < words.size(); i++) {
		std::cout << words[i] << " ";
	}
	std::cout << std::endl;
}

