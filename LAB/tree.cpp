#include "tree.h"

Tree::Tree(string notTerminal, string terminal, int depth, int code,int row,int column)
{
	this->notTerminal = notTerminal;
	this->terminal = terminal;
	this->depth = depth;
	this->lexemCode = code;
	this->row = row;
	this->column = column;
}

Tree* Tree::getLastChild()
{
	return this->children[this->children.size() - 1];

}

void Tree::addNotTerm(string notTerminal, int code)
{
	this->children.push_back(new Tree(notTerminal, "", this->depth + 1, code));
}

void Tree::addTerm(Lexer::Token lexem)
{
	this->children.push_back(new Tree("", lexem.name, this->depth + 1, lexem.code,lexem.row,lexem.colm));
}

void Tree::output(ofstream* fout)
{
	string name;
	if (this->terminal.empty()) {
		name = this->notTerminal;
	}
	else
	{
		name = std::to_string(this->lexemCode) + " " + this->terminal;

	}
	string spaces = "";
	for (int i = 0; i < this->depth; i++) {
		spaces += "..";
	}
	*fout << spaces << name << endl;
	if (this->lexemCode > 0) return;
	for (auto& it : this->children) {
		it->output(fout);
	}

}

