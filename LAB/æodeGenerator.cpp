#include "CodeGenerator.h"

CodeGenerator::CodeGenerator(Tree* root, ofstream* fout)
{
	this->root = root;
	this->fout = fout;

	*fout << "push rbp\nmov rbp, rsp\n" << endl;
	program(root->getLastChild());
	*fout << "\npop rbp\nret" << endl;
}

void CodeGenerator::program(Tree* node)
{
	for (auto it : node->children)
	{
		
		if (it->notTerminal == "<block>")
		{
			block(it);
			
		}
	}
}

void CodeGenerator::block(Tree* node)
{
	for (auto it : node->children)
	{
		if (it->notTerminal == "<declarations>")
		{
			label_Declarations(it->children[0]);
			
		}
		if (it->notTerminal == "<statements-list>")
		{
			statements_list(it);
			
		}
	}
}

void CodeGenerator::label_Declarations(Tree* node)
{
	for (auto it : node->children)
	{
		if (it->notTerminal == "<unsigned-integer>")
		{
			label_unint(it);
			continue;
		}
		if (it->notTerminal == "<labels-list>")
		{
			labels_List(it);
			continue;
		}
	}
}

void CodeGenerator::labels_List(Tree* node)
{
	for (auto it : node->children)
	{
		if (it->notTerminal == "<unsigned-integer>")
		{
			label_unint(it);
			continue;
		}
		if (it->notTerminal == "<labels-list>")
		{
			labels_List(it);
			continue;
		}
	}
}

void CodeGenerator::label_unint(Tree* node)
{
	label = stoi(node->children[0]->terminal);
	for (size_t i = 0; i < labels.size(); i++)
	{
		if (label == labels[i])
		{
			
			*fout << "ERROR: (row: " << node->children[0]->row << ", colm: " << node->children[0]->column << "). Label '" << label << "' was declared";
			fout->close();
			exit(0);
		}
	}
	labels.push_back(label);
}






void CodeGenerator::statements_list(Tree* node)
{
	for (auto it : node->children)
	{
		if (it->notTerminal == "<statement>")
		{
			statment_flag = 1;
			statement(it);
			
		}
		if (it->notTerminal == "<statements-list>")
		{
			statements_list(it);
			
		}
		if (it->notTerminal == "<empty>")
		{
			if (statment_flag == 0)
			{
				*fout << "nop" << endl;
			}
		}
		
	}
}

void CodeGenerator::statement(Tree* node)
{
	for (auto it : node->children)
	{
		if (node->children[0]->terminal == "GOTO" && GOTO_flag == 1)
		{
			GOTO_flag = 0;
			continue;
		}
		if (it->notTerminal == "<unsigned-integer>")
		{
			tmp = unsigned_Integer(it);
			*fout << tmp << ": ";
			labels_used.push_back(tmp);
			it = node->children[2];
			statement(it);
			continue;
		}
		if (it->terminal == "GOTO")
		{
			GOTO_flag = 1;
			it = node->children[1];
			int buff = GOTO_unsinden_integer(it);
			*fout << "jmp " << buff << endl;
			continue;
		}
		
		if (it->terminal=="LINK")
		{
			*fout << "ERROR: (row: " << node->children[0]->row << ", colm: " << node->children[0]->column << "). " << node->children[0]->terminal << "cannot be used without SIGNAL" << endl;
			fout->close();
			exit(0);

		}
		if (it->terminal == "IN")
		{
			*fout << "ERROR: (row: " << node->children[0]->row << ", colm: " << node->children[0]->column << ").  " << node->children[0]->terminal << "cannot be used without LINK " << endl;
			fout->close();
			exit(0);

		}
		if (it->terminal == "OUT")
		{
			*fout << "ERROR: (row: " << node->children[0]->row << ", colm: " << node->children[0]->column << ")." << node->children[0]->terminal << "cannot be used without LINK" << endl;
			fout->close();
			exit(0);

		}
		
	}
}

int CodeGenerator::unsigned_Integer(Tree* node)
{
	for (auto it : labels)
	{
		if (it == stoi(node->children[0]->terminal))
		{
			return it;
		}
	}
	
	*fout << "ERROR: (row: " << node->children[0]->row << ", colm: " << node->children[0]->column << "). Label " << node->children[0]->terminal << " was not declareted";
	fout->close();
	exit(0);
}

int CodeGenerator::GOTO_unsinden_integer(Tree* node)
{
	for (auto it : labels)
	{
		if (it == stoi(node->children[0]->terminal))
		{
			for (auto it2 : labels_used)
			{
				if (it == it2)
				{
					return it;
				}
			}
			
			*fout << "ERROR: (row: " << node->children[0]->row << ", colm: " << node->children[0]->column << "). Label " << node->children[0]->terminal << " was not used";
			fout->close();
			exit(0);
		}
	}
	
	*fout << "ERROR: (row: " << node->children[0]->row << ", colm: " << node->children[0]->column << "). Label " << node->children[0]->terminal << " was not declareted";
	fout->close();
	exit(0);
}
