#include <trw.h>
#include <iostream>

typedef std::list<TemplateRenderWizard::Tree::LeafElement*> LeafArray;

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
                if (leafValue->getType() == TemplateRenderWizard::Tree::LeafElementType::LeafElementText) {
                    auto str = (std::string *) leafValue->getData();
                    Value *v;
                    v = new Value();
                    int nSize = str->length() + 1;
                    INIT_CHAR_STRING(newStr, nSize)
                    memcpy(newStr, str->c_str(), (nSize - 1) * sizeof(char));
                    v->setData(newStr);
                    return v;
                }

                if (leafValue->getType() == Tree::LeafElementArray) {
                    Value *v;
                    v = new Value();
                    auto list = new std::list<Value*>;
                    auto leafArray = (LeafArray*) leafValue->getData();
                    for (auto it = leafArray->begin(); it != leafArray->end(); it++) {
                        auto leafElement = *it;
                    }
                    v->setData(list);
                    return v;
                }

                std::cout << "Unexpected leaf" << std::endl;
                throw new UnexpectedToken;
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
