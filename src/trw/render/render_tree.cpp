#include <trw.h>
#include <iostream>

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
        if (strcmp(rule->getName(), "body") == 0) {
            for (auto it = elements->begin(); it != elements->end(); it++) {
                auto curElement = *it;
                if (curElement->getType() == Syntax::SyntaxElementType::SyntaxType) {
                    this->render_tree(buffer, curElement->getElement());
                    continue;
                }

                if (curElement->getType() == Syntax::SyntaxElementType::TokenType) {
                    this->render_tree_token(buffer, curElement->getToken());
                    continue;
                }
            }

            return;
        }

        if (strcmp(rule->getName(), "injectValue") == 0) {
            std::cout << std::endl;
            auto it = elements->begin(); // t:openTagValue
            it++; // t:plainValue
            auto element = *it;
            if (element->getType() != Syntax::SyntaxElementType::TokenType) {
                throw new UnexpectedToken;
            }
            auto value = this->getValueFromToken(element->getToken());
            this->to_buffer_value(buffer, value);
            return;
        }

        if (strcmp(rule->getName(), "if_stmt") == 0) {
            int count = 0;
            for (auto it = elements->begin(); it != elements->end(); it++) {
                count++;
            }

            auto it = elements->begin(); // if statement
            auto syntaxElement = *it;
            if (syntaxElement->getType() != Syntax::SyntaxType || strcmp(syntaxElement->getRule()->getName(), "if_control") != 0) {
                throw new UnexpectedToken;
            }
            auto ifElement = syntaxElement->getElement();
            if (ifElement->getType() != Syntax::TokenListType || strcmp(ifElement->getRule()->getName(), "if_control") != 0) {
                throw new UnexpectedToken;
            }

            auto result = this->calc_if_control(ifElement);
            if (result) {
                it++; // body
                auto bodyElement = *it;
                if (bodyElement->getType() != Syntax::SyntaxElementType::SyntaxType) {
                    throw new UnexpectedToken;
                }
                this->render_tree(buffer, bodyElement->getElement());
                it++; // skip else/endif
                if (count == 5) {
                    it++; // skip else body
                    it++; // skip endif
                }
            } else {
                it++; // skip body
                it++; // skip else/endif
                if (count == 5) {
                    it++; // <- else body
                    auto bodyElement = *it;
                    if (bodyElement->getType() != Syntax::SyntaxElementType::SyntaxType) {
                        throw new UnexpectedToken;
                    }
                    this->render_tree(buffer, bodyElement->getElement());
                    it++; // endif
                }
            }
        }
    }

    Value* Render::calc_expr_tree(Syntax::SyntaxElement *syntaxElement)
    {
        if (syntaxElement->getType() == Syntax::TokenType) {
            return this->getValueFromToken(syntaxElement->getToken());
        }

        if (syntaxElement->getType() == Syntax::TokenListType) {
            if (strcmp(syntaxElement->getRule()->getName(), "expr") != 0) {
                throw new UnexpectedToken;
            }

            auto syntaxList = syntaxElement->getListElements();

            int count = 0;
            for (auto it = syntaxList->begin(); it != syntaxList->end(); it++) {
                count++;
            }

            auto it = syntaxList->begin(); // lValue
            auto firstElement = *it;

            Value *lValue;

            if (count == 1) {
                if (firstElement->getType() == Syntax::SyntaxElementType::SyntaxType) {
                    lValue = this->calc_expr_tree(firstElement->getElement());
                    return lValue;
                }
                if (firstElement->getType() == Syntax::SyntaxElementType::TokenType) {
                    return this->getValueFromToken(firstElement->getToken());
                }

                throw new UnexpectedToken;
            }

            if (firstElement->getType() == Syntax::SyntaxElementType::TokenType) {
                it++;
                auto exprValue = this->calc_expr_tree(*it);
                it++;
                return exprValue;
            }

            lValue = this->calc_expr_tree(*it);
            it++;
            auto tokenOp = *it;
            it++;
            auto rValue = this->calc_expr_tree(*it);

            return this->calc_expr(
                new Expression(
                    new SyntaxElement(lValue),
                    new SyntaxElement(rValue),
                    tokenOp->getToken()
                )
            );
        }

        if (syntaxElement->getType() != Syntax::SyntaxType || strcmp(syntaxElement->getRule()->getName(), "expr") != 0) {
            throw new UnexpectedToken;
        }

        return this->calc_expr_tree(syntaxElement->getElement());
    }

    void Render::render_tree_token(IOBuffer::IOBuffer *buffer, Token::Token *token)
    {
        switch (token->getType()) {
            case Token::Type::PlainTextType: {
                this->to_buffer_plain_text(buffer, token);
                break;
            }
            default: {
                throw new UnexpectedToken;
            }
        }
    }

    bool Render::calc_if_control(Syntax::SyntaxElement *syntaxElement)
    {
        auto it = syntaxElement->getListElements()->begin(); // open control tag
        it++; // keyword
        it++; // expr
        auto expr = *it;

        if (strcmp(expr->getRule()->getName(), "cmpExpr") == 0) {
            if (expr->getType() != Syntax::SyntaxElementType::SyntaxType) {
                throw new UnexpectedToken;
            }
            auto cmpExprSyntaxElement = expr->getElement();
            if (cmpExprSyntaxElement->getType() != Syntax::SyntaxElementType::TokenListType) {
                throw new UnexpectedToken;
            }
            auto itEl = cmpExprSyntaxElement->getListElements()->begin(); // s:expr
            auto lValue = this->calc_expr_tree(*itEl);
            itEl++; // t:compare
            auto tokenCmp = *itEl;
            itEl++; // s:expr
            auto rValue = this->calc_expr_tree(*itEl);
            return this->compare_value(lValue, rValue, tokenCmp->getToken());
        }

        if (strcmp(expr->getRule()->getName(), "expr") == 0) {
            auto lValue = this->calc_expr_tree(expr);
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

        throw new UnexpectedToken;
    }
}
