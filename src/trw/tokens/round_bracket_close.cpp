#include <trw.h>
#include <syntax-tree-lib.h>

namespace TemplateRenderWizard::Token
{
    RoundBracketClose::RoundBracketClose(int line, int column) : SyntaxTree::Token::Token(line, column, nullptr)
    {
    }

    int RoundBracketClose::getType() {
        return Type::RoundBracketCloseType;
    }
}
