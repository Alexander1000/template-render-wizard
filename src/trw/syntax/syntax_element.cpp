#include <trw.h>
#include <list>

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

    SyntaxElement::SyntaxElement(std::list<SyntaxElement*>* listElements) {
        this->type = SyntaxElementType::TokenListType;
        this->data.elements = listElements;
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

    void SyntaxElement::setRule(Rule *ruleElement) {
        this->rule = ruleElement;
    }

    std::list<SyntaxElement*>* SyntaxElement::getListElements() {
        return this->data.elements;
    }
}
