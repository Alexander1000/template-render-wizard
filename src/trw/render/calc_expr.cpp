#include <trw.h>

namespace TemplateRenderWizard
{
    Value* Render::calc_expr(Expression *expr)
    {
        if (expr->getToken()->getType() != Token::Type::MathOperationType) {
            throw new UnexpectedToken;
        }

        Value* lValue = this->get_value_from_syntax_element(expr->getLValue());

        Value* rValue = this->get_value_from_syntax_element(expr->getRValue());

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
