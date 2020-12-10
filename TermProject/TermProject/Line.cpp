#include "Line.h"

Line::Line() {
	this->byteLength = 0;
}

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
	this->byteLength += word.length() + 1;
}

void Line::removeWord(int idx) {

	this->byteLength -= (words[idx].length() + 1);
	std::vector<std::string>::iterator it = this->words.begin();
	this->words.erase(words.begin() + idx);
}

int Line::size() {
	return this->words.size();
}

std::string Line::get(int index) {
	return this->words[index];
}

int Line::getByteLength() {
	return this->byteLength;
}

void Line::print() {
	for (int i = 0; i < words.size(); i++) {
		std::cout << words[i] << " ";
	}
	std::cout << std::endl;
}

