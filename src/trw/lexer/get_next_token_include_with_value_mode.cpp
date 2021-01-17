#include <trw.h>
#include <syntax-tree-lib.h>

namespace TemplateRenderWizard::Lexer
{
    SyntaxTree::Token::Token* Lexer::getNextTokenIncludeWithValueMode()
    {
        char* curSymbol = this->getNextChar();
        if (curSymbol == nullptr) {
            return nullptr;
        }

        if (*curSymbol == 0x20) {
            // skip spaces
            do {
                curSymbol = this->getNextChar();
            } while(curSymbol != nullptr && *curSymbol == 0x20);
        }

        if (curSymbol == nullptr) {
            return nullptr;
        }
        
        return nullptr;
    }
}
