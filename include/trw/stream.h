#ifndef H_TRW_STREAM_INCLUDED
#define H_TRW_STREAM_INCLUDED

#include <io-buffer.h>
#include <trw/token.h>
#include <stack>
#include <trw/position.h>

namespace TemplateRenderWizard
{
    enum StreamMode{
        PlainText,
        ValueMode
    };

    class Stream
    {
    public:
        Stream(IOBuffer::CharStream* charStream);
        Token::Token* getNextToken();

    private:
        IOBuffer::CharStream* charStream;
        StreamMode mode;
        std::stack<char*>* charStack;
        std::stack<Position*>* positionStack;

        Position *position;

        char* getNextChar();
        void setMode(StreamMode);
        void pushStackChar(char*);
    };
}

#endif
