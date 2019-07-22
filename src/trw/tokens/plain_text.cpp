#include <trw/token.h>
#include <io-buffer.h>

namespace TemplateRenderWizard::Token
{
    PlainText::PlainText(int line, int column, IOBuffer::IOReader *reader) : Token(line, column, reader) {
    }

    Type PlainText::getType() {
        return Type::PlainTextType;
    }
}
