#ifndef H_TOKEN_INCLUDED
#define H_TOKEN_INCLUDED

#include <io-buffer.h>
#include <syntax-tree-lib.h>
#include <map>

namespace TemplateRenderWizard::Token
{
    enum Type {
        EofType,
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
        MathOperationHighPriorityType,
        MathOperationType,
        ExpressionValueType,
        CommaType,
        FilePathType,
        DoubleDotType,
        OpenBraceType,
        CloseBraceType,
        IncludeWithKeyType,
    };

    class TokenMap : public SyntaxTree::Token::TokenMap
    {
    public:
        TokenMap();
    };

    class OpenTagValue : public SyntaxTree::Token::Token
    {
    public:
        OpenTagValue(int line, int column);
        int getType() final;
    };

    class CloseTagValue : public SyntaxTree::Token::Token
    {
    public:
        CloseTagValue(int line, int column);
        int getType() final;
    };

    class OpenControlTag : public SyntaxTree::Token::Token
    {
    public:
        OpenControlTag(int line, int column);
        int getType() final;
    };

    class CloseControlTag : public SyntaxTree::Token::Token
    {
    public:
        CloseControlTag(int line, int column);
        int getType() final;
    };

    class PlainText : public SyntaxTree::Token::Token
    {
    public:
        PlainText(int line, int column, IOBuffer::IOReader *reader);
        int getType() final;
    };

    class PlainValue : public SyntaxTree::Token::Token
    {
    public:
        PlainValue(int line, int column, IOBuffer::IOReader *reader);
        int getType() final;
    };

    class Keyword : public SyntaxTree::Token::Token
    {
    public:
        Keyword(int line, int column, IOBuffer::IOReader *reader);
        int getType() final;
    };

    class RoundBracketOpen : public SyntaxTree::Token::Token
    {
    public:
        RoundBracketOpen(int line, int column);
        int getType() final;
    };

    class RoundBracketClose : public SyntaxTree::Token::Token
    {
    public:
        RoundBracketClose(int line, int column);
        int getType() final;
    };

    class Compare : public SyntaxTree::Token::Token
    {
    public:
        Compare(int line, int column, IOBuffer::IOReader *reader);
        int getType() final;
    };

    class MathOperationHighPriority : public SyntaxTree::Token::Token
    {
    public:
        MathOperationHighPriority(int line, int column, IOBuffer::IOReader *reader);
        int getType() final;
    };

    class MathOperation : public SyntaxTree::Token::Token
    {
    public:
        MathOperation(int line, int column, IOBuffer::IOReader *reader);
        int getType() final;
    };

    class ExpressionValue : public SyntaxTree::Token::Token
    {
    public:
        ExpressionValue(int line, int column, IOBuffer::IOReader *reader);
        int getType() final;
    };

    class Comma : public SyntaxTree::Token::Token
    {
    public:
        Comma(int line, int column);
        int getType() final;
    };

    class FilePath : public SyntaxTree::Token::Token
    {
    public:
        FilePath(int line, int column, IOBuffer::IOReader *reader);
        int getType() final;
    };

    class DoubleDot : public SyntaxTree::Token::Token
    {
    public:
        DoubleDot(int line, int column);
        int getType() final;
    };

    class OpenBrace : public SyntaxTree::Token::Token
    {
    public:
        OpenBrace(int line, int column);
        int getType() final;
    };

    class CloseBrace : public SyntaxTree::Token::Token
    {
    public:
        CloseBrace(int line, int column);
        int getType() final;
    };

    class IncludeWithKey : public SyntaxTree::Token::Token
    {
    public:
        IncludeWithKey(int line, int column, IOBuffer::IOReader *reader);
        int getType() final;
    };
}

#endif
