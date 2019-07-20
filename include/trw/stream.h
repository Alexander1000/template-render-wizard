#ifndef H_TRW_STREAM_INCLUDED
#define H_TRW_STREAM_INCLUDED

#include <io-buffer.h>
#include <trw/token.h>

namespace TemplateRenderWizard
{
    enum StreamMode{
        PlainText
    };

    class Stream
    {
    public:
        Stream(IOBuffer::CharStream* charStream);
        Token* getNextToken();

    private:
        IOBuffer::CharStream* charStream;
        StreamMode mode;

        char* getNextChar();
    };
}

#endif
