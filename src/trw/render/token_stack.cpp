#include <trw.h>

namespace TemplateRenderWizard
{
    Token::Token* Render::getNextToken()
    {
        if (!this->tokenStack->empty()) {
            auto token = this->tokenStack->top();
            this->tokenStack->pop();
            return token;
        }

        return this->stream->getNextToken();
    }

    void Render::pushBackToken(Token::Token *token)
    {
        this->tokenStack->push(token);
    }
}
