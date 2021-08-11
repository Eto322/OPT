#include "lexer.h"
#include "syntax.h"

int main(int argc, char* argv[])
{

    if (argc != 2)
        cout << "Error" << endl;
    else
    {

        ifstream fInput(argv[1] + string("//input.sig"));
        ofstream fOutputut(argv[1] + string("//generated.txt", ios_base::out | ios_base::trunc));
        if (!fInput.is_open())
        {
            cout << "ERROR OF OPEN FILE" << endl;
            return 0;
        }
        Lexer lex(&fInput, &fOutputut);
        Syntax synt(&fOutputut, lex.getLexems());
        fInput.close();
        fOutputut.close();

    }
    return 1;

}