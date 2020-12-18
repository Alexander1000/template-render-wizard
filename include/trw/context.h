#ifndef H_TRW_CONTEXT_INCLUDED
#define H_TRW_CONTEXT_INCLUDED

#include <trw/value.h>

namespace TemplateRenderWizard
{
    class Context
    {
    public:
        Context();

        void setValueContext(Value*);
        Value* getValueContext();

        void setValue(const char*, Value*);
        Value* getValue(const char*);

    private:
        Value* value;
    };
}

#endif
