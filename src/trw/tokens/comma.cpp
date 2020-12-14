#include <trw.h>

namespace TemplateRenderWizard::Token
{
    Comma::Comma(int line, int column) : Token(line, column, nullptr) {
        this->line = line;
        this->column = column;
    }

    Type Comma::getType() {
        return Type::CommaType;
    }
}
