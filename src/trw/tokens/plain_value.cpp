#include <trw/token.h>
#include <io-buffer.h>

namespace TemplateRenderWizard::Token
{
    PlainValue::PlainValue(int line, int column, IOBuffer::IOReader *reader) : Token(line, column, reader) {
    }

    Type PlainValue::getType() {
        return Type::PlainValueType;
    }
}
