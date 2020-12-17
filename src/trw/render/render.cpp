#include <io-buffer.h>
#include <memory.h>
#include <iostream>
#include <list>
#include <trw.h>

namespace TemplateRenderWizard
{
    bool Render::compare_value(Value *lValue, Value *rValue, Token::Token *token)
    {
        RESET_TOKEN_READER(token);
        INIT_CHAR_STRING(cmpValue, 4)
        token->getReader()->read(cmpValue, 4);

        if (lValue->getType() == ValueType::String && ctype_digits(lValue->getData<char*>())) {
            const char* src = lValue->getData<char*>();
            int size = strlen(src) + 1;
            INIT_CHAR_STRING(dst, size)
            memcpy(dst, src, sizeof(char) * (size - 1));
            Value* v;
            v = new Value();
            v->setData(atoi(lValue->getData<char *>()));
            lValue = v;
        }

        if (rValue->getType() == ValueType::String && ctype_digits(rValue->getData<char*>())) {
            const char* src = rValue->getData<char*>();
            int size = strlen(src) + 1;
            INIT_CHAR_STRING(dst, size)
            memcpy(dst, src, sizeof(char) * (size - 1));
            Value* v;
            v = new Value();
            v->setData(atoi(rValue->getData<char *>()));
            rValue = v;
        }

        if (lValue->getType() == ValueType::Integer && rValue->getType() == ValueType::Integer) {
            if (strcmp(cmpValue, ">=") == 0) {
                return *lValue->getData<int*>() >= *rValue->getData<int*>();
            }
        }

        std::cout << "Line: " << token->getLine() << "; Column: " << token->getColumn() << std::endl;
        throw new UnexpectedToken;
    }
}
