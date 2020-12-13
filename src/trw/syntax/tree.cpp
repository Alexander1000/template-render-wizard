#include <trw.h>
#include <list>

namespace TemplateRenderWizard::Syntax
{
    Tree::Tree() {
        this->rules = new std::list<Rule*>;
        this->initializeDefaults();
    }

    void Tree::initializeDefaults()
    {
        // do make syntax tree rules
    }
}
