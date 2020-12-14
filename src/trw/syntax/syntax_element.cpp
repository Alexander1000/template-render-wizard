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

    SyntaxElementType SyntaxElement::getType() {
        return this->type;
    }

    TemplateRenderWizard::Token::Token * SyntaxElement::getToken() {
        return this->data.token;
    }

    SyntaxElement * SyntaxElement::getElement() {
        return this->data.syntaxElement;
    }

    Rule * SyntaxElement::getRule() {
        return this->rule;
    }
}
