#ifndef H_TRW_STREAM_INCLUDED
#define H_TRW_STREAM_INCLUDED

#include <io-buffer.h>

namespace TemplateRenderWizard
{
    class Stream
    {
    public:
        Stream(IOBuffer::CharStream* charStream);

    private:
        IOBuffer::CharStream* charStream;
    };
}

#endif
