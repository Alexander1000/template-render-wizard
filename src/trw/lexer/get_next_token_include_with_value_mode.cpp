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

        if (*curSymbol == '}') {
            this->switchToPreviousMode();
            return this->getNextTokenIncludeWithMode();
        }

        if (*curSymbol == ',') {
            this->switchToPreviousMode();
            return new Token::Comma(this->position->getLine(), this->position->getColumn());
        }

        if (*curSymbol == '(') {
            return new Token::RoundBracketOpen(this->position->getLine(), this->position->getColumn());
        }

        if (*curSymbol == ')') {
            return new Token::RoundBracketClose(this->position->getLine(), this->position->getColumn());
        }

        if (*curSymbol == '=' || *curSymbol == '>' || *curSymbol == '<' || *curSymbol == '!') {
            auto ioWriter = new IOBuffer::IOMemoryBuffer(4);
            ioWriter->write(curSymbol, 1);

            char* nextSymbol = this->getNextChar();
            if (nextSymbol == nullptr) {
                return nullptr;
            }

            if (*nextSymbol == '=') {
                ioWriter->write(nextSymbol, 1);
            }

            return new Token::Compare(this->position->getLine(), this->position->getColumn(), ioWriter);
        }

        if (*curSymbol == '*' || *curSymbol == '/') {
            auto ioWriter = new IOBuffer::IOMemoryBuffer(4);
            ioWriter->write(curSymbol, 1);
            return new Token::MathOperationHighPriority(this->position->getLine(), this->position->getColumn(), ioWriter);
        }

        if (*curSymbol == '+' || *curSymbol == '-' || *curSymbol == '%') {
            auto ioWriter = new IOBuffer::IOMemoryBuffer(4);
            ioWriter->write(curSymbol, 1);
            return new Token::MathOperation(this->position->getLine(), this->position->getColumn(), ioWriter);
        }

        auto ioWriter = new IOBuffer::IOMemoryBuffer(64);
        while (curSymbol != nullptr) {
            if (this->isWord(curSymbol) || this->isDigit(curSymbol)) {
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
