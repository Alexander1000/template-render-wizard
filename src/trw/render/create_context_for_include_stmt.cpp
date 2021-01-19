#include <trw.h>
#include <syntax-tree-lib.h>
#include <iostream>
#include <cstring>

namespace TemplateRenderWizard
{
    Context* Render::create_context_for_include_stmt(SyntaxTree::Syntax::SyntaxElement *element)
    {
        if (element->getType() == SyntaxTree::Syntax::SyntaxElementType::SyntaxType) {
            return this->create_context_for_include_stmt(element->getElement());
        }

        auto listElements = element->getListElements();
        auto itListElements = listElements->begin(); // first element
        auto curElement = *itListElements;
        if (curElement->getType() == SyntaxTree::Syntax::SyntaxElementType::SyntaxType) {
            if (strcmp(curElement->getRule()->getName(), "include_with_stmt") == 0) {
                this->create_context_for_include_stmt(curElement->getElement());
            }
            if (strcmp(curElement->getRule()->getName(), "include_with_pair") == 0) {
                auto elIncludeWithPair = curElement->getElement();
                if (elIncludeWithPair->getType() != SyntaxTree::Syntax::SyntaxElementType::TokenListType) {
                    throw new UnexpectedToken;
                }
                auto lIncludePair = elIncludeWithPair->getListElements();
                auto itIncludePair = lIncludePair->begin(); // token with key
                itIncludePair++; // token double dot
                itIncludePair++; // value
                std::cout << std::endl;
            }
        }
        itListElements++; // t:comma
        itListElements++; // second element
        std::cout << std::endl;
        return nullptr;
    }
}
