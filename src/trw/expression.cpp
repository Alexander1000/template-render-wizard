#include <trw.h>
#include <syntax-tree-lib.h>

namespace TemplateRenderWizard
{
    Expression::Expression(SyntaxElement *lValue, SyntaxElement *rValue, SyntaxTree::Token::Token *token) {
        this->lValue = lValue;
        this->rValue = rValue;
        this->relation = token;
    }

    SyntaxElement::SyntaxElement(Value *value) {
        this->type = SyntaxValueType;
        this->data.value = value;
    }

    SyntaxElement::SyntaxElement(Expression *expr) {
        this->type = SyntaxExpressionType;
        this->data.expression = expr;
    }

    SyntaxElement::SyntaxElement(SyntaxTree::Token::Token *token) {
        this->type = SyntaxTokenType;
        this->data.token = token;
    }

    SyntaxElementType SyntaxElement::getType() {
        return this->type;
    }

    void* SyntaxElement::getData() {
        return (void*) this->data.token;
    }

    SyntaxElement* Expression::getLValue() {
        return this->lValue;
    }

    SyntaxElement* Expression::getRValue() {
        return this->rValue;
    }

    SyntaxTree::Token::Token* Expression::getToken() {
        return this->relation;
    }
}
