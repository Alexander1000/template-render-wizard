#include <io-buffer.h>
#include <trw.h>
#include <stack>
#include <iostream>
#include <syntax-tree-lib.h>

namespace TemplateRenderWizard
{
    Stream::Stream(IOBuffer::CharStream *charStream)
    {
        this->charStream = charStream;
        this->mode = StreamMode::PlainText;
        this->modeStack = new std::stack<StreamMode>;

        this->charStack = new std::stack<char*>;

        this->position = new Position(0, 0);
        this->positionStack = new std::stack<Position*>;

        this->keywords = new std::list<std::string>{
            "if",
            "else",
            "endif",
            "for",
            "endfor",
            "in",
            "and",
            "or",
            "include",
            "with",
        };
    }

    SyntaxTree::Token::Token* Stream::getNextToken()
    {
        char* curSymbol = this->getNextChar();
        if (curSymbol == nullptr) {
            return nullptr;
        }

        SyntaxTree::Token::Token* token = nullptr;
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
                        this->switchToMode(StreamMode::ValueMode);
                        return token;
                    }

                    if (*nextChar == '%') {
                        token = new Token::OpenControlTag(this->position->getLine(), this->position->getColumn());
                        this->switchToMode(StreamMode::ControlModeExpression);
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
                        this->switchToPreviousMode();
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

            case StreamMode::ControlModeExpression: {
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
                        this->switchToPreviousMode(); // <- switch on parent mode
                        token = new Token::CloseControlTag(this->position->getLine(), this->position->getColumn());
                        return token;
                    }
                    this->pushStackChar(nextSymbol);
                }

                if (*curSymbol == '(') {
                    token = new Token::RoundBracketOpen(this->position->getLine(), this->position->getColumn());
                    return token;
                }

                if (*curSymbol == ')') {
                    token = new Token::RoundBracketClose(this->position->getLine(), this->position->getColumn());
                    return token;
                }

                if (*curSymbol == '=' || *curSymbol == '>' || *curSymbol == '<' || *curSymbol == '!') {
                    ioWriter = new IOBuffer::IOMemoryBuffer(4);
                    ioWriter->write(curSymbol, 1);

                    char* nextSymbol = this->getNextChar();
                    if (nextSymbol == nullptr) {
                        return nullptr;
                    }

                    if (*nextSymbol == '=') {
                        ioWriter->write(nextSymbol, 1);
                    }

                    token = new Token::Compare(this->position->getLine(), this->position->getColumn(), ioWriter);
                    return token;
                }

                if (*curSymbol == '*' || *curSymbol == '/') {
                    ioWriter = new IOBuffer::IOMemoryBuffer(4);
                    ioWriter->write(curSymbol, 1);
                    token = new Token::MathOperationHighPriority(this->position->getLine(), this->position->getColumn(), ioWriter);
                    return token;
                }

                if (*curSymbol == '+' || *curSymbol == '-' || *curSymbol == '%') {
                    ioWriter = new IOBuffer::IOMemoryBuffer(4);
                    ioWriter->write(curSymbol, 1);
                    token = new Token::MathOperation(this->position->getLine(), this->position->getColumn(), ioWriter);
                    return token;
                }

                ioWriter = new IOBuffer::IOMemoryBuffer(64);
                do {
                    if (*curSymbol == '%') {
                        char* nextChar = this->getNextChar();
                        if (*nextChar == '}') {
                            this->pushStackChar(nextChar);
                            this->pushStackChar(curSymbol);
                            break;
                        }
                    }

                    if (*curSymbol == ')') {
                        this->pushStackChar(curSymbol);
                        break;
                    }

                    ioWriter->write(curSymbol, 1);
                    curSymbol = this->getNextChar();
                } while(curSymbol != nullptr && *curSymbol != 0x20);

                if (ioWriter->length() >= 2 && ioWriter->length() <= 7) {
                    INIT_CHAR_STRING(strKeyword, 8);
                    ioWriter->read(strKeyword, 7);
                    if (this->isKeyword(strKeyword)) {
                        if (strcmp(strKeyword, "for") == 0) {
                            this->switchToMode(StreamMode::ControlModeForExpression);
                            token = new Token::Keyword(this->position->getLine(), this->position->getColumn(), ioWriter);
                            return token;
                        }

                        token = new Token::Keyword(this->position->getLine(), this->position->getColumn(), ioWriter);
                        return token;
                    }
                }

                token = new Token::ExpressionValue(this->position->getLine(), this->position->getColumn(), ioWriter);
                return token;
            }

            case StreamMode::ControlModeForExpression: {
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
                        token = new Token::CloseControlTag(this->position->getLine(), this->position->getColumn());
                        return token;
                    }
                    this->pushStackChar(nextSymbol);
                }

                if (*curSymbol == ',') {
                    token = new Token::Comma(this->position->getLine(), this->position->getColumn());
                    return token;
                }

                ioWriter = new IOBuffer::IOMemoryBuffer(64);
                int tokenLength = 0;

                do {
                    if (*curSymbol == '%') {
                        char* nextChar = this->getNextChar();
                        if (*nextChar == '}') {
                            this->pushStackChar(nextChar);
                            this->pushStackChar(curSymbol);
                            break;
                        }
                    }

                    if (*curSymbol == ',') {
                        this->pushStackChar(curSymbol);
                        break;
                    }

                    ioWriter->write(curSymbol, 1);
                    curSymbol = this->getNextChar();
                    tokenLength++;
                } while(curSymbol != nullptr && *curSymbol != 0x20);

                if (tokenLength == 2) {
                    INIT_CHAR_STRING(strKeyword, 3);
                    ioWriter->read(strKeyword, 2);
                    if (strcmp(strKeyword, "in") == 0) {
                        token = new Token::Keyword(this->position->getLine(), this->position->getColumn(), ioWriter);
                        return token;
                    }
                }

                token = new Token::PlainValue(this->position->getLine(), this->position->getColumn(), ioWriter);
                return token;
            }
        }

        return token;
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

    void Stream::switchToMode(StreamMode newMode) {
        this->modeStack->push(this->mode);
        this->mode = newMode;
    }

    void Stream::switchToPreviousMode() {
        this->mode = this->modeStack->top();
        this->modeStack->pop();
    }

    bool Stream::isWord(const char *symbol) {
        return (*symbol >= 'a' && *symbol <= 'z') || (*symbol >= 'A' && *symbol <= 'Z');
    }

    bool Stream::isKeyword(std::string* strKeyword) {
        for (auto it = this->keywords->begin(); it != this->keywords->end(); it++) {
            if (strcmp(it->c_str(), strKeyword->c_str()) == 0) {
                return true;
            }
        }
        return false;
    }

    bool Stream::isKeyword(const char* strKeyword) {
        for (auto it = this->keywords->begin(); it != this->keywords->end(); it++) {
            if (strcmp(it->c_str(), strKeyword) == 0) {
                return true;
            }
        }
        return false;
    }
}
