#include <trw.h>
#include <syntax-tree-lib.h>

namespace TemplateRenderWizard
{
    void Render::render_tree(IOBuffer::IOBuffer *buffer, SyntaxTree::Syntax::SyntaxElement *treeElement, Context* context)
    {
        if (treeElement->getType() == SyntaxTree::Syntax::SyntaxElementType::SyntaxType) {
            this->render_tree(buffer, treeElement->getElement(), context);
            return;
        }

        if (treeElement->getType() == SyntaxTree::Syntax::SyntaxElementType::TokenListType) {
            this->render_tree(buffer, treeElement->getRule(), treeElement->getListElements(), context);
            return;
        }

        // simple token
    }

    void Render::render_tree(IOBuffer::IOBuffer *buffer, SyntaxTree::Syntax::Rule *rule, std::list<SyntaxTree::Syntax::SyntaxElement*>* elements, Context* context)
    {
        if (strcmp(rule->getName(), "body") == 0) {
            for (auto it = elements->begin(); it != elements->end(); it++) {
                auto curElement = *it;
                if (curElement->getType() == SyntaxTree::Syntax::SyntaxElementType::SyntaxType) {
                    this->render_tree(buffer, curElement->getElement(), context);
                    continue;
                }

                if (curElement->getType() == SyntaxTree::Syntax::SyntaxElementType::TokenType) {
                    this->render_tree_token(buffer, curElement->getToken());
                    continue;
                }
            }

            return;
        }

        if (strcmp(rule->getName(), "injectValue") == 0) {
            auto it = elements->begin(); // t:openTagValue
            it++; // t:plainValue
            auto element = *it;
            if (element->getType() != SyntaxTree::Syntax::SyntaxElementType::TokenType) {
                throw new UnexpectedToken;
            }
            auto value = this->getValueFromToken(element->getToken(), context);
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
            if (syntaxElement->getType() != SyntaxTree::Syntax::SyntaxType || strcmp(syntaxElement->getRule()->getName(), "if_control") != 0) {
                throw new UnexpectedToken;
            }
            auto ifElement = syntaxElement->getElement();
            if (ifElement->getType() != SyntaxTree::Syntax::TokenListType || strcmp(ifElement->getRule()->getName(), "if_control") != 0) {
                throw new UnexpectedToken;
            }

            auto result = this->calc_if_control(ifElement, context);
            if (result) {
                it++; // body
                auto bodyElement = *it;
                if (bodyElement->getType() != SyntaxTree::Syntax::SyntaxElementType::SyntaxType) {
                    throw new UnexpectedToken;
                }
                this->render_tree(buffer, bodyElement->getElement(), context);
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
                    if (bodyElement->getType() != SyntaxTree::Syntax::SyntaxElementType::SyntaxType) {
                        throw new UnexpectedToken;
                    }
                    this->render_tree(buffer, bodyElement->getElement(), context);
                    it++; // endif
                }
            }
        }

