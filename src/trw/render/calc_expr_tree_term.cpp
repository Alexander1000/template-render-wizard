#include <trw.h>
#include <syntax-tree-lib.h>
#include <iostream>
#include <cstring>

namespace TemplateRenderWizard
{
    Value * Render::calc_expr_tree_term(SyntaxTree::Syntax::SyntaxElement *syntaxElement, Context *context)
    {
        if (syntaxElement->getType() == SyntaxTree::Syntax::SyntaxElementType::SyntaxType) {
            return this->calc_expr_tree_term(syntaxElement->getElement(), context);
        }

        if (syntaxElement->getType() == SyntaxTree::Syntax::SyntaxElementType::TokenListType) {
            int size = syntaxElement->getListElements()->size();
            auto it = syntaxElement->getListElements()->begin();
            auto firstElement = (*it)->getElement();
            if (size == 1) {
                if (strcmp(firstElement->getRule()->getName(), "factor") == 0) {
                    return this->calc_expr_tree_factor(firstElement, context);
                }
            }

            Value* lValue = this->calc_expr_tree(firstElement, context);

            it++; // token math op
            auto tokenOp = *it;

            it++; // rValue
            auto rValueElement = (*it)->getElement();
            Value* rValue = this->calc_expr_tree(rValueElement, context);

            return this->calc_expr(
                new Expression(
                    new SyntaxElement(lValue),
                    new SyntaxElement(rValue),
                    tokenOp->getToken()
                )
            );
        }

        throw new UnexpectedToken;

        return nullptr;
    }
}
