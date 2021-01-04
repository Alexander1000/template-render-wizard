#include <trw.h>
#include <syntax-tree-lib.h>
#include <iostream>
#include <cstring>

namespace TemplateRenderWizard
{
    Value * Render::calc_expr_tree_term(SyntaxTree::Syntax::SyntaxElement *syntaxElement, Context *context)
    {
        if (syntaxElement->getType() == SyntaxTree::Syntax::SyntaxElementType::TokenListType) {
            int size = syntaxElement->getListElements()->size();
            auto it = syntaxElement->getListElements()->begin();
            auto firstElement = (*it)->getElement();
            if (size == 1) {
                if (strcmp(firstElement->getRule()->getName(), "factor") == 0) {
                    return this->calc_expr_tree_factor(firstElement, context);
                }
            }

            throw new UnexpectedToken;
        }

        throw new UnexpectedToken;

        return nullptr;
    }
}
