#ifndef H_TRW_RENDER_INCLUDED
#define H_TRW_RENDER_INCLUDED

#include <string>
#include <trw/stream.h>
#include <trw/tree_parameters.h>
#include <io-buffer.h>
#include <list>
#include <trw/token.h>
#include <trw/value.h>
#include <trw/expression.h>

namespace TemplateRenderWizard
{
    class Render
    {
        TemplateRenderWizard::Tree::Tree* tree;
        TemplateRenderWizard::Stream* stream;

        void renderControlExpression();
        bool ifExpressionControlTag();
        Value* get_value(std::list<Token::Token*>*);
        Value* getValueFromToken(Token::Token*);
        int compare_value(Value*, Value*, Token::Token*);
        Expression* make_expression(std::list<SyntaxElement*>*);
        Value* calc_expr(Expression*);

        std::list<SyntaxElement*>* filter_low_priority_operations(std::list<SyntaxElement*>*);

        bool is_unprocessed_token_exist(std::list<SyntaxElement*>*);

    public:
        Render(const char*, TemplateRenderWizard::Tree::Tree*);
        Render(std::string*, TemplateRenderWizard::Tree::Tree*);
        Render(TemplateRenderWizard::Stream*, TemplateRenderWizard::Tree::Tree*);
        IOBuffer::IOMemoryBuffer* toBuffer();
    };
}

#endif
