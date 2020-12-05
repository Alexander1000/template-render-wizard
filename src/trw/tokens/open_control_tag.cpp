#include <trw/token.h>

namespace TemplateRenderWizard::Token
{
    OpenControlTag::OpenControlTag(int line, int column) : Token(line, column, nullptr)
    {
    }

    Type OpenControlTag::getType() {
        return Type::OpenControlTagType;
    }
}
