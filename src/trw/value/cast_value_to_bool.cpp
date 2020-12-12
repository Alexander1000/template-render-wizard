#include <trw.h>
#include <iostream>

namespace TemplateRenderWizard
{
    bool cast_value_to_bool(Value* value)
    {
        switch (value->getType()) {
            case ValueType::None: {
                return false;
            }
            case ValueType::Integer: {
                return *value->getData<int*>() != 0;
            }
            case ValueType::String: {
                return strlen(value->getData<char*>()) > 0;
            }
            default: {
                std::cout << "Unexpected value" << std::endl;
                throw new UnexpectedToken;
            }
        }
    }
}
