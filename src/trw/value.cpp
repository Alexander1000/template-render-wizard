#include <trw.h>
#include <list>
#include <map>

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

    void Value::setData(std::map<std::string, Value*>* data)
    {
        this->type = Object;
        this->_data.o_data = data;
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

    std::list<Value*>* Value::getArray() {
        return this->_data.a_data;
    }

    Value* cast_yaml_array_to_value(std::list<Tree::LeafElement*>* yamlList)
    {
        auto v = new Value();

        auto l = new std::list<Value*>;

        for (auto it = yamlList->begin(); it != yamlList->end(); it++) {
            if ((*it)->getType() == Tree::LeafElementType::LeafElementObject) {
                l->push_back(cast_yaml_object_to_value((std::map<std::string, Tree::LeafElement*>*) (*it)->getData()));
            }
            if ((*it)->getType() == Tree::LeafElementType::LeafElementArray) {
                l->push_back(cast_yaml_array_to_value((std::list<Tree::LeafElement*>*) (*it)->getData()));
            }
            if ((*it)->getType() == Tree::LeafElementType::LeafElementText) {
                auto strData = (std::string*) (*it)->getData();
                INIT_CHAR_STRING(tmpStrData, 1024);
                memcpy(tmpStrData, strData->c_str(), strData->length());
                auto newV = new Value();
                newV->setData(tmpStrData);
                l->push_back(newV);
            }
        }

        v->setData(l);
        return v;
    }

    Value* cast_yaml_object_to_value(std::map<std::string, Tree::LeafElement*>* yamlObject)
    {
        auto v = new Value();

        auto m = new std::map<std::string, Value*>;

        for (auto it = yamlObject->begin(); it != yamlObject->end(); it++) {
            // it->first
            if (it->second->getType() == Tree::LeafElementType::LeafElementObject) {
                (*m)[it->first] = cast_yaml_object_to_value((std::map<std::string, Tree::LeafElement*>*) it->second->getData());
            }
            if (it->second->getType() == Tree::LeafElementType::LeafElementArray) {
                (*m)[it->first] = cast_yaml_array_to_value((std::list<Tree::LeafElement*>*) it->second->getData());
            }
            if (it->second->getType() == Tree::LeafElementType::LeafElementText) {
                auto strData = (std::string*) it->second->getData();
                INIT_CHAR_STRING(tmpStrData, 1024);
                memcpy(tmpStrData, strData->c_str(), strData->length());
                auto newV = new Value();
                newV->setData(tmpStrData);
                (*m)[it->first] = newV;
            }
        }

        v->setData(m);

        return v;
    }
}
