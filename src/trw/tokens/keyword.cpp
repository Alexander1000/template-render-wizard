#include <trw/token.h>
#include <io-buffer.h>

namespace TemplateRenderWizard::Token
{
    Keyword::Keyword(int line, int column, IOBuffer::IOReader *reader) : Token(line, column, reader) {
    }

    Type Keyword::getType() {
        return Type::KeywordType;
    }
}
