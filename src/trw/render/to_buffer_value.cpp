#include <trw.h>
#include <iostream>

namespace TemplateRenderWizard
{
    void Render::to_buffer_value(IOBuffer::IOBuffer *buffer, Token::Token *token)
    {
        this->to_buffer_value(buffer, this->getValueFromToken(token, nullptr));
    }

    void Render::to_buffer_value(IOBuffer::IOBuffer *buffer, Value *value)
    {
        switch (value->getType()) {
            case ValueType::String: {
                const char* data = value->getData<char*>();
                buffer->write((char*) data, strlen(data));
                break;
            }

            case ValueType::Integer: {
                INIT_CHAR_STRING(strDigit, 10)
                sprintf(strDigit, "%d", *value->getData<int*>());
                buffer->write(strDigit, strlen(strDigit));
                break;
            }

            case ValueType::None: {
                break;
            }

            default: {
                std::cout << "to_buffer_value.cpp: unexpected value type" << std::endl;
                throw new UnexpectedToken;
            }
        }
    }
}
