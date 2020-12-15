#include <trw.h>

namespace TemplateRenderWizard
{
    void Render::render_tree(IOBuffer::IOBuffer *buffer, Syntax::SyntaxElement *treeElement)
    {
        if (treeElement->getType() == Syntax::SyntaxElementType::SyntaxType) {
            this->render_tree(buffer, treeElement->getElement());
            return;
        }

        if (treeElement->getType() == Syntax::SyntaxElementType::TokenListType) {
            // todo: call sub sequence renders
            return;
        }
    }
}
