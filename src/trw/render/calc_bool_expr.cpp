#include <trw.h>
#include <syntax-tree-lib.h>

namespace TemplateRenderWizard
{
    bool Render::calc_bool_expr(SyntaxTree::Syntax::SyntaxElement* syntaxElement, Context* context)
    {
        if (syntaxElement->getType() == SyntaxTree::Syntax::SyntaxElementType::TokenType) {
            auto value = this->getValueFromToken(syntaxElement->getToken(), context);
            return cast_value_to_bool(value);
        }

        if (syntaxElement->getType() == SyntaxTree::Syntax::SyntaxElementType::SyntaxType) {
            return this->calc_bool_expr(syntaxElement->getElement(), context);
        }

        if (syntaxElement->getType() == SyntaxTree::Syntax::SyntaxElementType::TokenListType) {
            if (strcmp(syntaxElement->getRule()->getName(), "boolExpr") == 0) {
                auto listElements = syntaxElement->getListElements()->begin(); // first expr
                bool lValue = this->calc_bool_expr(*listElements, context);
                listElements++; // and/or
                auto boolExpr = *listElements;
                auto boolOperatorToken = (*(boolExpr->getElement()->getListElements()->begin()))->getToken();
                RESET_TOKEN_READER(boolOperatorToken);
                INIT_CHAR_STRING(strBoolOperator, 4)
                boolOperatorToken->getReader()->read(strBoolOperator, 3);
                listElements++; // second expr
                bool rValue = this->calc_bool_expr(*listElements, context);
                if (strcmp(strBoolOperator, "and") == 0) {
                    return lValue && rValue;
                }
                if (strcmp(strBoolOperator, "or") == 0) {
                    return lValue || rValue;
                }
            }
            if (strcmp(syntaxElement->getRule()->getName(), "cmpExpr") == 0) {
                auto itEl = syntaxElement->getListElements()->begin(); // s:expr
                auto lValue = this->calc_expr_tree(*itEl, context);
                itEl++; // t:compare
                auto tokenCmp = *itEl;
                itEl++; // s:expr
                auto rValue = this->calc_expr_tree(*itEl, context);
                return this->compare_value(lValue, rValue, tokenCmp->getToken());
            }
            if (strcmp(syntaxElement->getRule()->getName(), "expr") == 0) {
                auto lValue = this->calc_expr_tree(syntaxElement, context);
                if (lValue->getType() == ValueType::None) {
                    return false;
                }
                if (lValue->getType() == ValueType::Integer) {
                    return *lValue->getData<int*>() != 0;
                }
                if (lValue->getType() == ValueType::String) {
                    return strlen(lValue->getData<char*>()) > 0;
                }
            }
        }

        throw new UnexpectedToken;
    }
}
