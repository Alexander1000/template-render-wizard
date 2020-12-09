#include <trw.h>

namespace TemplateRenderWizard
{

    Value* Render::getValueFromToken(Token::Token *token)
    {
        if (token->getType() != TemplateRenderWizard::Token::Type::ExpressionValueType) {
            throw new UnexpectedToken;
        }

        INIT_CHAR_STRING(tokenValue, 128)
        token->getReader()->read(tokenValue, 128);

        auto leafValue = this->tree->get(tokenValue);
        if (leafValue != nullptr) {
            switch(leafValue->getType()) {
                case TemplateRenderWizard::Tree::LeafElementType::LeafElementText: {
                    auto str = (std::string*) leafValue->getData();
                    Value* v;
                    v = new Value();
                    int nSize = str->length() + 1;
                    INIT_CHAR_STRING(newStr, nSize)
                    memcpy(newStr, str->c_str(), (nSize - 1) * sizeof(char));
                    v->setData(newStr);
                    return v;
                }
                case TemplateRenderWizard::Tree::LeafElementType::LeafElementArray: {
                    throw new UnexpectedToken;
                    break;
                }
                case TemplateRenderWizard::Tree::LeafElementType::LeafElementObject: {
                    throw new UnexpectedToken;
                    break;
                }
            }
        } else {
            Value* v = new Value;
            int length = strlen(tokenValue) + 1;
            INIT_CHAR_STRING(strValue, length)
            memcpy(strValue, tokenValue, sizeof(char) * length);
            v->setData(strValue);
            return v;
        }

        return nullptr;
    }
}
