#include <trw/token.h>
#include <io-buffer.h>

namespace TemplateRenderWizard::Token
{
    MathOperationHighPriority::MathOperationHighPriority(int line, int column, IOBuffer::IOReader *reader) : Token(line, column, reader) {
    }

    Type MathOperationHighPriority::getType() {
        return Type::MathOperationHighPriorityType;
    }
}
