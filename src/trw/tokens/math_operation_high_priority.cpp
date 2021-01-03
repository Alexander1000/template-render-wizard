#include <trw.h>
#include <io-buffer.h>
#include <syntax-tree-lib.h>

namespace TemplateRenderWizard::Token
{
    MathOperationHighPriority::MathOperationHighPriority(int line, int column, IOBuffer::IOReader *reader) : SyntaxTree::Token::Token(line, column, reader) {
    }

    int MathOperationHighPriority::getType() {
        return Type::MathOperationHighPriorityType;
    }
}
