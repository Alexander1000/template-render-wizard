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

    Token::Token* Stream::getNextToken() {
        char* curSymbol = this->getNextChar();
        if (curSymbol == NULL) {
            return NULL;
        }

        Token::Token* token = NULL;
        IOBuffer::IOMemoryBuffer* ioWriter = NULL;

        switch (this->mode) {
            case StreamMode::PlainText: {
                if (*curSymbol == '{') {
                    char *nextChar = this->getNextChar();
                    if (nextChar == NULL) {
                        // todo: throw exception?
                        return NULL;
                    }
                    if (*nextChar == '{') {
                        ioWriter = new IOBuffer::IOMemoryBuffer(3);
                        ioWriter->write(curSymbol, 1);
                        ioWriter->write(nextChar, 1);
                        token = new Token::OpenTagValue();
                    }
                    // parse token
                }

                // parse plain text
                break;
            }
        }

        return token;
    }

    char* Stream::getNextChar() {
        return this->charStream->getNext();
    }
}
