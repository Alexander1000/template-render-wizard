#include <trw.h>

namespace TemplateRenderWizard
{
    Token::Token* Render::getNextToken()
    {
        return this->stream->getNextToken();
    }
}
