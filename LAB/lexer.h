
#pragma once
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <map>
#include <vector>
using namespace std;

class Lexer {
public:
	Lexer(ifstream* fInput, ofstream* fOutput);
	struct Token
	{
		string name;
		int code;
		int row;
		int colm;
	};
	Token token;
	vector<Token> getLexems();
private:
	map<string, int> identifiers;
	map<string, int> separators;
	map<string, int> constants;
	map<string, int> keywords
	{ {"PROGRAM", 401},
		{"BEGIN", 402},
		{"END", 403},
		{"LABEL", 404},
		{"GOTO", 405},
		{"LINK", 406},
		{"IN", 407},
		{"OUT", 408}
	};
	int symbolCategory[128];
	vector<Token> lexems;
	int row = 1;
	int col = 0;
	int start_Row;
	int start_Col;
	char symbol;
	int lexemCode;
	int symbolCat;
	ifstream* finput;
	ofstream* foutput;
	void lexer();
	void init();
	void gets();
	void setStruct(int code, string name);
	void fileOut();
	void err(string lexem);


};
