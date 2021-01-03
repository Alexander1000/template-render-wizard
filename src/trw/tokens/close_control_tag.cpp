#include <trw.h>
#include <syntax-tree-lib.h>

namespace TemplateRenderWizard::Token
{
    CloseControlTag::CloseControlTag(int line, int column) : SyntaxTree::Token::Token(line, column, nullptr)
    {
    }

    int CloseControlTag::getType() {
        return Type::CloseControlTagType;
    }
}
