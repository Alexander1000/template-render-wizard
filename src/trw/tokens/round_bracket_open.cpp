#include <trw.h>
#include <syntax-tree-lib.h>

namespace TemplateRenderWizard::Token
{
    RoundBracketOpen::RoundBracketOpen(int line, int column) : SyntaxTree::Token::Token(line, column, nullptr)
    {
    }

    int RoundBracketOpen::getType() {
        return Type::RoundBracketOpenType;
    }
}
