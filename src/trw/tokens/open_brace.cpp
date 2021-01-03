#include <trw.h>
#include <syntax-tree-lib.h>

namespace TemplateRenderWizard::Token
{
    OpenBrace::OpenBrace(int line, int column) : SyntaxTree::Token::Token(line, column, nullptr) {
        this->line = line;
        this->column = column;
    }

    int OpenBrace::getType() {
        return Type::OpenBraceType;
    }
}
