#include <trw/token.h>
#include <io-buffer.h>

namespace TemplateRenderWizard::Token
{
    ExpressionValue::ExpressionValue(int line, int column, IOBuffer::IOReader *reader) : Token(line, column, reader) {
    }

    Type ExpressionValue::getType() {
        return Type::ExpressionValueType;
    }
}
