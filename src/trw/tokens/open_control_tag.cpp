#include <trw.h>
#include <syntax-tree-lib.h>

namespace TemplateRenderWizard::Token
{
    OpenControlTag::OpenControlTag(int line, int column) : SyntaxTree::Token::Token(line, column, nullptr)
    {
    }

    int OpenControlTag::getType() {
        return Type::OpenControlTagType;
    }
}
