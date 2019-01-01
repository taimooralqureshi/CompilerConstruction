
#include<iostream>
#include<fstream>
#include <string>
#include <vector>
#include "LexicalAnalyzer.h"
#include "SyntaxAndSementicAnalyzer.h"


using namespace std;

vector<string> fileInput;

int main(int argc, char** argv) {
	ifstream file("text.txt", ifstream::in);
	if (file.is_open())
	{
		string line;
		while (getline(file, line))
			fileInput.push_back(line.c_str());
		file.close();
	}
	string s = "h,e,l,l";
	
	LexicalAnalyzer lexzer(fileInput);
	lexzer.tokenizer();
	//lexzer.tokenizer();
	lexzer.classifier();

	SyntaxAndSementicAnalyzer ssa(lexzer.tokenlist);
	cout << ssa.start()<<"   result\n";
	system("PAUSE");
	return 0;
}