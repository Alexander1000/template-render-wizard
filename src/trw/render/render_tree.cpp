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
            this->render_tree(buffer, treeElement->getRule(), treeElement->getListElements());
            return;
        }

        // simple token
    }

    void Render::render_tree(IOBuffer::IOBuffer *buffer, Syntax::Rule *rule, std::list<Syntax::SyntaxElement*>* elements)
    {
        if (strcmp(rule->getName(), "if_stmt") == 0) {
            auto it = elements->begin();
            auto syntaxElement = *it;
            if (syntaxElement->getType() != Syntax::SyntaxType || strcmp(syntaxElement->getRule()->getName(), "if_control") != 0) {
                throw new UnknownToken;
            }
        }
    }
}
