#include "Line.h"

Line::Line(std::vector<std::string> words) {
	this->words = words;
	this->byteLength = words.size() - 1;
	for (int i = 0; i < words.size(); i++) {
		this->byteLength += words[i].length();
	}
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
