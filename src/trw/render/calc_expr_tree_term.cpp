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
            auto firstElement = *it;
            if (size == 1) {
                if (strcmp(firstElement->getRule()->getName(), "factor") == 0) {
                    return this->calc_expr_tree_factor(firstElement, context);
                }
            }

            Value* lValue = nullptr;
            if (firstElement->getType() == SyntaxTree::Syntax::SyntaxElementType::SyntaxType) {
                lValue = this->calc_expr_tree(firstElement->getElement(), context);
            }
            if (firstElement->getType() == SyntaxTree::Syntax::SyntaxElementType::TokenType) {
                lValue = this->getValueFromToken(firstElement->getToken(), context);
            }

            it++; // token math op
            auto tokenOp = *it;

            it++; // rValue
            auto rValueElement = *it;
            Value* rValue = nullptr;
            if (rValueElement->getType() == SyntaxTree::Syntax::SyntaxElementType::SyntaxType) {
                rValue = this->calc_expr_tree(rValueElement->getElement(), context);
            }
            if (rValueElement->getType() == SyntaxTree::Syntax::SyntaxElementType::TokenType) {
                rValue = this->getValueFromToken(rValueElement->getToken(), context);
            }

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
