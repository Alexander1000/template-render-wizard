#include <trw.h>
#include <syntax-tree-lib.h>

namespace TemplateRenderWizard
{
    Value * Render::calc_expr_tree_term(SyntaxTree::Syntax::SyntaxElement *syntaxElement, Context *context)
    {
        if (syntaxElement->getType() == SyntaxTree::Syntax::SyntaxElementType::TokenListType) {
            int size = syntaxElement->getListElements()->size();
            auto it = syntaxElement->getListElements()->begin();
        }
        return nullptr;
    }
}
