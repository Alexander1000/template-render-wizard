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
#include <trw/context.h>
#include <syntax-tree-lib.h>

#define TRW_RENDER_MEMORY_BLOCK_SIZE 4096
#define TRW_RENDER_BUFFER_SIZE 1024

namespace TemplateRenderWizard
{
    class Render
    {
        TemplateRenderWizard::Tree::Tree* tree;
        TemplateRenderWizard::Stream* stream;

        Value* getValueFromToken(SyntaxTree::Token::Token*, Context*);
        bool compare_value(Value*, Value*, SyntaxTree::Token::Token*);
        Value* calc_expr(Expression*);

        SyntaxTree::Token::Token* getNextToken();

        Value* get_value_from_syntax_element(SyntaxElement*);

        void to_buffer_plain_text(IOBuffer::IOBuffer* buffer, SyntaxTree::Token::Token* token);
        void to_buffer_value(IOBuffer::IOBuffer* buffer, Value* value);
        void to_buffer_value(IOBuffer::IOBuffer* buffer, SyntaxTree::Token::Token* token);

        void render_tree(IOBuffer::IOBuffer* buffer, SyntaxTree::Syntax::SyntaxElement* treeElement, Context *context);
        void render_tree(IOBuffer::IOBuffer* buffer, SyntaxTree::Syntax::Rule* rule, std::list<SyntaxTree::Syntax::SyntaxElement*>* elements, Context *context);
        Value* calc_expr_tree(SyntaxTree::Syntax::SyntaxElement*, Context*);
        void render_tree_token(IOBuffer::IOBuffer* buffer, SyntaxTree::Token::Token* token);
        bool calc_if_control(SyntaxTree::Syntax::SyntaxElement*, Context*);
        bool calc_bool_expr(SyntaxTree::Syntax::SyntaxElement*, Context*);

    public:
        Render(const char*, TemplateRenderWizard::Tree::Tree*);
        Render(std::string*, TemplateRenderWizard::Tree::Tree*);
        Render(TemplateRenderWizard::Stream*, TemplateRenderWizard::Tree::Tree*);
        IOBuffer::IOMemoryBuffer* toBufferTree();
    };
}

#endif
