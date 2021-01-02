#include <trw.h>
#include <list>
#include <syntax-tree-lib.h>

namespace TemplateRenderWizard
{
    IOBuffer::IOMemoryBuffer* Render::toBufferTree()
    {
        auto buffer = new IOBuffer::IOMemoryBuffer(TRW_RENDER_MEMORY_BLOCK_SIZE);

        auto tokens = new std::list<SyntaxTree::Token::Token*>;
        auto token = this->getNextToken();

        while (token != nullptr) {
            tokens->push_back(token);
            token = this->getNextToken();
        }

        SyntaxTree::Syntax::Tree syntaxTree;
        auto syntax = syntaxTree.parse(tokens);

        this->render_tree(buffer, syntax, nullptr);

        return buffer;
    }
}
