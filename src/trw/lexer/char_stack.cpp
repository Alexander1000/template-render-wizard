#include <trw.h>

namespace TemplateRenderWizard::Lexer
{
    char* Lexer::getNextChar()
    {
        if (!this->charStack->empty()) {
            char* symbol = this->charStack->top();
            this->charStack->pop();
            // todo: free current position
            this->position = this->positionStack->top();
            this->positionStack->pop();
            return symbol;
        }

        char* nextChar = this->charStream->getNext();
        if (nextChar != nullptr) {
            if (*nextChar == 0x0A || *nextChar == 0x0D) {
                this->position->setColumn(0);
                this->position->setLine(this->position->getLine() + 1);
            } else {
                this->position->setColumn(this->position->getColumn() + 1);
            }
        }

        return nextChar;
    }

    void Lexer::pushStackChar(char* curChar) {
        this->charStack->push(curChar);
        auto p = new Position(this->position->getLine(), this->position->getColumn());
        this->positionStack->push(p);
    }
}
