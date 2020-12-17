#ifndef H_TRW_VALUE
#define H_TRW_VALUE

#include <list>

namespace TemplateRenderWizard
{
    enum ValueType {
        None,
        String,
        Integer,
        Float,
        Array,
    };

    class Value
    {
    public:
        Value();
        ValueType getType();
        void setType(ValueType);
        void setData(int data);
        void setData(char* data);
        void setData(float data);
        void setData(std::list<Value*>* data);

        template<typename T> T getData()
        {
            return this->getDataTyped((T) nullptr);
        }

    private:
        ValueType type;

        union {
            int* i_data;
            char* c_data;
            float* f_data;
            std::list<Value*>* a_data;
        } _data;

        int* getDataTyped(int* nothing);
        char* getDataTyped(char* nothing);
        float* getDataTyped(float* nothing);
    };

    int cast_value_to_int(Value*);
    bool cast_value_to_bool(Value*);
}

#endif
