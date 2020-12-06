#ifndef H_TRW_VALUE
#define H_TRW_VALUE

namespace TemplateRenderWizard
{
    enum ValueType {
        String,
        Integer,
        Float,
    };

    class Value
    {
    public:
        Value();
        ValueType getType();

    private:
        ValueType type;

        union {
            int i_data;
            char* c_data;
            float f_data;
        } _data;
    };
}

#endif
