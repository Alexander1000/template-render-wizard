#include <trw/tree_parameters.h>

namespace TemplateRenderWizard::Tree
{
    LeafElement::LeafElement(LeafElementType type, void* data)
    {
        this->type = type;
        this->data = data;
    }

    LeafElementType LeafElement::getType() {
        return this->type;
    }

    void* LeafElement::getData() {
        return this->data;
    }
}
