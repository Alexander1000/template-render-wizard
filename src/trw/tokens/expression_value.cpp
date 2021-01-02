#include <trw.h>
#include <io-buffer.h>
#include <syntax-tree-lib.h>

namespace TemplateRenderWizard::Token
{
    ExpressionValue::ExpressionValue(int line, int column, IOBuffer::IOReader *reader) : SyntaxTree::Token::Token(line, column, reader) {
    }

    int ExpressionValue::getType() {
        return Type::ExpressionValueType;
    }
}
