#include <trw.h>
#include <io-buffer.h>
#include <syntax-tree-lib.h>
#include <cstring>

namespace TemplateRenderWizard
{
    void Render::render_tree_include(
        IOBuffer::IOBuffer *buffer,
        SyntaxTree::Syntax::Rule *rule,
        std::list<SyntaxTree::Syntax::SyntaxElement*> *elements,
        Context *context
    ) {
        if (strcmp(rule->getName(), "include_stmt") == 0) {
            // do something
            auto it = elements->begin(); // open control tag
            it++; // keyword include
            it++; // file name for render
            auto elFilePath = *it;
            if (elFilePath->getType() != SyntaxTree::Syntax::SyntaxElementType::TokenType) {
                throw new UnexpectedToken;
            }
            auto tFilePath = elFilePath->getToken();
            RESET_TOKEN_READER(tFilePath);
            INIT_CHAR_STRING(strFilePath, 64);
            tFilePath->getReader()->read(strFilePath, 63);

            if (file_exists(strFilePath)) {
                // todo: check files exists
                // todo: check files in depend main template-file
                // todo: check tpl directory
                auto r = new Render(strFilePath, this->tree);
                auto nestedBuffer = r->toBufferTree(context);
                // todo: merge buffers
            }
            it++; // close control tag
        }
    }
}
