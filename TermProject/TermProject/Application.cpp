#include <iostream>
#include "TextEditor.h"

int main() {
	TextEditor *myTextEditor = new TextEditor();
	myTextEditor->run();
	delete myTextEditor;
	return 0;
}