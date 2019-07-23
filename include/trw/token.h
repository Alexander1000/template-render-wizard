#ifndef H_TOKEN_INCLUDED
#define H_TOKEN_INCLUDED

#include <io-buffer.h>

namespace TemplateRenderWizard::Token
{
    enum Type {
        PlainTextType,
        OpenTagValueType,
        CloseTagValueType
    };

    class Token
    {
    public:
        Token(int line, int column, IOBuffer::IOReader *reader);
        int getLine();
        int getColumn();
        virtual Type getType() = 0;
    protected:
        int line;
        int column;
        IOBuffer::IOReader *reader;
    };

    class OpenTagValue : public Token
    {
    public:
        OpenTagValue(int line, int column);
        Type getType();
    };

    class CloseTagValue : public Token
    {
    public:
        CloseTagValue(int line, int column);
        Type getType();
    };

    class PlainText : public Token
    {
    public:
        PlainText(int line, int column, IOBuffer::IOReader *reader);
        Type getType();
    };
}

#endif
