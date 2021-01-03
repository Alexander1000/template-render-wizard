#include <trw.h>

namespace TemplateRenderWizard::Lexer
{
    SyntaxTree::Token::Token* Lexer::getNextTokenIncludeMode()
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

        if (*curSymbol == '%') {
            char* nextSymbol = this->getNextChar();
            if (nextSymbol == nullptr) {
                return nullptr;
            }
            if (*nextSymbol == '}') {
                this->switchToPreviousMode(); // <- switch on control mode
                this->switchToPreviousMode(); // <- switch on parent mode
                return new Token::CloseControlTag(this->position->getLine(), this->position->getColumn());
            }
            this->pushStackChar(nextSymbol);
        }

        return nullptr;
    }
}
