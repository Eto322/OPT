#pragma once
#include "lexer.h"
#include "tree.h"
using namespace std;

class Syntax {
public:
	Syntax(ofstream* out, vector<Lexer::Token> lexems);
private:
	ofstream* out;
	vector<Lexer::Token> lexems;
	Lexer::Token buffer;
	Tree* root;
	vector<Lexer::Token>::iterator iterator = lexems.begin();
	void scan(string expected);
	void signalProgram();
	void program(Tree* node);
	void block(Tree* node);
	void declarations(Tree* node);
	void labelDeclarations(Tree* node);
	void labelsList(Tree* node);
	void statementsList(Tree* node);
	int statement(Tree* node);
	void variableIdentifier(Tree* node);
	void procedureIdentifier(Tree* node);
	void identifier(Tree* node);
	int unsignedInteger(Tree* node);
	void error(string expected);

};

