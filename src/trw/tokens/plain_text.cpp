#include <trw/token.h>

namespace TemplateRenderWizard::Token
{
    PlainText::PlainText() : Token() {
    }

    Type PlainText::getType() {
        return Type::PlainTextType;
    }
}
