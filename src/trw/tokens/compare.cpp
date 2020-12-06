#include <trw/token.h>
#include <io-buffer.h>

namespace TemplateRenderWizard::Token
{
    Compare::Compare(int line, int column, IOBuffer::IOReader *reader) : Token(line, column, reader) {
    }

    Type Compare::getType() {
        return Type::CompareType;
    }
}
