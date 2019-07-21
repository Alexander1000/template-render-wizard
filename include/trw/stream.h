#ifndef H_TRW_STREAM_INCLUDED
#define H_TRW_STREAM_INCLUDED

#include <io-buffer.h>
#include <trw/token.h>
#include <stack>

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

        char* getNextChar();
        void setMode(StreamMode);
    };
}

#endif
