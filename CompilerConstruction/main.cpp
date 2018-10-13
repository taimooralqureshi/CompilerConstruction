
#include<iostream>
#include<fstream>
#include <string>
#include <vector>
#include "LexicalAnalyzer.h"
using namespace std;

vector<string> fileInput;

int main() {
	ifstream file("text.txt", ifstream::in);
	if (file.is_open())
	{
		string line;
		while (getline(file, line))
			fileInput.push_back(line.c_str());
		file.close();
	}

	LexicalAnalyzer lexzer(fileInput);
	lexzer.tokenizer_();
	//lexzer.tokenizer();
	lexzer.classifier();

	system("PAUSE");
	return 0;
}