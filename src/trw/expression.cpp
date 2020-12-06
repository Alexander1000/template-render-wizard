#include <trw.h>

namespace TemplateRenderWizard
{
    Expression::Expression(SyntaxElement *lValue, SyntaxElement *rValue, Token::Token *token) {
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

    SyntaxElement::SyntaxElement(Token::Token *token) {
        this->type = SyntaxTokenType;
        this->data.token = token;
    }
}
