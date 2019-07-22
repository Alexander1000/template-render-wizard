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
        if (curSymbol == nullptr) {
            return nullptr;
        }

        Token::Token* token = nullptr;
        IOBuffer::IOMemoryBuffer* ioWriter = nullptr;

        switch (this->mode) {
            case StreamMode::PlainText: {
                if (*curSymbol == '{') {
                    char *nextChar = this->getNextChar();
                    if (nextChar == nullptr) {
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

                if (ioWriter == nullptr) {
                    ioWriter = new IOBuffer::IOMemoryBuffer(512);
                    ioWriter->write(curSymbol, 1);
                }

                // parse plain text
                bool escape = false;

                do {
                    curSymbol = this->getNextChar();
                    if (curSymbol == nullptr) {
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
                if (*curSymbol == 0x20) {
                    // skip spaces
                    do {
                        curSymbol = this->getNextChar();
                    } while(curSymbol != nullptr && *curSymbol == 0x20);
                }

                if (curSymbol == nullptr) {
                    return nullptr;
                }

                ioWriter = new IOBuffer::IOMemoryBuffer(32);

                if (*curSymbol == '}') {
                    char* nextSymbol = this->getNextChar();
                    if (*nextSymbol == '}') {
                        // todo: return close tag value
                    }
                }
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
