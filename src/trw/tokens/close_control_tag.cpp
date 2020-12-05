#include <trw/token.h>

namespace TemplateRenderWizard::Token
{
    CloseControlTag::CloseControlTag(int line, int column) : Token(line, column, nullptr)
    {
    }

    Type CloseControlTag::getType() {
        return Type::CloseControlTagType;
    }
}
