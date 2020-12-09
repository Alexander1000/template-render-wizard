#include <trw.h>

namespace TemplateRenderWizard
{
    Value* Render::calc_expr(Expression *expr)
    {
        if (expr->getToken()->getType() != Token::Type::MathOperationType) {
            throw new UnexpectedToken;
        }

        Value* lValue;
        switch (expr->getLValue()->getType()) {
            case SyntaxTokenType: {
                lValue = this->getValueFromToken((Token::Token*) expr->getLValue()->getData());
                break;
            }
            case SyntaxValueType: {
                lValue = (Value*) expr->getLValue()->getData();
                break;
            }
            case SyntaxExpressionType: {
                lValue = this->calc_expr((Expression*) expr->getLValue()->getData());
                break;
            }
        }

        Value* rValue;
        switch (expr->getRValue()->getType()) {
            case SyntaxTokenType: {
                rValue = this->getValueFromToken((Token::Token *) expr->getRValue()->getData());
                break;
            }
            case SyntaxValueType: {
                rValue = (Value*) expr->getRValue()->getData();
                break;
            }
            case SyntaxExpressionType: {
                rValue = this->calc_expr((Expression*) expr->getRValue()->getData());
                break;
            }
        }

        INIT_CHAR_STRING(opValue, 3)
        RESET_TOKEN_READER(expr->getToken());
        expr->getToken()->getReader()->read(opValue, 3);

        if (strcmp(opValue, "+") == 0) {
            Value* v;
            v = new Value();
            v->setData(cast_value_to_int(lValue) + cast_value_to_int(rValue));
            return v;
        }

        if (strcmp(opValue, "*") == 0) {
            Value* v;
            v = new Value();
            v->setData(cast_value_to_int(lValue) * cast_value_to_int(rValue));
            return v;
        }

        return nullptr;
    }
}
