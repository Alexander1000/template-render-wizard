#include <trw.h>
#include <syntax-tree-lib.h>
#include <io-buffer.h>

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

        if (*curSymbol == ':') {
            // todo: switch on next lexer mode
            return new Token::DoubleDot(this->position->getLine(), this->position->getColumn());
        }

        auto ioWriter = new IOBuffer::IOMemoryBuffer(64);
        while (curSymbol != nullptr) {
            if (this->isWord(curSymbol)) {
                ioWriter->write(curSymbol, 1);
            } else {
                this->pushStackChar(curSymbol);
                break;
            }
            curSymbol = this->getNextChar();
        }

        return new Token::IncludeWithKey(this->position->getLine(), this->position->getColumn(), ioWriter);
    }
}
