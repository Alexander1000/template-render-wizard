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
#include <trw/syntax.h>

#define TRW_RENDER_MEMORY_BLOCK_SIZE 4096
#define TRW_RENDER_BUFFER_SIZE 1024

namespace TemplateRenderWizard
{
    class Render
    {
        TemplateRenderWizard::Tree::Tree* tree;
        TemplateRenderWizard::Stream* stream;
        std::stack<Token::Token*>* tokenStack;

        void renderControlExpression(IOBuffer::IOBuffer*);
        bool ifExpressionControlTag();
        Value* get_value(std::list<Token::Token*>*);
        Value* getValueFromToken(Token::Token*);
        bool compare_value(Value*, Value*, Token::Token*);
        Value* calc_expr(Expression*);

        std::list<SyntaxElement*>* filter_low_priority_operations(std::list<SyntaxElement*>*);

        bool is_unprocessed_token_exist(std::list<SyntaxElement*>*);

        Token::Token* getNextToken();
        void pushBackToken(Token::Token*);

        Value* get_value_from_syntax_element(SyntaxElement*);

        void to_buffer_plain_text(IOBuffer::IOBuffer* buffer, Token::Token* token);
        void to_buffer_value(IOBuffer::IOBuffer* buffer, Value* value);
        void to_buffer_value(IOBuffer::IOBuffer* buffer, Token::Token* token);

        void render_if_expression(IOBuffer::IOBuffer* buffer, bool result);

        void render_tree(IOBuffer::IOBuffer* buffer, Syntax::SyntaxElement* treeElement);

    public:
        Render(const char*, TemplateRenderWizard::Tree::Tree*);
        Render(std::string*, TemplateRenderWizard::Tree::Tree*);
        Render(TemplateRenderWizard::Stream*, TemplateRenderWizard::Tree::Tree*);
        IOBuffer::IOMemoryBuffer* toBuffer();
        IOBuffer::IOMemoryBuffer* toBufferTree();
    };
}

#endif
