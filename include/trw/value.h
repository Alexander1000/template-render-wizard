#ifndef H_TRW_VALUE
#define H_TRW_VALUE

namespace TemplateRenderWizard
{
    enum ValueType {
        None,
        String,
        Integer,
        Float,
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
        } _data;

        int* getDataTyped(int* nothing);
        char* getDataTyped(char* nothing);
        float* getDataTyped(float* nothing);
    };
}

#endif
