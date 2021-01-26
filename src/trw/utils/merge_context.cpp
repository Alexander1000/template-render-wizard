#include <trw.h>

namespace TemplateRenderWizard
{
    void merge_context(Context* dst, Context* src)
    {
        auto value = src->getValueContext();
        if (value != nullptr && value->getType() == ValueType::Object) {
            auto ctxObject = value->getObject();
            for (auto it = ctxObject->begin(); it != ctxObject->end(); it++) {
                dst->setValue(it->first.c_str(), it->second);
            }
        }
    }
}
