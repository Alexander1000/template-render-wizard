#include <trw.h>
#include <iostream>

namespace TemplateRenderWizard
{
    Value* Render::getValueFromToken(Token::Token *token)
    {
        bool allow = false;
        if (token->getType() == TemplateRenderWizard::Token::Type::ExpressionValueType || token->getType() == TemplateRenderWizard::Token::Type::PlainValueType) {
            allow = true;
        }
        if (!allow) {
            std::cout << "Line: " << token->getLine() << "; Column: " << token->getColumn() << std::endl;
            throw new UnexpectedToken;
        }

        INIT_CHAR_STRING(tokenValue, 128)
        RESET_TOKEN_READER(token);
        token->getReader()->read(tokenValue, 128);

        if (!ctype_digits(tokenValue)) {
            auto leafValue = this->tree->get(tokenValue);
            if (leafValue != nullptr) {
                if (leafValue->getType() != TemplateRenderWizard::Tree::LeafElementType::LeafElementText) {
                    std::cout << "Unexpected leaf" << std::endl;
                    throw new UnexpectedToken;
                }

                auto str = (std::string *) leafValue->getData();
                Value *v;
                v = new Value();
                int nSize = str->length() + 1;
                INIT_CHAR_STRING(newStr, nSize)
                memcpy(newStr, str->c_str(), (nSize - 1) * sizeof(char));
                v->setData(newStr);
                return v;
            }

            Value *v;
            v = new Value();
            return v;
        }

        Value* v = new Value;
        int length = strlen(tokenValue) + 1;
        INIT_CHAR_STRING(strValue, length)
        memcpy(strValue, tokenValue, sizeof(char) * length);
        v->setData(strValue);
        return v;
    }
}