        if (strcmp(rule->getName(), "for_stmt") == 0) {
            auto it = elements->begin(); // for_control
            auto elForControl = *it;
            if (elForControl->getType() != SyntaxTree::Syntax::SyntaxElementType::SyntaxType) {
                throw new UnexpectedToken;
            }
            auto forControl = elForControl->getElement();
            if (forControl->getType() != SyntaxTree::Syntax::SyntaxElementType::TokenListType) {
                throw new UnexpectedToken;
            }
            auto itForControl = forControl->getListElements()->begin(); // openControlTag
            itForControl++; // keyword (for)
            itForControl++; // plainValue
            SyntaxTree::Syntax::SyntaxElement* lValueElement = nullptr;
            SyntaxTree::Syntax::SyntaxElement* rValueElement = nullptr;
            lValueElement = *itForControl;
            itForControl++; // comma vs keyword(in)
            auto tForControlToken = *itForControl;
            if (tForControlToken->getType() != SyntaxTree::Syntax::SyntaxElementType::TokenType) {
                throw new UnexpectedToken;
            }
            if (tForControlToken->getToken()->getType() == Token::Type::CommaType) {
                itForControl++; // second plainValue
                rValueElement = *itForControl;
                itForControl++; // keyword (in)
            }
            itForControl++; // plainValue (source of data)
            auto sourceElement = *itForControl;
            if (sourceElement->getType() != SyntaxTree::Syntax::SyntaxElementType::TokenType) {
                throw new UnexpectedToken;
            }
            if (sourceElement->getToken()->getType() != Token::Type::PlainValueType) {
                throw new UnexpectedToken;
            }
            auto sourceValue = this->getValueFromToken(sourceElement->getToken(), context);
            itForControl++; // closeControlTag
            it++; // body
            auto elBody = *it;
            if (sourceValue->getType() == ValueType::Array) {
                int currentNumber = 0;
                for (auto itArray = sourceValue->getArray()->begin(); itArray != sourceValue->getArray()->end(); itArray++) {
                    auto ctxValue = new Value();
                    auto ctxValueMap = new std::map<std::string, Value*>;
                    ctxValue->setData(ctxValueMap);
                    auto ctx = new Context(context);
                    ctx->setValueContext(ctxValue);
                    auto curContextElement = *itArray;
                    if (lValueElement != nullptr) {
                        INIT_CHAR_STRING(strValue, 1024)
                        auto lValueToken = lValueElement->getToken();
                        RESET_TOKEN_READER(lValueToken);
                        lValueToken->getReader()->read(strValue, 1024);
                        (*ctxValueMap)[strValue] = curContextElement;
                        if (rValueElement != nullptr) {
                            auto v = new Value();
                            v->setData(currentNumber);
                            (*ctxValueMap)[strValue] = v;
                        } else {
                            (*ctxValueMap)[strValue] = curContextElement;
                        }
                    }
                    if (rValueElement != nullptr) {
                        INIT_CHAR_STRING(strValue, 1024)
                        auto rValueToken = rValueElement->getToken();
                        RESET_TOKEN_READER(rValueToken);
                        rValueToken->getReader()->read(strValue, 1024);
                        (*ctxValueMap)[strValue] = curContextElement;
                    }
                    this->render_tree(buffer, elBody, ctx);
                    currentNumber++;
                }
            }
            if (sourceValue->getType() == ValueType::Object) {
                for (auto itObject = sourceValue->getObject()->begin(); itObject != sourceValue->getObject()->end(); itObject++) {
                    auto ctxValue = new Value();
                    auto ctxValueMap = new std::map<std::string, Value*>;
                    ctxValue->setData(ctxValueMap);
                    auto ctx = new Context(context);
                    ctx->setValueContext(ctxValue);
                    auto curContextElement = *itObject;
                    if (lValueElement != nullptr) {
                        INIT_CHAR_STRING(strValue, 1024)
                        auto lValueToken = lValueElement->getToken();
                        RESET_TOKEN_READER(lValueToken);
                        lValueToken->getReader()->read(strValue, 1024);
                        if (rValueElement != nullptr) {
                            auto v = new Value();
                            v->setData((char*) curContextElement.first.c_str());
                            (*ctxValueMap)[strValue] = v;
                        } else {
                            (*ctxValueMap)[strValue] = curContextElement.second;
                        }
                    }
                    if (rValueElement != nullptr) {
                        INIT_CHAR_STRING(strValue, 1024)
                        auto rValueToken = rValueElement->getToken();
                        RESET_TOKEN_READER(rValueToken);
                        rValueToken->getReader()->read(strValue, 1024);
                        (*ctxValueMap)[strValue] = curContextElement.second;
                    }
                    this->render_tree(buffer, elBody, ctx);
                }
            }
            it++; // endfor_control
        }

        if (strcmp(rule->getName(), "expr_control") == 0) {
            auto it = elements->begin(); // openControlTag
            it++; // expression
            auto element = *it;
            if (strcmp(element->getRule()->getName(), "expr") == 0) {
                auto value = this->calc_expr_tree(element, context);
                this->to_buffer_value(buffer, value);
            } else if (strcmp(element->getRule()->getName(), "cmpExpr") == 0 || strcmp(element->getRule()->getName(), "boolExpr") == 0) {
                bool result = this->calc_bool_expr(element, context);
                if (result) {
                    buffer->write("true", 4);
                } else {
                    buffer->write("false", 5);
                }
            }
            it++; // closeControlTag
        }

