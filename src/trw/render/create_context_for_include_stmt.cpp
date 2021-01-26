#include <trw.h>
#include <syntax-tree-lib.h>
#include <iostream>
#include <cstring>

namespace TemplateRenderWizard
{
    Context* Render::create_context_for_include_stmt(SyntaxTree::Syntax::SyntaxElement *element, Context* context)
    {
        if (element->getType() == SyntaxTree::Syntax::SyntaxElementType::SyntaxType) {
            return this->create_context_for_include_stmt(element->getElement(), context);
        }

        auto ctx = new Context;

        auto listElements = element->getListElements();
        auto itListElements = listElements->begin(); // first element
        auto curElement = *itListElements;
        if (curElement->getType() == SyntaxTree::Syntax::SyntaxElementType::SyntaxType) {
            if (strcmp(curElement->getRule()->getName(), "include_with_stmt") == 0) {
                auto nestedContext = this->create_context_for_include_stmt(curElement->getElement(), context);
                merge_context(ctx, nestedContext);
            }
            if (strcmp(curElement->getRule()->getName(), "include_with_pair") == 0) {
                auto elIncludeWithPair = curElement->getElement();
                if (elIncludeWithPair->getType() != SyntaxTree::Syntax::SyntaxElementType::TokenListType) {
                    throw new UnexpectedToken;
                }
                auto lIncludePair = elIncludeWithPair->getListElements();
                auto itIncludePair = lIncludePair->begin(); // token with key
                auto elTokenKey = *itIncludePair;
                if (elTokenKey->getType() != SyntaxTree::Syntax::SyntaxElementType::TokenType) {
                    throw new UnexpectedToken;
                }
                auto tKey = elTokenKey->getToken();
                RESET_TOKEN_READER(tKey);
                INIT_CHAR_STRING(sKey, 128);
                tKey->getReader()->read(sKey, 128);
                itIncludePair++; // token double dot
                itIncludePair++; // value
                auto elValue = *itIncludePair;
                if (elValue->getRule() != nullptr) {
                    if (strcmp(elValue->getRule()->getName(), "expr") == 0) {
                        auto v = this->calc_expr_tree(elValue, context);
                        ctx->setValue(sKey, v);
                    }
                    if (strcmp(elValue->getRule()->getName(), "cmpExpr") == 0) {
                        bool cmpExpr = this->calc_bool_expr(elValue, context);
                        auto v = new Value;
                        v->setData(cmpExpr);
                        ctx->setValue(sKey, v);
                    }
                }
            }
        }
        itListElements++; // t:comma
        itListElements++; // second element
        curElement = *itListElements;
        if (curElement->getType() == SyntaxTree::Syntax::SyntaxElementType::SyntaxType) {
            if (strcmp(curElement->getRule()->getName(), "include_with_stmt") == 0) {
                auto nestedContext = this->create_context_for_include_stmt(curElement->getElement(), context);
                merge_context(ctx, nestedContext);
            }
            if (strcmp(curElement->getRule()->getName(), "include_with_pair") == 0) {
                auto elIncludeWithPair = curElement->getElement();
                if (elIncludeWithPair->getType() != SyntaxTree::Syntax::SyntaxElementType::TokenListType) {
                    throw new UnexpectedToken;
                }
                auto lIncludePair = elIncludeWithPair->getListElements();
                auto itIncludePair = lIncludePair->begin(); // token with key
                auto elTokenKey = *itIncludePair;
                if (elTokenKey->getType() != SyntaxTree::Syntax::SyntaxElementType::TokenType) {
                    throw new UnexpectedToken;
                }
                auto tKey = elTokenKey->getToken();
                RESET_TOKEN_READER(tKey);
                INIT_CHAR_STRING(sKey, 128);
                tKey->getReader()->read(sKey, 128);
                itIncludePair++; // token double dot
                itIncludePair++; // value
                auto elValue = *itIncludePair;
                if (elValue->getRule() != nullptr) {
                    if (strcmp(elValue->getRule()->getName(), "expr") == 0) {
                        auto v = this->calc_expr_tree(elValue, context);
                        ctx->setValue(sKey, v);
                    }
                    if (strcmp(elValue->getRule()->getName(), "cmpExpr") == 0) {
                        bool cmpExpr = this->calc_bool_expr(elValue, context);
                        auto v = new Value;
                        v->setData(cmpExpr);
                        ctx->setValue(sKey, v);
                    }
                }
            }
        }
        std::cout << std::endl;
        return ctx;
    }
}
