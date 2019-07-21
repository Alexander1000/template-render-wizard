#include <trw/stream.h>
#include <io-buffer.h>
#include <trw/token.h>
#include <stack>

namespace TemplateRenderWizard
{
    Stream::Stream(IOBuffer::CharStream *charStream)
    {
        this->charStream = charStream;
        this->mode = StreamMode::PlainText;

        this->charStack = new std::stack<char*>;
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
                        ioWriter = new IOBuffer::IOMemoryBuffer(2);
                        ioWriter->write(curSymbol, 1);
                        token = new Token::PlainText();
                        return token;
                    }

                    if (*nextChar == '{') {
                        ioWriter = new IOBuffer::IOMemoryBuffer(3);
                        ioWriter->write(curSymbol, 1);
                        ioWriter->write(nextChar, 1);
                        token = new Token::OpenTagValue();
                        this->setMode(StreamMode::ValueMode);
                        return token;
                    }

                    ioWriter = new IOBuffer::IOMemoryBuffer(512);
                    ioWriter->write(curSymbol, 1);
                    ioWriter->write(nextChar, 1);
                }

                if (ioWriter == NULL) {
                    ioWriter = new IOBuffer::IOMemoryBuffer(512);
                    ioWriter->write(curSymbol, 1);
                }

                // parse plain text
                bool escape = false;

                do {
                    curSymbol = this->getNextChar();
                    if (curSymbol == NULL) {
                        break;
                    }

                    if (escape) {
                        escape = false;
                    } else {
                        if (*curSymbol == '\\') {
                            escape = true;
                            continue;
                        }

                        if (*curSymbol == '{') {
                            this->charStack->push(curSymbol);
                            break;
                        }
                    }

                    ioWriter->write(curSymbol, 1);
                } while (true);

                token = new Token::PlainText;
                break;
            }

            case StreamMode::ValueMode: {
                break;
            }
        }

        return token;
    }

    void Stream::setMode(StreamMode streamMode)
    {
        this->mode = streamMode;
    }

    char* Stream::getNextChar()
    {
        if (!this->charStack->empty()) {
            char* symbol = this->charStack->top();
            this->charStack->pop();
            return symbol;
        }

        return this->charStream->getNext();
    }
}
