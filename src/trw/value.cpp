#include <trw.h>
#include <list>

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
        this->_data.i_data = new int;
        *this->_data.i_data = data;
    }

    void Value::setData(char *data) {
        this->type = String;
        this->_data.c_data = data;
    }

    void Value::setData(float data) {
        this->type = Float;
        this->_data.f_data = new float;
        *this->_data.f_data = data;
    }

    void Value::setData(std::list<Value*>* data)
    {
        this->type = Array;
        this->_data.a_data = data;
    }

    int* Value::getDataTyped(int* nothing)
    {
        return this->_data.i_data;
    }

    char* Value::getDataTyped(char* nothing)
    {
        return this->_data.c_data;
    }

    float* Value::getDataTyped(float* nothing)
    {
        return this->_data.f_data;
    }
}
