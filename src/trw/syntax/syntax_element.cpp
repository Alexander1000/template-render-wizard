#include <trw.h>

namespace TemplateRenderWizard::Syntax
{
    SyntaxElement::SyntaxElement(TemplateRenderWizard::Token::Token* token) {
        this->data.token = token;
        this->type = SyntaxElementType::TokenType;
    }

    SyntaxElement::SyntaxElement(SyntaxElement *syntaxElement) {
        this->data.syntaxElement = syntaxElement;
        this->type = SyntaxElementType::SyntaxType;
    }
}
