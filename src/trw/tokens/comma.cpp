#include <trw.h>
#include <syntax-tree-lib.h>

namespace TemplateRenderWizard::Token
{
    Comma::Comma(int line, int column) : SyntaxTree::Token::Token(line, column, nullptr) {
        this->line = line;
        this->column = column;
    }

    int Comma::getType() {
        return Type::CommaType;
    }
}
