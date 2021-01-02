#include <trw.h>
#include <io-buffer.h>
#include <syntax-tree-lib.h>

namespace TemplateRenderWizard::Token
{
    OpenTagValue::OpenTagValue(int line, int column) : SyntaxTree::Token::Token(line, column, nullptr)
    {
    }

    int OpenTagValue::getType() {
        return Type::OpenTagValueType;
    }
}
