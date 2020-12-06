#ifndef H_TOKEN_INCLUDED
#define H_TOKEN_INCLUDED

#include <io-buffer.h>

namespace TemplateRenderWizard::Token
{
    enum Type {
        PlainTextType,
        OpenTagValueType,
        CloseTagValueType,
        PlainValueType,
        OpenControlTagType,
        CloseControlTagType,
        KeywordType,
        RoundBracketOpenType,
        RoundBracketCloseType,
        CompareType,
    };

    class Token
    {
    public:
        Token(int line, int column, IOBuffer::IOReader *reader);
        int getLine();
        int getColumn();
        virtual Type getType() = 0;
        IOBuffer::IOReader* getReader();
    protected:
        int line;
        int column;
        IOBuffer::IOReader *reader;
    };

    class OpenTagValue : public Token
    {
    public:
        OpenTagValue(int line, int column);
        Type getType() final;
    };

    class CloseTagValue : public Token
    {
    public:
        CloseTagValue(int line, int column);
        Type getType() final;
    };

    class OpenControlTag : public Token
    {
    public:
        OpenControlTag(int line, int column);
        Type getType() final;
    };

    class CloseControlTag : public Token
    {
    public:
        CloseControlTag(int line, int column);
        Type getType() final;
    };

    class PlainText : public Token
    {
    public:
        PlainText(int line, int column, IOBuffer::IOReader *reader);
        Type getType() final;
    };

    class PlainValue : public Token
    {
    public:
        PlainValue(int line, int column, IOBuffer::IOReader *reader);
        Type getType() final;
    };

    class Keyword : public Token
    {
    public:
        Keyword(int line, int column, IOBuffer::IOReader *reader);
        Type getType() final;
    };

    class RoundBracketOpen : public Token
    {
    public:
        RoundBracketOpen(int line, int column);
        Type getType() final;
    };

    class RoundBracketClose : public Token
    {
    public:
        RoundBracketClose(int line, int column);
        Type getType() final;
    };

    class Compare : public Token
    {
    public:
        Compare(int line, int column, IOBuffer::IOReader *reader);
        Type getType() final;
    };
}

#endif
