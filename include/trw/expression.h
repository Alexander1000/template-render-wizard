#ifndef H_TRW_EXPRESSION_INCLUDED
#define H_TRW_EXPRESSION_INCLUDED

#include <trw/token.h>

namespace TemplateRenderWizard
{
    class Expression;

    enum SyntaxElementType {
        SyntaxTokenType,
        SyntaxValueType,
        SyntaxExpressionType,
    };

    class SyntaxElement
    {
    public:
        SyntaxElement(Token::Token*);
        SyntaxElement(Value*);
        SyntaxElement(Expression*);

        SyntaxElementType getType();
        void* getData();
    private:
        SyntaxElementType type;

        union {
            Token::Token* token;
            Value* value;
            Expression* expression;
        } data;
    };

    class Expression
    {
    public:
        Expression(SyntaxElement*, SyntaxElement*, Token::Token*);
        SyntaxElement* getLValue();
        SyntaxElement* getRValue();
        Token::Token* getToken();

    private:
        SyntaxElement* lValue;
        SyntaxElement* rValue;
        Token::Token* relation;
    };
}

#endif
