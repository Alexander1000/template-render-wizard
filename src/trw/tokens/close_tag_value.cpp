#include <trw.h>
#include <syntax-tree-lib.h>

namespace TemplateRenderWizard::Token
{
    CloseTagValue::CloseTagValue(int line, int column) : SyntaxTree::Token::Token(line, column, nullptr) {
    }

    int CloseTagValue::getType() {
        return Type::CloseTagValueType;
    }
}
