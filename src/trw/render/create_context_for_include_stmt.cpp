#include <trw.h>
#include <syntax-tree-lib.h>
#include <iostream>

namespace TemplateRenderWizard
{
    Context* Render::create_context_for_include_stmt(SyntaxTree::Syntax::SyntaxElement *element)
    {
        if (element->getType() == SyntaxTree::Syntax::SyntaxElementType::SyntaxType) {
            return this->create_context_for_include_stmt(element->getElement());
        }
        std::cout << std::endl;
        return nullptr;
    }
}
