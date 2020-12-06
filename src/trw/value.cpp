#include <trw.h>

namespace TemplateRenderWizard
{
    Value::Value() {
        this->type = None;
        this->_data.i_data = 0;
    }

    ValueType Value::getType() {
        return this->type;
    }

    void Value::setType(ValueType valueType) {
        this->type = valueType;
    }

    void Value::setData(int data) {
        this->type = Integer;
        this->_data.i_data = data;
    }

    void Value::setData(char *data) {
        this->type = String;
        this->_data.c_data = data;
    }

    void Value::setData(float data) {
        this->type = Float;
        this->_data.f_data = data;
    }
}
