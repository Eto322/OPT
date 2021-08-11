#include "lexer.h"

void Lexer::lexer()
{
    init();
    string buff = "";
    int Const = 501;
    int idn = 1001;
    int flag = 0;
    gets();
    while (!finput->eof())
    {

        buff = "";
        lexemCode = 0;
        start_Row = row;
        start_Col = col;
        switch (symbolCat)
        {
        case 0:// whitespace
            while (!finput->eof())
            {
                if (symbolCat != 0) break;
                gets();
            }
            break;
        case 1://constant
            while (!finput->eof() && symbolCat == 1)
            {
                buff += symbol;
                gets();
            }

            if (constants[buff])
            {
                lexemCode = constants[buff];
            }
            else
            {

                lexemCode = Const;
                constants[buff] = Const;
                Const++;

            }
            setStruct(lexemCode, buff);
            break;
        case 2://keyword or identifier
            while (!finput->eof() && (symbolCat == 1 || symbolCat == 2))
            {
                buff += symbol;
                gets();
            }
            if (keywords[buff])
            {
                lexemCode = keywords[buff];

            }
            else
            {
                if (identifiers[buff])
                {
                    lexemCode = identifiers[buff];

                }
                else
                {
                    lexemCode = idn;
                    identifiers[buff] = lexemCode;
                    idn++;

                }
            }
            setStruct(lexemCode, buff);
            break;
        case 3:
            buff = symbol;
            if (separators[buff])
            {
                lexemCode = separators[buff];

            }
            else
            {
                lexemCode = symbol;
                separators[buff] = symbol;
            }
            setStruct(lexemCode, buff);
            gets();
            break;
        case 5:
            flag = 0;
            gets();
            if (symbol == '*')
            {
                //gets();
                while (!finput->eof())
                {
                    gets();
                    if (symbol == '*')
                    {
                        //gets();
                        while (symbol == '*')
                        {
                            gets();
                            if (symbol == ')')
                            {
                                flag = 1;
                                break;
                            }
                        }
                    }
                    if (flag == 1)
                    {
                        break;
                    }
                    if (finput->eof())
                    {
                        //error
                        *foutput << "Lexer:Error(row " << start_Row << " position " << start_Col << ")" << " comment not closed" << endl;
                        fileOut();
                        exit(0);
                    }
                }
            }
            else
            {
                col--;
                buff = '(';
                err(buff);
                col++;

            }
            gets();
            break;
        case 6:
            //error
            buff = symbol;
            err(buff);
            gets();
            break;

        }
    }
    //fileOut();
}

void Lexer::init()
{
    for (int i = 0; i < 128; i++)// illegal
    {
        symbolCategory[i] = 6;
    }

    for (int i = 8; i <= 13; i++) // white
    {
        symbolCategory[i] = 0;
    }

    for (int i = 48; i <= 57; i++) // digit
    {
        symbolCategory[i] = 1;
    }

    for (int i = 65; i <= 90; i++) // let
    {
        symbolCategory[i] = 2;
    }
    symbolCategory[32] = 0;
    symbolCategory['('] = 5;
    symbolCategory[';'] = 3;
    symbolCategory['.'] = 3;
    symbolCategory[','] = 3;
    symbolCategory[':'] = 3;
}

void Lexer::gets()
{
    symbol = finput->get();
    symbolCat = symbolCategory[symbol];
    if (symbol == '\n')
    {
        col = 0;
        row++;
    }
    else
    {
        col++;
    }
}

void Lexer::setStruct(int code, string name)
{
    token.code = code;
    token.name = name;
    token.colm = start_Col;
    token.row = start_Row;
    lexems.push_back(token);
}

void Lexer::fileOut()
{
    for (auto& i : lexems)
    {
        *foutput << i.row << "\t" << i.colm << "\t" << i.code << "\t" << i.name << endl;
    }
}

void Lexer::err(string lexem)
{
    *foutput << "Lexer::Error(row " << row << " position " << col << ")" << " illegal symbol: " << lexem << endl;
}

vector<Lexer::Token> Lexer::getLexems()
{
    return lexems;
}

Lexer::Lexer(ifstream* fInput, ofstream* fOutput)
{
    this->finput = fInput;
    this->foutput = fOutput;
    lexer();
}
