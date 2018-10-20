#pragma once
#ifndef LEXICALANALYZER_H
#define LEXICALANALYZER_H
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <string>
#include "Token.h"
#include<vector>
using namespace std;


class LexicalAnalyzer
{
public:
	LexicalAnalyzer(std::vector<string> input);
	~LexicalAnalyzer();

	void tokenizer();
	void tokenizer_();//   review

	void classifier();
	void classifier_(); 

	string isID(string word, int num);
	string isID_(string &word, int num);

	bool isInt(string word);
	bool isFloat(string word);
	bool isChar(string word);
	bool isString(string word);
	bool isPunctuator(string word);
	bool isIndent(string word);
	string isOperator(string word);
    bool isOperator_(string word); //   review

	string isKeyword(string word);


private:
	//string str;
	vector<string> input;
	string line;
};

#endif