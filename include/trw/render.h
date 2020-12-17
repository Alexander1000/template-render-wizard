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

        Value* getValueFromToken(Token::Token*);
        bool compare_value(Value*, Value*, Token::Token*);
        Value* calc_expr(Expression*);

        Token::Token* getNextToken();

        Value* get_value_from_syntax_element(SyntaxElement*);

        void to_buffer_plain_text(IOBuffer::IOBuffer* buffer, Token::Token* token);
        void to_buffer_value(IOBuffer::IOBuffer* buffer, Value* value);
        void to_buffer_value(IOBuffer::IOBuffer* buffer, Token::Token* token);

        void render_tree(IOBuffer::IOBuffer* buffer, Syntax::SyntaxElement* treeElement);
        void render_tree(IOBuffer::IOBuffer* buffer, Syntax::Rule* rule, std::list<Syntax::SyntaxElement*>* elements);
        Value* calc_expr_tree(Syntax::SyntaxElement*);
        void render_tree_token(IOBuffer::IOBuffer* buffer, Token::Token* token);
        bool calc_if_control(Syntax::SyntaxElement*);

    public:
        Render(const char*, TemplateRenderWizard::Tree::Tree*);
        Render(std::string*, TemplateRenderWizard::Tree::Tree*);
        Render(TemplateRenderWizard::Stream*, TemplateRenderWizard::Tree::Tree*);
        IOBuffer::IOMemoryBuffer* toBufferTree();
    };
}

#endif