        if (strcmp(rule->getName(), "include_stmt") == 0) {
            this->render_tree_include(buffer, rule, elements, context);
        }
    }

    Value* Render::calc_expr_tree(SyntaxTree::Syntax::SyntaxElement *syntaxElement, Context* context)
    {
        if (syntaxElement->getType() == SyntaxTree::Syntax::TokenType) {
            return this->getValueFromToken(syntaxElement->getToken(), context);
        }

        if (syntaxElement->getType() == SyntaxTree::Syntax::TokenListType) {
            if (strcmp(syntaxElement->getRule()->getName(), "term") == 0) {
                return this->calc_expr_tree_term(syntaxElement, context);
            }

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
                if (firstElement->getType() == SyntaxTree::Syntax::SyntaxElementType::SyntaxType) {
                    lValue = this->calc_expr_tree(firstElement->getElement(), context);
                    return lValue;
                }
                if (firstElement->getType() == SyntaxTree::Syntax::SyntaxElementType::TokenType) {
                    return this->getValueFromToken(firstElement->getToken(), context);
                }

                throw new UnexpectedToken;
            }

            if (firstElement->getType() == SyntaxTree::Syntax::SyntaxElementType::TokenType) {
                it++;
                auto exprValue = this->calc_expr_tree(*it, context);
                it++;
                return exprValue;
            }

            lValue = this->calc_expr_tree(*it, context);
            it++;
            auto tokenOp = *it;
            it++;
            auto rValue = this->calc_expr_tree(*it, context);

            return this->calc_expr(
                new Expression(
                    new SyntaxElement(lValue),
                    new SyntaxElement(rValue),
                    tokenOp->getToken()
                )
            );
        }

        if (strcmp(syntaxElement->getRule()->getName(), "term") == 0) {
            return this->calc_expr_tree_term(syntaxElement, context);
        }

        if (syntaxElement->getType() != SyntaxTree::Syntax::SyntaxType || strcmp(syntaxElement->getRule()->getName(), "expr") != 0) {
            throw new UnexpectedToken;
        }

        return this->calc_expr_tree(syntaxElement->getElement(), context);
    }

    void Render::render_tree_token(IOBuffer::IOBuffer *buffer, SyntaxTree::Token::Token *token)
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

    bool Render::calc_if_control(SyntaxTree::Syntax::SyntaxElement *syntaxElement, Context* context)
    {
        auto it = syntaxElement->getListElements()->begin(); // open control tag
        it++; // keyword
        it++; // expr
        auto expr = *it;

        if (strcmp(expr->getRule()->getName(), "cmpExpr") == 0) {
            if (expr->getType() != SyntaxTree::Syntax::SyntaxElementType::SyntaxType) {
                throw new UnexpectedToken;
            }
            auto cmpExprSyntaxElement = expr->getElement();
            if (cmpExprSyntaxElement->getType() != SyntaxTree::Syntax::SyntaxElementType::TokenListType) {
                throw new UnexpectedToken;
            }
            auto itEl = cmpExprSyntaxElement->getListElements()->begin(); // s:expr
            auto lValue = this->calc_expr_tree(*itEl, context);
            itEl++; // t:compare
            auto tokenCmp = *itEl;
            itEl++; // s:expr
            auto rValue = this->calc_expr_tree(*itEl, context);
            return this->compare_value(lValue, rValue, tokenCmp->getToken());
        }

        if (strcmp(expr->getRule()->getName(), "expr") == 0) {
            auto lValue = this->calc_expr_tree(expr, context);
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

        if (strcmp(expr->getRule()->getName(), "boolExpr") == 0) {
            return this->calc_bool_expr(expr, context);
        }

        throw new UnexpectedToken;
    }
}
