#include <trw.h>
#include <syntax-tree-lib.h>

namespace TemplateRenderWizard::Token
{
    CloseBrace::CloseBrace(int line, int column) : SyntaxTree::Token::Token(line, column, nullptr) {
        this->line = line;
        this->column = column;
    }

    int CloseBrace::getType() {
        return Type::CloseBraceType;
    }
}
