#include <trw.h>
#include <syntax-tree-lib.h>

namespace TemplateRenderWizard::Token
{
    DoubleDot::DoubleDot(int line, int column) : SyntaxTree::Token::Token(line, column, nullptr) {
        this->line = line;
        this->column = column;
    }

    int DoubleDot::getType() {
        return Type::DoubleDotType;
    }
}
