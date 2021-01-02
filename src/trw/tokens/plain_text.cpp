#include <trw.h>
#include <io-buffer.h>
#include <syntax-tree-lib.h>

namespace TemplateRenderWizard::Token
{
    PlainText::PlainText(int line, int column, IOBuffer::IOReader *reader) : SyntaxTree::Token::Token(line, column, reader) {
    }

    int PlainText::getType() {
        return Type::PlainTextType;
    }
}
