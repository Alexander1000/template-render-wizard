#include <trw/token.h>
#include <io-buffer.h>

namespace TemplateRenderWizard::Token
{
    OpenTagValue::OpenTagValue(int line, int column) : Token(line, column, nullptr)
    {
    }

    Type OpenTagValue::getType() {
        return Type::OpenTagValueType;
    }
}
