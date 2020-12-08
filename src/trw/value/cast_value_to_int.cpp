#include <trw.h>

namespace TemplateRenderWizard
{
    int cast_value_to_int(Value* value)
    {
        if (value->getType() == ValueType::String && ctype_digits(value->getData<char*>())) {
            const char* src = value->getData<char*>();
            int size = strlen(src) + 1;
            INIT_CHAR_STRING(dst, size)
            memcpy(dst, src, sizeof(char) * (size - 1));
            return atoi(value->getData<char*>());
        }

        if (value->getType() == ValueType::Integer) {
            return *value->getData<int*>();
        }

        return 0;
    }
}
