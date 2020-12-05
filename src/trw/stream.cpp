#include <trw/stream.h>
#include <io-buffer.h>
#include <trw/token.h>
#include <trw/position.h>
#include <stack>

namespace TemplateRenderWizard
{
    Stream::Stream(IOBuffer::CharStream *charStream)
    {
        this->charStream = charStream;
        this->mode = StreamMode::PlainText;

        this->charStack = new std::stack<char*>;

        this->position = new Position(0, 0);
        this->positionStack = new std::stack<Position*>;
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
                        token = new Token::OpenTagValue(this->position->getLine(), this->position->getColumn());
                        return token;
                    }

                    if (*nextChar == '{') {
                        token = new Token::OpenTagValue(this->position->getLine(), this->position->getColumn());
                        this->setMode(StreamMode::ValueMode);
                        return token;
                    }

                    if (*nextChar == '%') {
                        token = new Token::OpenControlTag(this->position->getLine(), this->position->getColumn());
                        this->setMode(StreamMode::ControlMode);
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
                            this->pushStackChar(curSymbol);
                            break;
                        }
                    }

                    ioWriter->write(curSymbol, 1);
                } while (true);

                token = new Token::PlainText(this->position->getLine(), this->position->getColumn(), ioWriter);
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

                if (*curSymbol == '}') {
                    char* nextSymbol = this->getNextChar();
                    if (*nextSymbol == '}') {
                        token = new Token::CloseTagValue(this->position->getLine(), this->position->getColumn());
                        this->mode = StreamMode::PlainText;
                        break;
                    }

                    // todo: unexpected character
                    break;
                }

                ioWriter = new IOBuffer::IOMemoryBuffer(32);
                ioWriter->write(curSymbol, 1);

                do {
                    curSymbol = this->getNextChar();
                    if (curSymbol == nullptr) {
                        break;
                    }
                    if (*curSymbol == '}') {
                        this->pushStackChar(curSymbol);
                        break;
                    }

                    if (*curSymbol == ' ') {
                        break;
                    }

                    ioWriter->write(curSymbol, 1);
                } while(true);

                token = new Token::PlainValue(this->position->getLine(), this->position->getColumn(), ioWriter);
                break;
            }

            case StreamMode::ControlMode: {
                if (*curSymbol == 0x20) {
                    // skip spaces
                    do {
                        curSymbol = this->getNextChar();
                    } while(curSymbol != nullptr && *curSymbol == 0x20);
                }

                if (curSymbol == nullptr) {
                    return nullptr;
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
            // todo: free current position
            this->position = this->positionStack->top();
            this->positionStack->pop();
            return symbol;
        }

        char* nextChar = this->charStream->getNext();
        if (nextChar != nullptr) {
            if (*nextChar == 0x0A || *nextChar == 0x0D) {
                this->position->setColumn(0);
                this->position->setLine(this->position->getLine() + 1);
            } else {
                this->position->setColumn(this->position->getColumn() + 1);
            }
        }

        return nextChar;
    }

    void Stream::pushStackChar(char* curChar) {
        this->charStack->push(curChar);
        auto p = new Position(this->position->getLine(), this->position->getColumn());
        this->positionStack->push(p);
    }
}
