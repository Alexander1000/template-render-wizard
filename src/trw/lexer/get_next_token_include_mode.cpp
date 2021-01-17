#include <trw.h>
#include <io-buffer.h>
#include <cstring>

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

        bool quoted = false;
        if (*curSymbol == '"') {
            quoted = true;
            curSymbol = this->getNextChar();
        }
        bool escape = false;

        auto ioWriter = new IOBuffer::IOMemoryBuffer(64);
        while (curSymbol != nullptr) {
            if (quoted && !escape && *curSymbol == '\\') {
                escape = true;
                continue;
            }
            if (quoted && *curSymbol == '"') {
                if (escape) {
                    escape = false;
                    ioWriter->write(curSymbol, 1);
                    curSymbol = this->getNextChar();
                    continue;
                }
                break;
            }
            if (!quoted && *curSymbol == 0x20) {
                break;
            }
            ioWriter->write(curSymbol, 1);
            curSymbol = this->getNextChar();
        }

        if (ioWriter->length() == 4) {
            INIT_CHAR_STRING(strValue, 5);
            ioWriter->read(strValue, 4);
            if (strcmp(strValue, "with") == 0) {
                return new Token::Keyword(this->position->getLine(), this->position->getColumn(), ioWriter);
            }
        }

        return new Token::FilePath(this->position->getLine(), this->position->getColumn(), ioWriter);
    }
}
