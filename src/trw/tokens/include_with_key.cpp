#include <trw.h>
#include <io-buffer.h>
#include <syntax-tree-lib.h>

namespace TemplateRenderWizard::Token
{
    IncludeWithKey::IncludeWithKey(int line, int column, IOBuffer::IOReader *reader) : SyntaxTree::Token::Token(line, column, reader) {
    }

    int IncludeWithKey::getType() {
        return Type::IncludeWithKeyType;
    }
}
