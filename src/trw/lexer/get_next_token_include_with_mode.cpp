#include <trw.h>
#include <syntax-tree-lib.h>

namespace TemplateRenderWizard::Lexer
{
    SyntaxTree::Token::Token* Lexer::getNextTokenIncludeWithMode()
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

        if (*curSymbol == '{') {
            return new Token::OpenBrace(this->position->getLine(), this->position->getColumn());
        }

        if (*curSymbol == '}') {
            this->switchToPreviousMode();
            return new Token::CloseBrace(this->position->getLine(), this->position->getColumn());
        }

        return nullptr;
    }
}
