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

        if (*curSymbol == ',') {
            this->switchToPreviousMode();
            return new Token::Comma(this->position->getLine(), this->position->getColumn());
        }

        auto ioWriter = new IOBuffer::IOMemoryBuffer(64);
        while (curSymbol != nullptr) {
            if (*curSymbol != ',') {
                ioWriter->write(curSymbol, 1);
            } else {
                this->pushStackChar(curSymbol);
                break;
            }
            curSymbol = this->getNextChar();
        }

        return new Token::ExpressionValue(this->position->getLine(), this->position->getColumn(), ioWriter);
    }
}
