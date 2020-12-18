#ifndef H_TRW_CONTEXT_INCLUDED
#define H_TRW_CONTEXT_INCLUDED

#include <trw/value.h>

namespace TemplateRenderWizard
{
    class Context
    {
    public:
        Context();

    private:
        Value* value;
    };
}

#endif
