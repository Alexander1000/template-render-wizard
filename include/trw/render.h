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
#include <stack>

#define TRW_RENDER_MEMORY_BLOCK_SIZE 4096
#define TRW_RENDER_BUFFER_SIZE 1024

namespace TemplateRenderWizard
{
    class Render
    {
        TemplateRenderWizard::Tree::Tree* tree;
        TemplateRenderWizard::Stream* stream;
        std::stack<Token::Token*>* tokenStack;

        void renderControlExpression(IOBuffer::IOMemoryBuffer*);
        bool ifExpressionControlTag();
        Value* get_value(std::list<Token::Token*>*);
        Value* getValueFromToken(Token::Token*);
        bool compare_value(Value*, Value*, Token::Token*);
        Value* calc_expr(Expression*);

        std::list<SyntaxElement*>* filter_low_priority_operations(std::list<SyntaxElement*>*);

        bool is_unprocessed_token_exist(std::list<SyntaxElement*>*);

        Token::Token* getNextToken();
        void pushBackToken(Token::Token*);

    public:
        Render(const char*, TemplateRenderWizard::Tree::Tree*);
        Render(std::string*, TemplateRenderWizard::Tree::Tree*);
        Render(TemplateRenderWizard::Stream*, TemplateRenderWizard::Tree::Tree*);
        IOBuffer::IOMemoryBuffer* toBuffer();
    };
}

#endif
