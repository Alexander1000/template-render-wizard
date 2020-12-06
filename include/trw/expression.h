#ifndef H_TRW_EXPRESSION_INCLUDED
#define H_TRW_EXPRESSION_INCLUDED

#include <trw/token.h>

namespace TemplateRenderWizard
{
    class Expression
    {
    public:
        Expression(Token::Token*, Token::Token*, Token::Token*);

    private:
        void* lValue;
        void* rValue;
        void* relation;
    };
}

#endif
