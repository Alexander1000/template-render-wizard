#include <trw/stream.h>
#include <io-buffer.h>
#include <trw/token.h>

namespace TemplateRenderWizard
{
    Stream::Stream(IOBuffer::CharStream *charStream)
    {
        this->charStream = charStream;
        this->mode = StreamMode::PlainText;
    }

    Token* Stream::getNextToken() {
        char* curSymbol = this->getNextChar();
        if (curSymbol == NULL) {
            return NULL;
        }

        Token* token = NULL;
        return token;
    }

    char* Stream::getNextChar() {
        return this->charStream->getNext();
    }
}
