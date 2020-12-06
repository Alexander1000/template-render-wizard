#include <trw/token.h>
#include <io-buffer.h>

namespace TemplateRenderWizard::Token
{
    MathOperation::MathOperation(int line, int column, IOBuffer::IOReader *reader) : Token(line, column, reader) {
    }

    Type MathOperation::getType() {
        return Type::MathOperationType;
    }
}
