#include <trw.h>
#include <syntax-tree-lib.h>

namespace TemplateRenderWizard::Syntax
{
    SyntaxTree::Syntax::SyntaxElement* Tree::beforeParse(std::list<SyntaxTree::Syntax::SyntaxElement *> *elements)
    {
        return this->parse(elements);
    }
}
