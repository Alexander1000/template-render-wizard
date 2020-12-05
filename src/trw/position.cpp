#include <trw.h>

namespace TemplateRenderWizard
{
    Position::Position(int line, int column) {
        this->line = line;
        this->column = column;
    }

    int Position::getColumn() {
        return this->column;
    }

    int Position::getLine() {
        return this->line;
    }

    void Position::setColumn(int column) {
        this->column = column;
    }

    void Position::setLine(int line) {
        this->line = line;
    }
}
