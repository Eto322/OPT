#pragma once
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include "lexer.h"
using namespace std;

class Tree
{
public:
	int lexemCode;
	string terminal;
	string notTerminal;
	int depth;
	vector<Tree*> children;
	Tree(string notTerminal, string terminal, int depth, int code = -1,int row=-1,int column=-1);
	Tree* getLastChild();
	void addNotTerm(string notTerminal, int code = -1);
	void addTerm(Lexer::Token lexem);
	void output(ofstream* fout);
	int column;
	int row;


};