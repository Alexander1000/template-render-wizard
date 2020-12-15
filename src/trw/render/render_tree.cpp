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
                throw new UnexpectedToken;
            }
            auto ifElement = syntaxElement->getElement();
            if (ifElement->getType() != Syntax::TokenListType || strcmp(ifElement->getRule()->getName(), "if_control") != 0) {
                throw new UnexpectedToken;
            }

            auto itEl = ifElement->getListElements()->begin(); // open control tag
            itEl++; // keyword
            itEl++; // expr
            auto expr = *it;
            auto value = this->calc_expr_tree(expr);
        }
    }

    Value* Render::calc_expr_tree(Syntax::SyntaxElement *syntaxElement)
    {
        if (syntaxElement->getType() != Syntax::SyntaxType || strcmp(syntaxElement->getRule()->getName(), "expr") != 0) {
            throw new UnexpectedToken;
        }

        auto syntax = syntaxElement->getElement();

        return nullptr;
    }
}
