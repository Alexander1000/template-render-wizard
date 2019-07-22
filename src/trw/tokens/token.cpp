#include <trw/token.h>
#include <io-buffer.h>

namespace TemplateRenderWizard::Token
{
    Token::Token(int line, int column, IOBuffer::IOReader *reader) {
        this->line = line;
        this->column = column;
        this->reader = reader;
    }
}
