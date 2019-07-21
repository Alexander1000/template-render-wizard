#include <trw/token.h>

namespace TemplateRenderWizard::Token
{
    OpenTagValue::OpenTagValue() : Token()
    {
    }

    Type OpenTagValue::getType() {
        return Type::OpenTagValueType;
    }
}
