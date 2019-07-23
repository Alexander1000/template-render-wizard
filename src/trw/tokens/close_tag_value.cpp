#include <trw/token.h>

namespace TemplateRenderWizard::Token
{
    CloseTagValue::CloseTagValue(int line, int column) : Token(line, column, nullptr) {
    }

    Type CloseTagValue::getType() {
        return Type::CloseTagValueType;
    }
}
