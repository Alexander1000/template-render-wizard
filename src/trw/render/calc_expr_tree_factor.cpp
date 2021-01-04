#include <trw.h>
#include <iostream>

namespace TemplateRenderWizard
{
    Value * Render::calc_expr_tree_factor(SyntaxTree::Syntax::SyntaxElement *syntaxElement, Context *context)
    {
        if (syntaxElement->getType() == SyntaxTree::Syntax::SyntaxElementType::TokenListType) {
            auto it = syntaxElement->getListElements()->begin();
            int size = syntaxElement->getListElements()->size();
            if (size == 1) {
                auto firstElement = *it;
                if (firstElement->getType() == SyntaxTree::Syntax::SyntaxElementType::TokenType) {
                    return this->getValueFromToken(firstElement->getToken(), context);
                }
                throw new UnexpectedToken;
            }

            it++;
            Value* v = this->calc_expr_tree(*it, context);
            it++;
            return v;
        }

        throw new UnexpectedToken;
        return nullptr;
    }
}
