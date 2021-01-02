#include <trw.h>
#include <syntax-tree-lib.h>

namespace TemplateRenderWizard
{
    SyntaxTree::Token::Token* Render::getNextToken()
    {
        return this->stream->getNextToken();
    }
}
