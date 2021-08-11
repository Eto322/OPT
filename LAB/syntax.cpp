#include "syntax.h"
#include "CodeGenerator.h"

Syntax::Syntax(ofstream* out, vector<Lexer::Token> lexems) :
	out(out),
	lexems{ lexems }
{signalProgram(); }

void Syntax::scan(string expected)
{
	if (iterator != lexems.end())
	{
		buffer = *iterator++;
	}
	else
	{
		bool tmp = lexems.empty();
		if (tmp);
		{
			*out << "Syntax: Error (file is empty)" << endl;
			out->close();
			exit(0);
		}
		iterator--;
		*out << "Syntax: Error(line: " << iterator->row << " position: " << iterator->colm + iterator->name.length() << ") after '" << iterator->name << "' expected '" << expected << "'" << endl;
		out->close();
		exit(0);
	}
}

void Syntax::signalProgram()
{
	root = new Tree("<signal-program>", "", 0);
	scan("PROGRAM");
	root->addNotTerm("<program>");
	program(root->getLastChild());
	//root->output(out);
	CodeGenerator a(root, out);

}

void Syntax::program(Tree* node)
{

	if (buffer.code == 401)//program
	{
		node->addTerm(buffer);
		scan("procedure idintifier");
		node->addNotTerm("<procedure-identifier>");
		procedureIdentifier(node->getLastChild());
		scan(";");
		if (buffer.code == ';')
		{
			node->addTerm(buffer);
			scan("block");
			node->addNotTerm("<block>");
			block(node->getLastChild());
			scan(".");
			if (buffer.code == '.')
			{
				node->addTerm(buffer);
			}
			else
			{
				error(".");
			}
		}
		else
		{
			error(";");
		}
	}
	else
	{
		error("PROGRAM");
	}
}

void Syntax::block(Tree* node)
{
	node->addNotTerm("<declarations>");
	declarations(node->getLastChild());
	//scan("BEGIN");
	if (buffer.code == 402)//begin
	{
		node->addTerm(buffer);
		scan("statements-list");
		node->addNotTerm("<statements-list>");
		statementsList(node->getLastChild());
		//scan("END");
		if (buffer.code == 403)//end
		{
			node->addTerm(buffer);
		}
		else
		{
			error("END");
		}
	}
	else
	{
		error("BEGIN");
	}
}

void Syntax::declarations(Tree* node)
{
	node->addNotTerm("<label-declarations>");
	labelDeclarations(node->getLastChild());
}

void Syntax::labelDeclarations(Tree* node)
{

	//scan("LABEL");
	if (buffer.code == 404)//label
	{
		node->addTerm(buffer);
		scan("unsigned integer");
		node->addNotTerm("<unsigned-integer>");
		unsignedInteger(node->getLastChild());
		scan("labels list");
		node->addNotTerm("<labels-list>");
		labelsList(node->getLastChild());
		//scan(";");
		if (buffer.code == ';')
		{
			node->addTerm(buffer);
			scan("BEGIN");
		}
		else
		{
			error(";");
		}
	}
	else
	{
		node->addNotTerm("<empty>");
	}
}

void Syntax::labelsList(Tree* node)
{

	if (buffer.code == ',')
	{
		node->addTerm(buffer);
		scan("unsigned integer");
		node->addNotTerm("<unsigned-integer>");
		unsignedInteger(node->getLastChild());
		scan("labels list");
		node->addNotTerm("<labels-list>");
		labelsList(node->getLastChild());
	}
	else
	{
		node->addNotTerm("<empty>");
	}
}

void Syntax::statementsList(Tree* node)
{
	node->addNotTerm("<statement>");
	if (statement(node->getLastChild()))
	{
		node->addNotTerm("<statements-list>");
		statementsList(node->getLastChild());
	}
	else
	{
		node->children.pop_back();
		node->addNotTerm("<empty>");
	}
}

int Syntax::statement(Tree* node)
{

	if (buffer.code > 500 && buffer.code < 1001)
	{
		node->addNotTerm("<unsigned-integer>");
		unsignedInteger(node->getLastChild());
		scan(":");
		if (buffer.code == ':')
		{
			node->addTerm(buffer);
			scan("statment or END");
			node->addNotTerm("<statement>");
			statement(node->getLastChild());
			return 1;

		}
		else
		{
			error(":");
		}

	}
	else
	{
		switch (buffer.code)
		{
		case 405://goto
			node->addTerm(buffer);
			scan("unsigned integer");
			node->addNotTerm("<unsigned-integer>");
			unsignedInteger(node->getLastChild());
			scan(";");
			if (buffer.code == ';')
			{
				node->addTerm(buffer);
				scan("statment or END");
				return 1;
			}
			else
			{
				error(";");
			}
			break;
		case 406://link
			node->addTerm(buffer);
			scan("variable identifier");
			node->addNotTerm("<variable-identifier>");
			variableIdentifier(node->getLastChild());
			scan(",");
			if (buffer.code == ',')
			{
				node->addTerm(buffer);
				scan("unsigned integer");
				node->addNotTerm("<unsigned-integer>");
				unsignedInteger(node->getLastChild());
				scan(";");
				if (buffer.code == ';')
				{
					node->addTerm(buffer);
					scan("statment or END");
					return 1;
				}
				else
				{
					error(";");
				}
			}
			else
			{
				error(",");
			}
			break;
		case 407://in
			node->addTerm(buffer);
			scan("unsigned-integer");
			node->addNotTerm("<unsigned-integer>");
			unsignedInteger(node->getLastChild());
			scan(";");
			if (buffer.code == ';')
			{
				node->addTerm(buffer);
				scan("statment or END");
				return 1;
			}
			else
			{
				error(";");
			}
			break;
			node->addTerm(buffer);
			scan("");
		case 408://out
			node->addTerm(buffer);
			scan("unsigned-integer");
			node->addNotTerm("<unsigned-integer>");
			unsignedInteger(node->getLastChild());
			scan(";");
			if (buffer.code == ';')
			{
				node->addTerm(buffer);
				scan("statment or END");
				return 1;
			}
			else
			{
				error(";");
			}
			break;
		default:
			return 0;
		}
	}
}

void Syntax::variableIdentifier(Tree* node)
{
	node->addNotTerm("<identifier>");
	identifier(node->getLastChild());

}

void Syntax::procedureIdentifier(Tree* node)
{
	node->addNotTerm("<identifier>");
	identifier(node->getLastChild());
}

void Syntax::identifier(Tree* node)
{
	if (buffer.code > 1000)
	{
		node->addTerm(buffer);
	}
	else
	{
		error("identifier");
	}
}

int Syntax::unsignedInteger(Tree* node)
{

	if (buffer.code > 500 && buffer.code < 1001)
	{
		node->addTerm(buffer);
		return 1;
	}
	else
	{
		error("unsigned integer");
	}
}

void Syntax::error(string expected)
{
	if (expected == "PROGRAM")
	{
		*out << "Syntax: Error(line: 1 position: 1) at the beginning of the program expected 'PROGRAM'" << endl;
	}
	else
	{
		iterator = iterator - 2;
		*out << "Syntax: Error(line: " << iterator->row << " position: " << iterator->colm + iterator->name.length() << ") after '" << iterator->name << "' expected '" << expected << "'" << endl;
	}
	out->close();
	exit(0);
}

