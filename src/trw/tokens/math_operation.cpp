#include <trw.h>
#include <io-buffer.h>
#include <syntax-tree-lib.h>

namespace TemplateRenderWizard::Token
{
    MathOperation::MathOperation(int line, int column, IOBuffer::IOReader *reader) : SyntaxTree::Token::Token(line, column, reader) {
    }

    int MathOperation::getType() {
        return Type::MathOperationType;
    }
}
