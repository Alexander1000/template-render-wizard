#ifndef H_TRW_EXPRESSION_INCLUDED
#define H_TRW_EXPRESSION_INCLUDED

#include <trw/token.h>
#include <syntax-tree-lib.h>

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
        SyntaxElement(SyntaxTree::Token::Token*);
        SyntaxElement(Value*);
        SyntaxElement(Expression*);

        SyntaxElementType getType();
        void* getData();
    private:
        SyntaxElementType type;

        union {
            SyntaxTree::Token::Token* token;
            Value* value;
            Expression* expression;
        } data;
    };

    class Expression
    {
    public:
        Expression(SyntaxElement*, SyntaxElement*, SyntaxTree::Token::Token*);
        SyntaxElement* getLValue();
        SyntaxElement* getRValue();
        SyntaxTree::Token::Token* getToken();

    private:
        SyntaxElement* lValue;
        SyntaxElement* rValue;
        SyntaxTree::Token::Token* relation;
    };
}

#endif
