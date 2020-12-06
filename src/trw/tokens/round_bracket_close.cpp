#include <trw/token.h>

namespace TemplateRenderWizard::Token
{
    RoundBracketClose::RoundBracketClose(int line, int column) : Token(line, column, nullptr)
    {
    }

    Type RoundBracketClose::getType() {
        return Type::RoundBracketCloseType;
    }
}
