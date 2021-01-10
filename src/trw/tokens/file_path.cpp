#include <trw.h>
#include <io-buffer.h>
#include <syntax-tree-lib.h>

namespace TemplateRenderWizard::Token
{
    FilePath::FilePath(int line, int column, IOBuffer::IOReader *reader) : SyntaxTree::Token::Token(line, column, reader) {
    }

    int FilePath::getType() {
        return Type::FilePathType;
    }
}
