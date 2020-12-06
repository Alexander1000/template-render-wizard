#include <trw/token.h>

namespace TemplateRenderWizard::Token
{
    RoundBracketOpen::RoundBracketOpen(int line, int column) : Token(line, column, nullptr)
    {
    }

    Type RoundBracketOpen::getType() {
        return Type::RoundBracketOpenType;
    }
}
