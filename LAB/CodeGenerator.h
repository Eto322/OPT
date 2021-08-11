#pragma once
#include "tree.h"

class CodeGenerator {

private:
	Tree* root;
	ofstream* fout;
	void program(Tree* node);
	vector <int> labels;
	vector <int> labels_used;
	string procedureName;
	int label, statment_flag = 0;
	int tmp = 0;
	int GOTO_flag = 0;
	
	

	void block(Tree* node);
	void label_Declarations(Tree* node);
	void labels_List(Tree* node);
	void label_unint(Tree* node);
	void statements_list(Tree* node);
	void statement(Tree* node);
	int unsigned_Integer(Tree* node);
	int GOTO_unsinden_integer(Tree* node);

public:
	CodeGenerator(Tree* root, ofstream* fout);
};
